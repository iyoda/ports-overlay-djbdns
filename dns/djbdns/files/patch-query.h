--- query.h	2026-05-27 09:06:09.748150000 +0000
+++ query.h	2026-05-27 09:06:09.760608000 +0000
@@ -1,7 +1,7 @@
 #ifndef QUERY_H
 #define QUERY_H
 
-#include "dns.h"
+#include "qmerge.h"
 #include "uint32.h"
 
 #define QUERY_MAXLEVEL 5
@@ -22,7 +22,7 @@
   uint32 scope_id;
   char type[2];
   char class[2];
-  struct dns_transmit dt;
+  struct qmerge *qm;
 } ;
 
 extern int query_start(struct query *z,char *dn,char type[2],char class[2],unsigned char localip[16],unsigned int scope_id);
