--- tinydns-data.c	2026-05-27 09:06:09.749885000 +0000
+++ tinydns-data.c	2026-05-27 09:06:09.764845000 +0000
@@ -214,7 +214,7 @@
   char type[2];
   char soa[20];
   char buf[4];
-
+  uint32 hack64bit;
   umask(022);
 
   fddata = open_read("data");
@@ -269,19 +269,19 @@
 	if (!dns_domain_fromdot(&d1,f[0].s,f[0].len)) nomem();
 
 	if (!stralloc_0(&f[3])) nomem();
-	if (!scan_u32(f[3].s,&u)) uint32_unpack_big(defaultsoa,&u);
+	if (!scan_u32(f[3].s,&u)) { uint32_unpack_big(defaultsoa,&hack64bit); u = hack64bit; }
 	uint32_pack_big(soa,u);
 	if (!stralloc_0(&f[4])) nomem();
-	if (!scan_u32(f[4].s,&u)) uint32_unpack_big(defaultsoa + 4,&u);
+	if (!scan_u32(f[4].s,&u)) { uint32_unpack_big(defaultsoa + 4,&hack64bit); u = hack64bit; }
 	uint32_pack_big(soa + 4,u);
 	if (!stralloc_0(&f[5])) nomem();
-	if (!scan_u32(f[5].s,&u)) uint32_unpack_big(defaultsoa + 8,&u);
+	if (!scan_u32(f[5].s,&u)) { uint32_unpack_big(defaultsoa + 8,&hack64bit); u = hack64bit; }
 	uint32_pack_big(soa + 8,u);
 	if (!stralloc_0(&f[6])) nomem();
-	if (!scan_u32(f[6].s,&u)) uint32_unpack_big(defaultsoa + 12,&u);
+	if (!scan_u32(f[6].s,&u)) { uint32_unpack_big(defaultsoa + 12,&hack64bit); u = hack64bit; }
 	uint32_pack_big(soa + 12,u);
 	if (!stralloc_0(&f[7])) nomem();
-	if (!scan_u32(f[7].s,&u)) uint32_unpack_big(defaultsoa + 16,&u);
+	if (!scan_u32(f[7].s,&u)) { uint32_unpack_big(defaultsoa + 16,&hack64bit); u = hack64bit; }
 	uint32_pack_big(soa + 16,u);
 
 	if (!stralloc_0(&f[8])) nomem();
