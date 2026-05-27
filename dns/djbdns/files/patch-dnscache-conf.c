--- dnscache-conf.c.orig	2026-05-27 09:34:13 UTC
+++ dnscache-conf.c
@@ -91,13 +91,13 @@ int main(int argc,char **argv)
   if (chdir(auto_home) == -1)
     strerr_die4sys(111,FATAL,"unable to switch to ",auto_home,": ");
 
-  fdrootservers = open_read("/etc/dnsroots.local");
+  fdrootservers = open_read("etc/dnsroots.local");
   if (fdrootservers == -1) {
     if (errno != error_noent)
-      strerr_die2sys(111,FATAL,"unable to open /etc/dnsroots.local: ");
-    fdrootservers = open_read("/etc/dnsroots.global");
+      strerr_die4sys(111,FATAL,"unable to open ",auto_home,"/etc/dnsroots.local: ");
+    fdrootservers = open_read("etc/dnsroots.global");
     if (fdrootservers == -1)
-      strerr_die2sys(111,FATAL,"unable to open /etc/dnsroots.global: ");
+      strerr_die4sys(111,FATAL,"unable to open ",auto_home,"/etc/dnsroots.global: ");
   }
 
   init(dir,FATAL);
