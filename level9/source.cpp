#include <cstring>
#include <unistd.h>
#include <iostream>

class N
{
    private:
    
        int _n;
        char _s[100];

    public:

        N(int n): _n(n) {}						// 0x080486f6

        void setAnnotation(char* s) {			// 0x0804870e
            memcpy(_s, s, strlen(s));
        }

        int operator+(N& other) {				// 0x0804873a
            return _n + other._n;
        }

        int operator-(N& other) {				// 0x0804874e
            return _n - other._n;
        }
};

int main(int ac, char** av)
{
    if (ac < 2)                     			// main+10 - main+23
        _exit(1);
    N* a = new N(5);                			// main+28 - main+58
    N* b = new N(6);                			// main+62 - main+92
    a->setAnnotation(av[1]);        			// main+112 - main+131
	int res = *a + *b;							// main+136 - main+159
    return res;									// main+161 - main+165
}