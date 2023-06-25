#include <string.h>
#include <stdbool.h>
#include <stdio.h>

bool is_palindrome(char* s)
{
    char string[strlen(s) + 1];

    // copy only numbers and letters converted to uppercase to new string
    char* string_p = &string[0];
    for (char* c = s; *c; c++)
    {
        if (*c >= 'a' && *c <= 'z') *string_p++ = *c - 32; // convert lower to upper
        else if (*c >= 'A' && *c <= 'Z') *string_p++ = *c;
        else if (*c >= '0' && *c <= '9') *string_p++ = *c;
    }

    *string_p-- = 0; // null terminate

    char* string_start = &string[0];

    while (string_start < string_p)
        if (*string_start++ != *string_p--)
            return false;
    
    return true;
}

int main()
{
    char string1[] = "rac ecar";
    printf("%d\n", is_palindrome(string1) ? 1 : 0);

    char string2[] = "rac ecars";
    printf("%d\n", is_palindrome(string2) ? 1 : 0);

    char string3[] = "A man, a plan, a canal: Panama!";
    printf("%d\n", is_palindrome(string3) ? 1 : 0);

    return 0;
}
