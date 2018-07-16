#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define CHAR_BITS (sizeof(char)*8)
#define GROUP_SIZE 128
#define CHAR_SIZE (GROUP_SIZE/CHAR_BITS)



typedef struct  {
    char members[CHAR_SIZE];
} Set;

void read_set (Set *, int[]);
void print_set(Set *, char *);
void union_set(Set *, Set *, Set *);
void intersect_set (Set *, Set *, Set *);
void sub_set (Set *, Set *, Set *);
void stop();





