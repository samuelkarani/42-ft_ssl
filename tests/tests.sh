echo "pickle rick" | openssl md5
c5e433c1dbd7ba01e3763a9483e74b04

echo "pickle rick" | md5
c5e433c1dbd7ba01e3763a9483e74b04
 
echo "pickle rick" | ./ft_ssl md5
c5e433c1dbd7ba01e3763a9483e74b04

echo "Do not pity the dead, Harry." | ./ft_ssl md5 -p
Do not pity the dead, Harry.
2d95365bc44bf0a298e09a3ab7b34d2f

echo "Pity the living." | ./ft_ssl md5 -q -r
e20c3b973f63482a778f3fd1869b7f25
 
echo "And above all," > file
./ft_ssl md5 file
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a
./ft_ssl md5 -r file
53d53ea94217b259c11a5a2d104ec58a file
 
./ft_ssl md5 -s "pity those that aren't following baerista on spotify."
MD5 ("pity those that aren't following baerista on spotify.") = a3c990a1964705d9bf0e602f44572f5f

echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file
be sure to handle edge cases carefully
3553dc7dc5963b583c056d1b9fa3349c
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a
 
echo "some of this will not make sense at first" | ./ft_ssl md5 file
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a

echo "but eventually you will understand" | ./ft_ssl md5 -p -r file
but eventually you will understand
dcdd84e0f635694d2a943fa8d3905281
53d53ea94217b259c11a5a2d104ec58a file
 
echo "GL HF let's go" | ./ft_ssl md5 -p -s "foo" file
GL HF let's go
d1e3cc342b6da09480b27ec57ff243e2
MD5 ("foo") = acbd18db4cc2f85cedef654fccc4a4d8
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a
 
echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"
one more thing
a0bd1876c6f011dd50fae52827f445f5
acbd18db4cc2f85cedef654fccc4a4d8 "foo"
53d53ea94217b259c11a5a2d104ec58a file
ft_ssl: md5: -s: No such file or directory
ft_ssl: md5: bar: No such file or directory
 
echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file
just to be extra clear
3ba35f1ea0d170cb3b9a752e3360286c
acbd18db4cc2f85cedef654fccc4a4d8
53d53ea94217b259c11a5a2d104ec58a


echo "https://www.youtube.com/watch?v=w-5yAtMtrSM" > big_smoke_order_remix
./ft_ssl sha256 -q big_smoke_order_remix
a8dc621c3dcf18a8a2eddae1845e8e5f6498970a867056ac5f7121ac3d66cfd9

openssl sha -sha256 big_smoke_order_remix
SHA256 (big_smoke_order_remix) = a8dc621c3dcf18a8a2eddae1845e8e5f6498970a867056ac5f7121ac3d66cfd9

./ft_ssl sha256 -s "wubba lubba dub dub"
SHA256 ("wubba lubba dub dub") = 23a0944d11b5a54f1970492b5265c732044ae824b7d5656acb193e7f0e51e5fa