--- dnscache.c	2026-05-27 09:06:09.746032000 +0000
+++ dnscache.c	2026-05-27 09:06:09.760235000 +0000
@@ -24,6 +24,7 @@
 #include "okclient.h"
 #include "droproot.h"
 #include "openreadclose.h"
+#include "maxclient.h"
 
 unsigned long interface;
 
@@ -60,7 +61,6 @@
 
 static int udp53;
 
-#define MAXUDP 200
 static struct udpclient {
   struct query q;
   struct taia start;
@@ -137,7 +137,6 @@
 
 static int tcp53;
 
-#define MAXTCP 20
 struct tcpclient {
   struct query q;
   struct taia start;
