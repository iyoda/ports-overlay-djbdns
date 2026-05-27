--- query.c	2026-05-27 09:06:09.748112000 +0000
+++ query.c	2026-05-27 09:06:09.762020000 +0000
@@ -84,7 +84,7 @@
   int j;
   int k;
 
-  dns_transmit_free(&z->dt);
+  qmerge_free(&z->qm);
   for (j = 0;j < QUERY_MAXALIAS;++j)
     dns_domain_free(&z->alias[j]);
   for (j = 0;j < QUERY_MAXLEVEL;++j) {
@@ -475,6 +475,29 @@
       }
     }
 
+    if (typematch(DNS_T_SOA,dtype)) {
+      byte_copy(key,2,DNS_T_SOA);
+      cached = cache_get(key,dlen + 2,&cachedlen,&ttl);
+      if (cached && (cachedlen || byte_diff(dtype,2,DNS_T_ANY))) {
+        log_cachedanswer(d,DNS_T_SOA);
+        if (!rqa(z)) goto DIE;
+        pos = 0;
+        while (pos = dns_packet_copy(cached,cachedlen,pos,misc,20)) {
+          pos = dns_packet_getname(cached,cachedlen,pos,&t2);
+          if (!pos) break;
+          pos = dns_packet_getname(cached,cachedlen,pos,&t3);
+          if (!pos) break;
+          if (!response_rstart(d,DNS_T_SOA,ttl)) goto DIE;
+          if (!response_addname(t2)) goto DIE;
+          if (!response_addname(t3)) goto DIE;
+          if (!response_addbytes(misc,20)) goto DIE;
+          response_rfinish(RESPONSE_ANSWER);
+        }
+        cleanup(z);
+        return 1;
+      }
+    }
+
     if (typematch(DNS_T_A,dtype)) {
       byte_copy(key,2,DNS_T_A);
       cached = cache_get(key,dlen + 2,&cachedlen,&ttl);
@@ -544,7 +567,7 @@
       }
     }
 
-    if (!typematch(DNS_T_ANY,dtype) && !typematch(DNS_T_AXFR,dtype) && !typematch(DNS_T_CNAME,dtype) && !typematch(DNS_T_NS,dtype) && !typematch(DNS_T_PTR,dtype) && !typematch(DNS_T_A,dtype) && !typematch(DNS_T_MX,dtype) && !typematch(DNS_T_AAAA,dtype)) {
+    if (!typematch(DNS_T_ANY,dtype) && !typematch(DNS_T_AXFR,dtype) && !typematch(DNS_T_CNAME,dtype) && !typematch(DNS_T_NS,dtype) && !typematch(DNS_T_PTR,dtype) && !typematch(DNS_T_A,dtype) && !typematch(DNS_T_MX,dtype) && !typematch(DNS_T_SOA,dtype) && !typematch(DNS_T_AAAA,dtype)) {
       byte_copy(key,2,dtype);
       cached = cache_get(key,dlen + 2,&cachedlen,&ttl);
       if (cached && (cachedlen || byte_diff(dtype,2,DNS_T_ANY))) {
@@ -623,15 +646,9 @@
   if (j == 256) goto SERVFAIL;
 
   dns_sortip6(z->servers[z->level],256);
-  if (z->level) {
-    dtype = z->ipv6[z->level] ? DNS_T_AAAA : DNS_T_A;
-    log_tx(z->name[z->level],dtype,z->control[z->level],z->servers[z->level],z->level);
-    if (dns_transmit_start(&z->dt,z->servers[z->level],flagforwardonly,z->name[z->level],dtype,z->localip) == -1) goto DIE;
-  }
-  else {
-    log_tx(z->name[0],z->type,z->control[0],z->servers[0],0);
-    if (dns_transmit_start(&z->dt,z->servers[0],flagforwardonly,z->name[0],z->type,z->localip) == -1) goto DIE;
-  }
+  dtype = z->level ? (z->ipv6[z->level] ? DNS_T_AAAA : DNS_T_A) : z->type;
+  if (qmerge_start(&z->qm,z->servers[z->level],flagforwardonly,z->name[z->level],dtype,z->localip,z->control[z->level]) == -1) goto DIE;
+
   return 0;
 
 
@@ -645,10 +662,10 @@
 
   HAVEPACKET:
   if (++z->loop == 100) goto DIE;
-  buf = z->dt.packet;
-  len = z->dt.packetlen;
+  buf = z->qm->dt.packet;
+  len = z->qm->dt.packetlen;
 
-  whichserver = z->dt.servers + 16 * z->dt.curserver;
+  whichserver = z->qm->dt.servers + 16 * z->qm->dt.curserver;
   control = z->control[z->level];
   d = z->name[z->level];
 /*  dtype = z->level ? DNS_T_A : z->type; */
@@ -772,6 +789,12 @@
     }
 
     if (!dns_domain_suffix(t1,control)) { i = j; continue; }
+
+    if (!flagforwardonly && byte_equal(type,2,DNS_T_NS) && dns_domain_equal(t1,control)) {
+        char dummy[256];
+        if (!roots(dummy,control)) { i = j; continue; }
+    }
+
     if (!roots_same(t1,control)) { i = j; continue; }
 
     if (byte_equal(type,2,DNS_T_ANY))
@@ -779,15 +802,24 @@
     else if (byte_equal(type,2,DNS_T_AXFR))
       ;
     else if (byte_equal(type,2,DNS_T_SOA)) {
+      int non_authority = 0;
+      save_start();
       while (i < j) {
         pos = dns_packet_skipname(buf,len,records[i]); if (!pos) goto DIE;
         pos = dns_packet_getname(buf,len,pos + 10,&t2); if (!pos) goto DIE;
         pos = dns_packet_getname(buf,len,pos,&t3); if (!pos) goto DIE;
         pos = dns_packet_copy(buf,len,pos,misc,20); if (!pos) goto DIE;
-        if (records[i] < posauthority)
+        if (records[i] < posauthority) {
           log_rrsoa(whichserver,t1,t2,t3,(const char*)misc,ttl);
+          save_data(misc,20);
+          save_data(t2,dns_domain_length(t2));
+          save_data(t3,dns_domain_length(t3));
+          non_authority++;
+        }
         ++i;
       }
+      if (non_authority)
+        save_finish(DNS_T_SOA,t1,ttl);
     }
     else if (byte_equal(type,2,DNS_T_CNAME)) {
       pos = dns_packet_skipname(buf,len,records[j - 1]); if (!pos) goto DIE;
@@ -1069,7 +1101,7 @@
 
 int query_get(struct query *z,iopause_fd *x,struct taia *stamp)
 {
-  switch(dns_transmit_get(&z->dt,x,stamp)) {
+  switch(qmerge_get(&z->qm,x,stamp)) {
     case 1:
       return doit(z,1);
     case -1:
@@ -1080,5 +1112,5 @@
 
 void query_io(struct query *z,iopause_fd *x,struct taia *deadline)
 {
-  dns_transmit_io(&z->dt,x,deadline);
+  qmerge_io(z->qm,x,deadline);
 }
