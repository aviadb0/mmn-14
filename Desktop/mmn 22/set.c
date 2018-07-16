#include "set.h"

/*
 * The read_set func - turn on the bits in the right places (every bit represent 1 num).
 * 1 is in the group, 0 is not.
 * To turn on the bit, using a mask.
 */
 void read_set (Set *A, int num[])
 {
      int mask;
      int i = 0;
      while (num[i] != -1) /* stops if -1 is found */
      {
          mask = 1 << (num[i] % CHAR_BITS); /* create the mask. num%CHAR_BITS return the position of the bit in the right byte. */
          A->members[num[i]/CHAR_BITS] |= mask; /* 'or' command turn on the right bits. num/CHAR_BIT return the right byte.*/
          i++;
      }

 }
/*
 * The union_set func - put the union of A & B to C.
 * Put A | B in C (every byte).
 */
 void union_set(Set *A, Set *B, Set *C)
 {
    int i;
    for (i = 0; i < CHAR_SIZE; i++)
    {
        C->members[i] = A->members[i] | B->members[i];
    }
 }

 /*
 * The intersect_set func - put the intersect of A & B to C.
 * Put A & B in C (every byte).
 */
 void intersect_set (Set *A, Set *B, Set *C)
 {
     int i;
     for (i = 0; i < CHAR_SIZE; i++)
     {
         C->members[i] = A->members[i] & B->members[i];
     }
 }

/*
 * The sub_set func - put the nums that in A and not in  B, to C.
 * Put (A & ~B) in C (every byte).
 */
 void sub_set (Set *A, Set *B, Set *C)
 {
     int i = 0;
     for (i=0;i<CHAR_SIZE;i++)
     {
         C->members[i] = A->members[i] & ~(B->members[i]);
     }

 }

/*
 * stop the program
 */
 void stop()
 {
    exit(0);
 }

 /*
  *
 * The print_set func - print the nums that are in A,
  */
 void print_set(Set *A, char *name)
 {
     int temp, flag = 0;
     unsigned int mask = 1;
     int i;
     for(i=0;i<CHAR_SIZE;i++) /* Check if the set is empty */
     {
         if (A->members[i] != 0)
             flag = 1;
     }
     if (flag == 0) /* empty */
     {
         printf("\nThe set is empty\n");
         return;
     }
     i = 0;
     printf("\nThe set members of %s are:\n",name);
     while (i < GROUP_SIZE) /* check every num between 0 and GROUP_SIZE */
     {
         mask = 1 << (i % CHAR_BITS); /* create the mask. i%CHAR_BITS return the position of the bit in the right byte. */
         temp = A->members[i/CHAR_BITS] & mask; /*i/CHAR_BIT return the right byte.*/
         if (temp != 0) /* check if the i bit is turn on - print it */
             printf("%d\n",i);
         i++;
     }
 }