--- hier.c.orig	2026-05-27 09:34:13 UTC
+++ hier.c
@@ -6,10 +6,10 @@ void hier()
 
 void hier()
 {
-  c("/","etc","dnsroots.global",-1,-1,0644);
+  c(auto_home,"etc","dnsroots.global",-1,-1,0644);
 
-  h(auto_home,-1,-1,02755);
-  d(auto_home,"bin",-1,-1,02755);
+  h(auto_home,-1,-1,0755);
+  d(auto_home,"bin",-1,-1,0755);
 
   c(auto_home,"bin","dnscache-conf",-1,-1,0755);
   c(auto_home,"bin","tinydns-conf",-1,-1,0755);
