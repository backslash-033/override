#include <stdio.h>

int main(int argc, const char **argv, const char **envp)
{
    char str[100];
    unsigned int i;

    i = 0;
    fgets(str, 100, stdin);
    for ( i = 0; i < strlen(str); ++i )
    {
        //  0x41 'A'     0x5a 'Z'
        if (str[i] > 65 && str[i] <= 90)
            str[i] ^= 0x20;
    }
    printf(str);
    exit(0);
}