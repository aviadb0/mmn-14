#include "set.h"

#define MAX_LEN_CM 14
#define MAX_INPUT 81
#define PARAM_NAME 4
#define PARAM_NUM 6
#define MAX_NUMS 80
#define NUM_OF_PARAM 3
#define STOP_LEN 4
#define STOP_POS 5

void readIn(char *);
void printIn (char *);
void subIn (char []);
void unionIn (char []);
void intersectIn (char []);
void stopIn (char []);
int getLine(char *, int);
int findComma (char *);
int getNum(char *, int[], int);
int findParam (char *);
int findExtra (char *);
void runSubInterUnion (char *, void (*)(Set *,Set *, Set *));


struct {
    char *name;
    void (*func)(char[]);
} cmd[] = {
        {"read_set", readIn},
        {"union_set", unionIn},
        {"print_set", printIn},
        {"intersect_set", intersectIn},
        {"sub_set", subIn},
        {"stop", stopIn},
        {"not valid", NULL}
};

struct {
    char *name; /* +1 for '/0' */
    Set group;
} parameter[] = {
        {"SETA", {{0}}},
        {"SETB", {{0}}},
        {"SETC", {{0}}},
        {"SETD", {{0}}},
        {"SETE", {{0}}},
        {"SETF", {{0}}}
};


/*
 * myset program - The programs gets lines of commands from stdin, to control a 6 groups of number (number between 0 to 127).
 * every line is analyzed - if there is an error - its print it and continune the prog whithout doing anything.
 * If its a valid command - the progra do the action that asked.
 * The rules:
 * *max length of every line: 80.
 * *first chars are the command (exclude blanks).
 * *after the command comes the parameters.
 * *no comma between the command and parameter.
 * *every command has other nums of parameters.
 * *if there are more parameters than 1, parameters are separated by comma.
 * * no extra chars after the end of commands (exclude blanks).
 * * EOF is not allowed. the program stop with the command 'stop' (EOF after stop is valid).
 * The commads:
 * ****read_set - 1 parameter, a comma and a list of nums (separated by comma). the last number must be -1.
 * The command put the list of num in the group that entered. (every num can appears more than one appearance).
 * EXm.: read_set SETA 0, 1, 10, -1
 * ****print_set - 1 parameter.
 * The command print the list of num in the group that entered.
 * Exm.: print_set SETA
 * ****union_set - 3 paramete
 * put the union of SETA & SETB in SETC.
 * EXm.: union_set SETA,SETB,SETC
 * ****intersect_set - 3 paramete
 * put the intersect of SETA & SETB in SETC.
 * EXm.: intersect_set SETA,SETB,SETC
 * ****sub_set - 3 paramete
 * put the nums of SETA that doesn't in SETB in SETC.
 * EXm.: sub_set SETA,SETB,SETC
 * ****stop - no parameter
 * stops the program.
 *
*/
int main()
{
    char s[MAX_INPUT];
    int i, cmdlen, funcI, len, c;
    printf("*****Welcome to myset program!*****\n\nThe program contains %d groups of numbers (SETA, SETB, etc.), from 0 to %d.\nYou can write commands to control the groups.\n"
           "The commands are:\n***read_set SETA - add to the group SETA the numbers (separated by one comma) after the command (terminated by -1). Max numbers: %d\n"
           "***print_set SETA - print the numbers in the group SETA.\n***union_set SETA,SETB,SETC - put the union of SETA & SETB in SETC.\n",PARAM_NUM ,(GROUP_SIZE-1),MAX_NUMS);
           printf("***intersect_set SETA,SETB,SETC - put the intersect of SETA & SETB in SETC.\n***sub_set SETA,SETB,SETC - put the nums of SETA that doesn't in SETB in SETC.\n"
           "***stop - stop the program.\n\nMultiple commas or comma between the command and parameter are disallowed.\nExtra text after the end of command is disallowed.\n"
           "The limit of every line is %d chars.\n", (MAX_INPUT-1));
    for(;;)
    {
        printf("\n~");
        i=0;
        len = getLine(s,MAX_INPUT);
        if(len == 0)   /* gets a new line and checks if it empty */
            continue;
        if (len == -1) /* no newline (found EOF) */
        {
            while (i<len && isspace(s[i])) /* skip blanks */
                i++;
            if ((strncmp(s,"stop", STOP_LEN) == 0) && findExtra(&s[i+ STOP_LEN])) /* check if 'stop' command detected */
                stop();
            else
            {
                printf("Error! EOF. 'stop' command is missing\n");
                exit(1);
            }
        }
        printf("\n%s\n", s); /* print the command */
        if (len == -2) /* exceeded the limit */
        {
            printf("Error! The line you entered is too long. The limit is %d chars.\n", MAX_INPUT-1);
            while ((c = getchar()) != '\n' && c != EOF) {} /* skip the otehr chars in the line */
            continue;
        }
        while (i<len && isspace(s[i])) /* skip blanks */
            i++;
        for (funcI = 0; cmd[funcI].func!=NULL;funcI++) /* to find the command */
        {
            cmdlen = strlen(cmd[funcI].name);
            if (strncmp(&s[i],cmd[funcI].name, cmdlen) == 0) /* if the command was detected, stop the loop */
                break;
        }
        if (cmd[funcI].func == NULL) /* command isn't valid */
            printf("Error! Undefined command name\n");
        else /* valid command */
        {
            i+=cmdlen; /* to promote the index to after the command */
            if (i < len && !isspace(s[i])) /* find space after command */
            {
                if (s[i] == ',') /* found illegal comma */
                    printf("Error! Illegal comma\n");
                else /* extra chars after the command, the command is not valid */
                    printf("Error! Undefined command name\n");
            }
            else if (i==len && funcI == STOP_POS) /* stop command was determined, no need more space in the line */
                stop();
            else if (i >= len) /* the line end exact after the command, no parameter */
                printf("Error! Missing parameter\n");

            else /* there is a command */
                (*(cmd[funcI].func))(&s[i]); /* call the right function */
        }

    }
}

/*
 * Do the extra checks for the read_set command.
 * Check if there is one valid parameter, and list of numbers in the range terminated by -1.
 * If the command is ok, call the func read_set.
 */
void readIn(char *s)
{
    int i = 0, len, temp, paramIndex, i2 = 0;
    int nums[MAX_NUMS];
    len = strlen(s);
    while (i<len && isspace(*(s+i))) /* skip blanks */
        i++;
    if (i< len && s[i] == ',') /* check illegal comma before set name */
    {
        printf("Error! Illegal comma\n");
        return;
    }
    if ((paramIndex = findParam(&s[i])) < 0) /* missing parameter */
    {
        return;
    }
    i += PARAM_NAME;
    if (i < len && !(isspace(s[i]) || s[i] == ',' || s[i] == '\0')) /* Wrong parameter name */
    {
        printf("Error! Undefined set name\n");
        return;
    }
    if (i >= len) /* list of numbers is missing */
    {
        printf("Error! List of set members is missing\n");
        return;
    }
    do
    {
        if ((temp = findComma(&s[i])) < 0)  /* didn't found a comma */
        {
            printf("Error! Missing comma\n");
            return;
        }
        i += temp;      /* skip the checked indexes */
        if (findComma(&s[++i]) >= 0) /* found second comma */
        {
            printf("Error! Multiple consecutive commas\n");
            return;
        }
        temp = getNum(&s[i], nums, i2); /*gets the new num */
        switch (temp)
        {
            case -1: /* no -1 in the end */
                printf("Error! List of set members is not terminated correctly\n");
                return;
            case -2: /* not an integer */
                printf("Error! Invalid set number - not an integer\n");
                return;
            case -3: /* out of range */
                printf("Error! Invalid set number - out of range\n");
                return;
        }
        i += temp;  /* skip the checked indexes */
        i2++;
    } while(i2 < MAX_NUMS && nums[i2-1] != -1); /*stops if more nums than MAX_NUMS were entered or -1 was detected */
    if (i2 == MAX_NUMS) /* more than MAC_NUMS */
    {
        printf("Error! Too many set members\n");
        return;
    }
    if (findExtra(&s[i]) < 0)    /* found a char after the end of command */
    {
        printf("Error! Extraneous text after end of command\n");
        return;
    }
    read_set(&(parameter[paramIndex].group) ,nums);
}

/*
 * Do the extra checks for the print_set command.
 * If the command is ok, call the func.
 */
void printIn (char *s) {
    int i = 0, len, paramIndex;
    len = strlen(s);
    while (s[i] != '\0' && isspace(*(s+i))) /* skip blanks */
        i++;
    if (i< len && s[i] == ',') /* check illegal comma before set name */
    {
        printf("Error! Illegal comma\n");
        return;
    }
    if ((paramIndex = findParam(&s[i])) < 0) /* missing parameter */
    {
        return;
    }
    i += PARAM_NAME;
    if (i < len && !(isspace(s[i]) || s[i] == ',' || s[i] == '\0'))
    {
        printf("Error! Undefined set name\n");
        return;
    }
    if (findExtra(&s[i]) < 0)    /* found a char after the end of command */
    {
        printf("Error! Extraneous text after end of command\n");
        return;
    }
    print_set(&(parameter[paramIndex].group),parameter[paramIndex].name);
}

/*
 * call the func for 3 sets.
*/
void subIn (char s[])
{
    runSubInterUnion(s,sub_set);
}

/*
 * call the func for 3 sets.
*/
void unionIn (char s[])
{
    runSubInterUnion(s,union_set);
}

/*
 * call the func for 3 sets.
*/
void intersectIn (char s[])
{
    runSubInterUnion(s,intersect_set);
}

/*
 * check if its valid stop command - ext the program.
*/
void stopIn (char s[])
{
    if (findExtra(s) < 0) /* found a char after the end of command */
    {
        printf("Error! Extraneous text after end of command\n");
        return;
    }
    stop();
}

/*
 * do the extra checks for functions with 3 sets.
 * if the command is ok, called the appropriate func.
 */
void runSubInterUnion (char *s, void (*func)(Set *,Set *, Set *))
{
    int i = 0, len, temp, paramI[NUM_OF_PARAM], index;
    len = strlen(s);
    while (i<len && isspace(*(s+i))) /* skip blanks */
        i++;
    if (i< len && s[i] == ',') /* check illegal comma before set name */
    {
        printf("Error! Illegal comma\n");
        return;
    }
    for (index = 0; index < NUM_OF_PARAM;index++)
    {
        while (i<len && isspace(*(s+i))) /* skip blanks */
            i++;
        if ((paramI[index] = findParam(&s[i])) < 0) /* missing parameter */
            return;

        i+=PARAM_NAME;
        if (index < (NUM_OF_PARAM - 1))
        {
            if ((temp = findComma(&s[i])) < 0)  /* didn't found a comma */
            {
                printf("Error! Missing comma\n");
                return;
            }
            i += temp;      /* skip the checked indexes */
            if (findComma(&s[++i]) >= 0) /* found second comma */
            {
                printf("Error! Multiple consecutive commas\n");
                return;
            }
        }
    }
    if (findExtra(&s[i]) < 0) /*there is extraneuous text after the command */
    {
        printf("Error! Extraneous text after end of command");
        return;
    }
    (*(func))(&(parameter[paramI[0]].group),&(parameter[paramI[1]].group),&(parameter[paramI[2]].group));
}




/*
 * return the index of the last char in the string if the string is empty (include just blanks).
 * return -1 if other char detected.
 */
int findExtra (char *s)
{
    int i = 0;
    while (s[i] != '\0') /* check extraneous text */
    {
        if (!isspace(s[i]))    /* found a char after the end of command */
            return -1;
        i++;
    }
    return i;
}



/*
 * The func find in the array if the first chars are a parameter's name and return
 * the index of the parameter in parameter[];
 * Else, it will print the right error and return -1.
 */
int findParam (char *s) {
    int len, paramIndex;
    len = strlen(s);
    if (len < PARAM_NAME) /* the string is too short to be a parameter */
    {
        printf("Error! Missing parameter\n");
        return -1;
    }
    for (paramIndex = 0; paramIndex < PARAM_NUM; paramIndex++)  /* finds if there is a valid parameter */
    {
        if (strncmp(s, parameter[paramIndex].name, PARAM_NAME) == 0) /* if parameter was found - exit the loop */
            break;
    }
    if (paramIndex == PARAM_NUM)  /* parameter didn't found */
    {
        printf("Error! Undefined set name\n");
        return -1;
    }
    return paramIndex;  /* parameter found, return the index of the valid parameter */
}

/*
 * The func get a new line from the stdin. The line is limited by (cnt-1) chars.
 * Returns the len of the new line. If there is no newline char from the stdin (EOF), returns -1.
 * Returns -2 if the the input chars are exceeded the limit (more than cnt-1).
 */
int getLine(char s[], int cnt)
{
     int len, i = 2, count = 0;
     char *test;
     test = fgets(s,cnt,stdin);
     if (test == NULL) /* EOF detected */
         return -1;
     len = strlen(s);
     if (s[len-1] != '\n')
         return -2; /* the input chars are exceeded the limit (cnt-1) */
     s[len-1] = '\0'; /* delete the newline  */
     while (i<=len && isspace(s[len - i])) /* check if there are blank indexes from the end  */
     {
         s[len - (i++)] = '\0'; /* remove blank index from the end  */
         count++; /* count the num of the removed indexes */
     }
     return (len-(count+1)); /* return the len of s  */
}


/*
 * Finds if the next char (exclude blanks) is a comma, and returns its index.
 * If it's not a comma, returns -1. If the last of the string is empty, return -2.
 */
int findComma (char *s)
{
    int i = 0, len;
    len = strlen(s);
    while (i < len && isspace(s[i]))
        i++;
    if (i == len) /* no char was found  */
        return -2;
    if (s[i]!=',') /* isn't a comma  */
        return -1;
    else
        return i;


}
/*
 * Finds if the firsts chars in a string are a number in the range - 0 to 127. if it is: put it in nums[index] and return
 * the index of the one char after the num..
 * If the last number n the array is not -1, returns -1.
 * if the char after the num is not a space or , or \0 or if there is no number - return -2.
 * If not in range - return -3.
 */
int getNum(char *s, int nums[], int index)
{
    int i, len, temp=0, start = 0, sign = 1;
    len = strlen(s);
    while (start < len && isspace(s[start]))  /* skip blanks */
        start++;
    if (s[start] == '-') /* check if negative  */
    {
        sign = -1;
        start++;
    }
    i = start;
    while (i < len && isdigit(s[i]))  /* add the digit to the num  */
    {
        temp *= 10;
        temp += (s[i] - '0');
        i++;
    }
    temp *= sign;
    if (i == len && temp != -1)   /* end of the string and not -1 */
        return -1;
    if (start == i || !(isspace(s[i]) || s[i] == ',' || s[i] == '\0')) /* no num was found or s[i] is not a valid char after a number */
        return -2;
    if (temp < -1 || temp >= GROUP_SIZE) /* not in the range  */
        return -3;
    nums[index] = temp;
    return i;
}

