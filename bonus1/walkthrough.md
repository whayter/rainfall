## Context

The program ends with a segmentation fault when no parameter is given. Looking in more detail, we see that the program expects two parameters. The numerical value of the first argument is retrieved using atoi() and stored in a variable n. If n is less than or equal to 9, then a number of characters up to n * 4 are copied from the second parameter to a buffer using memcpy(). Finally at this stage of the program, if n is equal to 0x574f4c46 (1464814662 in decimal), then a shell is launched with the command execl().

## Lead

Since n and buf have concomitant memory spaces on the stack, we naturally think of overflowing the buffer when calling memcpy() to write to n. The problem is that the size of the buffer (40) is greater than the maximum number of characters that can be written with memcpy(), since the function is only called if n is less than or equal to 9, which allows a maximum of 9 * 4 = 36 characters.

But there is a way to do it: signed integers are stored on 32 bits, according to the sign magnitude method, i.e. the most significant digit represents the sign of the integer (0 for positive, 1 for negative). Tthe range of numbers that can be represented is therefore between -2<sup>32-1</sup> to +(2<sup>32-1</sup> -1) (-2147483648 to +2147483647). Here are some examples:

+            1: 00000000 00000000 00000000 00000001
+   2147483647: 01111111 11111111 11111111 11111111
-   2147483648: 10000000 00000000 00000000 00000000
-   2147483647: 10000000 00000000 00000000 00000001

Attempting to record a value outside the range would result in an erroneous result, since there would be a lack of bits to represent it. For example, 2147483648 is 10000000 00000000 00000000 00000000 in 32 bits binary, but the most significant digit is interpreted as the sign and the program returns the value -2147483648.

To come back to the program, we will be able to exploit what we have just talked about to write more than 36 bytes in the buffer with memcpy(). By giving n a negative value, we respect the condition that n must be less than or equal to 9. When calling memcpy(), if n * 4 is out of range (i.e. less than -2147483648), then the result will be a positive value. 

Since the buffer has a size of 40 bytes, and n has a size of 4 bytes, we want to be able to write 44 bytes to the buffer. To do this we need to pass as the first argument -2147483648 - (44 / 4), which is -2147483637. It only remains to fill the buffer with 40 bytes of padding, then to pass the value 0x574f4c4 in the little endian convention.

## Exploit

```
bonus1@RainFall:~$ ./bonus1 -2147483637 $(python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"')
$ whoami
bonus2
$ cat /home/user/bonus2/.pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```
We can now reach to the next level with the command `su bonus2` and fill in the flag found as a password.