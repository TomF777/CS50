// print strings/char with pointer arithemtic

//#include <cs50.h>
#include <stdio.h>

int main(void)
{

    //string s = "HI!";           // in fact  its char *s = "HI!"
    char *s = "HI!";
    printf("%s\n", s);
    printf("%p\n", s);
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);

    printf("%c", *s);
    printf("%c", *(s+1));
    printf("%c\n", *(s+2));

}
