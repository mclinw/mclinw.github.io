/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

  // reverse("abc") -> "cba"
char* reverse(char *str) // reverse string
{
    char *begin, *end;
    char tmp;

    if (!str) return str;
    unsigned int len = strlen(str);
    for (begin = str, end=str+len ; begin<end ; begin++,end--) {
        /*swap*/
        tmp = *begin;
        *begin = *end;
        *end = tmp;
    }
    return str;
}

  // atoi("1") -> 1
int myatoi(char *str)//convert string to integer
{
    // todo : handle negative int
    int num = 0;
    char *p = str;
    int m = 1;
    if(!p) return 0;//error handle
    if(*p == '-') {
        ++p;
        m = -1; // negative
    }
    while(*p != '\0') {
        num *= 10;
        num += *p++ - '0';
    }
    return (m < 0) ? num * m : num;
}

char* uitoa(unsigned int ui, char *a)
{
    // const int m = 10;
    // int i = 0 ;
    /* buffer for reversed string */
    char rev_a[10/*32BIT_UINT_MAX_STR_LENGTH*/+1];
    char *ra = rev_a;
    char *cp = a;
    *ra++ = '\0';
    /* build reversed ui string */
    do {
        *ra++ = '0' + (ui % 10);      
        ui /= 10;
        // if(++i==m) {
        //     printf("exception %d %s" , i,rev_a) ;
        //     break;
        // }
    } while (ui);

    /* return reversed ui string back to correct order */
    do {
        *cp++ = *--ra;
    } while (ra > rev_a);
    return a;
}

/* integer to decimal string */
char* itoa(int i, char *a)
{
    unsigned int ui = i;
    char *p = a;
        
    /* consider if i is negative */
    if (i < 0) {
        *p++ = '-';
        ui = -i;
    }
    uitoa(ui, p);
    return a;
}

int main()
{
    char str [] =  "Hello World";
    // printf( "%d\n", myatoi("123"));
    // printf( "%d\n", myatoi("-456"));
    // printf( "%d\n", myatoi("0"));
    // printf( "%d\n", myatoi(""));

    char buf[10/*32BIT_UINT_MAX_STR_LENGTH*/+1];
    // printf("%s" , str) ;
    // printf( "%s\n", uitoa(0, buf));
    // printf( "%s\n", uitoa(1, buf));
    // printf( "%s\n", uitoa(12, buf));

    printf( "%s\n", itoa(0, buf));
    printf( "%s\n", itoa(1, buf));

    printf( "%s\n", itoa(-1, buf));
    printf( "%s\n", itoa(INT_MIN, buf));

    printf( "%s\n", itoa(INT_MAX, buf));
    return 0;
}
