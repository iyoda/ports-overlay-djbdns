--- log.c	2026-05-27 09:06:09.747547000 +0000
+++ log.c	2026-05-27 09:06:09.760272000 +0000
@@ -149,6 +149,13 @@
   line();
 }
 
+void log_tx_piggyback(const char *q, const char qtype[2], const char *control)
+{
+  string("txpb ");
+  logtype(qtype); space(); name(q); space(); name(control);
+  line();
+}
+
 void log_cachedanswer(const char *q,const char type[2])
 {
   string("cached "); logtype(type); space();
