// copy string and capitalize its 1st letter. Original string remains unchanged

#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>                                     // for malloc() and free()

int main(void)
{
    char *s = get_string("s: ");
    if (s == NULL)
    {
        return 1;
    }

    char *t = malloc(strlen(s) + 1);                    // reserve memory area; malloc return address of the 1st character in the memory
    if (t == NULL)
    {// abort the program when there is no enough memory for t declaration
        return 1;
    }


    //for (int i = 0, len = strlen(s); i <= len; i++)     // copy also '\0'
    //{
    //    t[i] = s[i];
    //}

    // the above code snippet can be realized with strcpy
    strcpy(t, s);

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("%s\n", s);
    printf("%s\n", t);

    // release memory reserved by malloc()
    free(t);
    return 0;
}
