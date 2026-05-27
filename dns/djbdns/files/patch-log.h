--- log.h	2026-05-27 09:06:09.747581000 +0000
+++ log.h	2026-05-27 09:06:09.760300000 +0000
@@ -18,6 +18,7 @@
 extern void log_cachedns(const char *,const char *);
 
 extern void log_tx(const char *q,const char qtype[2],const char *control,const unsigned char servers[256],unsigned int gluelessness);
+extern void log_tx_piggyback(const char *,const char *,const char *);
 
 extern void log_nxdomain(const unsigned char server[16],const char *q,unsigned int ttl);
 extern void log_nodata(const unsigned char server[16],const char *q,const char qtype[2],unsigned int ttl);
