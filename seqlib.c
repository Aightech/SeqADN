#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "seqlib.h"

Seq* getSeq(char * path) 
{
	FILE* file=NULL;
	file=fopen(path,"r");
	
	Seq* seq=(Seq*)malloc(sizeof(Seq));
	
	char ch=fgetc((FILE*)file);
	int i;
	//find the size of the sequences
	int sizeX=0;
	int sizeY=0;
	while(ch!='\n')
	{
		sizeX=sizeX*10+ch-'0';
		//printf("%c\n",ch);
		ch=fgetc((FILE*)file);
		
	}

	ch=fgetc((FILE*)file);
	while(ch!='\n')
	{
		sizeY=sizeY*10+ch-'0';
		//printf("%c\n",ch);
		ch=fgetc((FILE*)file);
	}
	printf("x: %d |y: %d\n",sizeX, sizeY );
	seq->sizeX=sizeX;
	seq->sizeY=sizeY;
	seq->seqX=(char*)malloc((sizeX+1)*sizeof(char));
	seq->seqY=(char*)malloc((sizeY+1)*sizeof(char));
	for(i=0;i<sizeX;i++)
	{
		ch=fgetc((FILE*)file);
		fgetc((FILE*)file);
		seq->seqX[i]=ch;
		//printf("%c\n",ch);
	}
	seq->seqX[sizeX]='\0';
	fgetc((FILE*)file);
	for(i=0;i<sizeY;i++)
	{
		ch=fgetc((FILE*)file);
		getc((FILE*)file);
		seq->seqY[i]=ch;
		//printf("%c\n",ch);
	}
	seq->seqY[sizeY]='\0';
	printf("X={%s}\n",seq->seqX);
	printf("Y={%s}\n",seq->seqY);
	return seq;
   
}

