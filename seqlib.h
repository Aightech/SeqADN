#ifndef _SEQLIB_H
#define _SEQLIB_H


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

typedef struct _Seq{//the structure to sort
	int sizeX; /**< size of sequence X */
	int sizeY; /**< size of sequence Y */
	char* seqX; /**< sequence X */
	char* seqY; /**< sequence Y */
}Seq;

Seq* getSeq(char * path);


#endif
