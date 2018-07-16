#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 512  /* The length of the string */

int inputCheck (float,float, float,char[]);
int my_bcmp(const void *, const void *, size_t);
int isInt (float f);

/* The program gets 4 inputs - 3 float: length (integer and non-negative) & 2 indexes
 * (integer and non-negative, and valid indexes of the string).
 * And a string (max length is 512 chars. If more than 512 chars are inserted,
 * the input will be the first 512 chars).
 *
 * The program checks the validity of the inputs. If something is wrong - it will print the error and will exit with erro code 1.
 * In the first steps, the validity check is just if the type of the inputs is valid (checks after every input).
 * after the all inputs are stored in vars, the second validity check will check if:
 * 1. Indexes and len are non-negative and integer.
 * 2. Every index+len are in the range of memory (MAX_LEN bytes from str[0]).
 * 3. Indexes are into the range of the string.
 * If something is wrong - The appropriate errors will printed, and the program will exit with error code 1.
 * If the inputs are valid, the program will check if the memory segmets are equals (it compares the memory
 * segment- len bytes from str[i1] to memory segment len bytes from str[i2].
 * If the program succeed, it prints the answer and returns 0.*/

int main()
{
    float i1 = -1;
    float i2 = -1;
    float len = -1;
    int scanres;
    char str[MAX_LEN];
    int c;
    printf("**********Welcome to my_bcmp program!**********\n\nThe program gets a string, 2 indexes & a number (len),\nand checks if"
           " the memory segments from each index are equals (len bytes from any index).\n");
    printf("\nPlease insert the number of bytes to check.\n"
                   "The length must be an integer and non-negative,\nand the mximum bytes are %d (minus each index):", MAX_LEN);
    scanres = scanf("%f", &len); /* gets the length */
    if (!scanres) /* check if the input is a valid float */
    {
        printf("\nError! This is not a valid number.\n");
        exit(1); /* The input is not a valid float */
    }
    printf("\n\nPlease insert the first index.\nThe index must be an integer an non-negative:");
    scanres = scanf("%f", &i1); /* gets the first index */
    if (!scanres) /* check if the input is a valid float */
    {
        printf("\nError! This is not a valid number.\n");
        exit(1);
    }
    printf("\n\nPlease insert the second index.\nThe index must be an integer an non-negative:");
    scanres = scanf("%f", &i2); /* gets the second index */
    if (!scanres) /* check if the input is a valid float */
    {
        printf("\nError! This is not a valid number.\n");
        exit(1);
    }
    printf("\n\nPlease insert a string (Max length = %d):",MAX_LEN);
    while (isspace(c = getchar()) && c != EOF){}/* Clean the buffer */
    if (c != EOF)
        ungetc(c,stdin);
    scanres = scanf("%512[^\n]", str); /* gets the string */
    if (!scanres) /* check if the string is not empty */
    {
        printf("\nError! You didn't enter a string.\n");
        exit(1);
    }
    if (!inputCheck(i1,i2,len,str)) /* check if all the inputs are valid for the program */
        exit(1); /* error, one value or more are not valid */
    printf("\nThe values you entered:\nThe string: %s\nThe First index: %d.\nThe second index: %d."
           "\nThe length is: %d\n",str,(int)i1,(int)i2,(int)len); /*print the inputs */
    if (!my_bcmp(&str[(int)i1], &str[(int)i2], (int)len)) /* check if the bytes are equals */
        printf("The memory segments are equals.\n"); /* the memory segments are equals */
    else
        printf("The memory segments are not equals.\n"); /* not equals */
    return 0;
}

/* The func gets 2 pointers (b1, b2) and a non-negative len
 * and return 0 if the memory segments (the length of the segments: len bytes) from each pointer.
 * Returns 1 if the segments are not equals.*/
int my_bcmp(const void *b1, const void *b2, size_t len)
{
     char *p1 = (char *)b1; /* convert the void pointers to char pointers - to scan 1 byte each time */
     char *p2 = (char *)b2;
     int i;
     if (len == 0) /* if len == 0 the segments are always equals */
         return 0;
     for(i=0;i<len;i++)
     {
         if (p1[i] != p2[i]) /* if there is one byte that is not equal, the segments are not equal - return 0 */
             return 1;
     }
     return 0; /* segments are equals */
}

/*
 *  The func check if the input is valid for the program.
 *  Checks:
 *  1. Indexes and len are valid (non-negative and integer).
 *  2. Every index+len are in the range of memory (MAX_LEN bytes).
 *  3. Indexes are in the range of the string.
 *
 *  If valid - return 1. Else - 0.
 */
int inputCheck (float i1, float i2, float len,char s[])
{
    int flag = 1; /*flag is 1 if there are no errors, and 0 if there are */
    int slen = strlen(s);

    if (!isInt(i1)) /* if i1 is non-negative or integer will report error*/
    {
        puts("\nError! The first index is not an integer or non-negative.\n");
        flag = 0;
    }
    else /* i1 is valid */
    {
        if (i1 > (slen - 1))  /*i1 is valid but is out of the range of the string*/
        {
            puts("\nError! The first index is out of range.\n");
            flag = 0;
        }
        if ((i1+len) >= MAX_LEN) /* if i2+len is out the range of memory (MAX_LEN bytes) will report error*/
        {
            printf("\nError! The num of bytes + first index exceed the maximum of bytes (%d).\n", MAX_LEN);
            flag = 0;
        }
    }
    if (!isInt(i2)) /* if i2 is non-negative or integer will report error*/
    {
        puts("\nError! The second index is not an integer or non-negative.\n");
        flag = 0;
    }
    else  /* i2 is valid */
    {
        if (i2 > (slen -1)) /*i2 is valid but is out of the range of the string*/
        {
            puts("\nError! The second index is out of range.\n");
            flag = 0;
        }
        if ((i2+len) >= MAX_LEN) /* if i2+len is out the range of memory (MAX_LEN bytes) will report error*/
        {
            printf("\nError! The num of bytes + second index exceed the maximum of bytes (%d).\n", MAX_LEN);
            flag = 0;
        }
    }

    if (!isInt(len)) /* if len is non-negative or integer will report error*/
    {
        puts("\nError! The length is not an integer or non-negative.\n");
        flag = 0;
    }
    return flag; /* return if there are errors (flag == 0 - error, flag == 1 - no errors) */
}

/*
 * The func gets a float f and return 1 if it is non-negative integer (accuracy - 0.00001).
 * Else -return 0.
 */
int isInt (float f)
{
    int num= (int)f; /*convert to int */
    if ((f - (float)num) < 0.00001 && f>=0)  /*check if the float equals to int (accuracy=0.00001) and the float is non-negative */
        return 1;
    return 0;
}

