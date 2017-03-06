#ifndef _SEQLIB_H
#define _SEQLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


/*! \file seqlib.h
    \brief Array related functions descriptions.
    \author Alexis Devillard
    \version 1.0
    \date 25 february 2017
*/


/*! \fn void dispArray(int* A,int n);
    \brief Display array.
    \param A The array to dsplay.
    \param n The lenght of the array to dsplay.
    
*/
typedef struct _Nuc{//the structure to sort
	char nucleo1; /**< nucleotide 1 */
	char nucleo2; /**< nucleotide 2 */
	struct _Nuc* next;
	
}Nucleotides;

typedef struct _Seq{//the structure to sort
	int sizeX; /**< size of sequence X */
	int sizeY; /**< size of sequence Y */
	char* seqX; /**< sequence X */
	char* seqY; /**< sequence Y */
	Nucleotides * M;/**< The optimal alignement between se X and Y */
	int lenght;/**< The size of the optimal alignement between se X and Y */
	int errors;/**< The number of un-matching nucleotides in the optimal alignement between se X and Y */
	int gaps;
}Seq;



Seq* getSeq(char * path);
int **COUT1(Seq *S);

int COUT2(Seq *S,int m,int n,int* min);
int min(int n1,int n2,int n3);
Nucleotides* SOL1(Seq *S,int** F);
void addPair(Nucleotides* N,char x,char y);
void dispNucleotides(Nucleotides* N);


#endif
