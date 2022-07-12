The decompiled program includes a main() function, an m() function and an n() function. The main() function first allocates 64 bytes to store its given parameter using strcpy(). A function pointer is also declared and allocated on the heap, and takes the address of m(). The m() function is then called in that way. The m() function is pretty useless, but the n() function does exactly what we want to do, that is to display the content of the file /home/user/level7/.pass. It is quite clear that our goal here is to force the program to call the n() function instead of the m() function, by exploiting the strcpy() vulnerability.

All we have to do is find the offset of the function pointer on the heap, just as we did for some of the previous levels. Using gdb, we launch the program with a changing parameter size until we find the offset of our pointer to function. It appears tha the offset is 72 bytes.

All that remains is to forge the parameter passed to the program: the address of the n() function (0x08048454) must be passed according to the little endian convention after 72 padding characters:

```
level6@RainFall:~$ ./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```
We can now reach to the next level with the command `su level7` and fill in the flag found as a password.