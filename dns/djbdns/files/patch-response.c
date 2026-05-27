--- response.c	2026-05-27 09:06:09.748318000 +0000
+++ response.c	2026-05-27 09:06:09.758881000 +0000
@@ -34,7 +34,7 @@
         uint16_pack_big(buf,49152 + name_ptr[i]);
         return response_addbytes(buf,2);
       }
-    if (dlen <= 128)
+    if ((dlen <= 128) && (response_len < 16384))
       if (name_num < NAMES) {
 	byte_copy(name[name_num],dlen,d);
 	name_ptr[name_num] = response_len;
