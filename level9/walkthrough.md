As for the previous exercises, we have a level9 executable. With or without parameters, the program does nothing in appearance. Thanks to the ltrace command, we learn a little more about the program. First of all, the presence of symbols belonging to the libc++ library tells us that the source code was written in C++. We also learn that the program exits with a status of 1 if no argument is given. Finally, we can see that the string passed in parameter is recorded at 0x0804a00c using the memset() function.

We are getting used to it, we will probably have to perform a buffer overflow attack to exploit this binary file. Since there is no call to `system("/bin/sh")` in the code, and the .pass file is not read, we will have to write a shellcode. We will use the shellcode from level2.

There is a window of opportunity for us to exexute the shellcode at main+159: a call is made to whatever function edx is pointing to. So at main+159, edx must contain the address of our shellcode. We need to go back into the assembly code to find what we need to overwrite with our buffer overflow attack and how to craft our input. edx is defined at main+142 as whatever is pointed by eax, so what we want to overwrite is eax. As the variable is dereferenced twice, eax must point to an address that points to our shellcode.

Let's start by finding out when a segmentation fault occurs. After some tests using gdb, we find that the program crashes with a parameter of more than 108 characters. We can now build our input: the address of our shellcode (4 bytes: 0x0804a00c + 4 = 0x0804a010), followed by the shellcode itself (21 bytes), followed by some padding (108 - 4 - 21), followed by the address of the begining of our input (0x0804a00c). And we should be good!

```
level9@RainFall:~$ ./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80" + "A" * 83 + "\x0c\xa0\x04\x08"')
$ whoami
bonus0
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```
We can now reach to the next level with the command `su bonus0` and fill in the flag found as a password.