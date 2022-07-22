## Context

The program has only a main() function and expects 1 parameter. First, the content of the file `/home/user/end/.pass` is read and stored in a buffer using fopen() and fread(). The numerical value of the parameter is then retrieved with atoi(), and a '\0' is placed in the buffer with an offset of that value. Finally, a comparison is made between this value and the buffer with strcmp(). If strcmp() returns 0, then a shell is launched. Otherwise, buf is displayed on the standard output. 

## Lead

Since there is no way for us to perform a buffer overflow attack, we quickly discard the idea of displaying the contents of the buffer and concentrate on the call to execvl().

## Exploit

The solution is actually quite simple: we just need to give an empty parameter. This way, atoi() will return 0, buf[0] will be set to '\0' and the comparison between av[1] and buf will return 0:
```
bonus3@RainFall:~$ ./bonus3 ""
$ whoami
end
$ cat /home/user/end/.pass
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
```