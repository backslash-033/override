#include <stdio.h>

int main(int argc, const char **argv, const char **envp)
{
    char s[100]; // [esp+28h] [ebp-70h] BYREF
    unsigned int i; // [esp+8Ch] [ebp-Ch]

    i = 0;
    fgets(s, 100, stdin);
    for ( i = 0; i < strlen(s); ++i )
    {
        //  0x41 'A'     0x5a 'Z'
        if (s[i] > 65 && s[i] <= 90)
            s[i] ^= 0x20;
    }
    printf(s);
    exit(0);
}