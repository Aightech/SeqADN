#include "seqlib.h"
#define DELTA_GAP 1
#define DELTA_IJ 3

Seq* getSeq(char * path) 
{
	FILE* file=NULL;
	file=fopen(path,"r");
	12 23
	Seq* seq=(Seq*)malloc(sizeof(Seq));
	
	printf("readng file: %s\n",path );
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
		seq->seqX[i]=ch;
		fgetc((FILE*)file);
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
	fclose(file);
	
	seq->lenght=0;
	seq->errors=0;
	seq->gaps=0;
	
	return seq;
   
}

int min(int n1,int n2,int n3)
{
	if(n1<n2){
		if(n3<n1)
			return n3;
		else
			return n1;
	}
	else{
		if(n3<n2)
			return n3;
		else
			return n2;
	}
}

int **COUT1(Seq *S)
{
	int i,j;
	int m=S->sizeX,n=S->sizeY;
	int**F=(int**)malloc((m+1)*sizeof(int*));
	F[0]=(int*)malloc((n+1)*sizeof(int*));
	for(j=0;j<n+1;j++)
	{
		F[0][j]=DELTA_GAP*j;
		printf("%d ",F[0][j]);
	}
	printf("\n");
	for(i=1;i<m+1;i++)
	{
		F[i]=(int*)malloc(n*sizeof(int*));
		F[i][0]=DELTA_GAP*i;
		printf("%d ",F[i][0]);
		for(j=1;j<n+1;j++)
		{
			F[i][j]=min(F[i][j-1]+DELTA_GAP,F[i-1][j]+DELTA_GAP,F[i-1][j-1]+((S->seqX[i-1]==S->seqY[j-1])?0:DELTA_IJ));
			printf("%d ",F[i][j]);
		}
		printf("\n");
	}
	return F;
		
}

int COUT2(Seq *S,int m,int n,int* mini)
{
	int i,j;
	int F[2][n+1];//=(int**)malloc((m+1)*sizeof(int*));
	//F[0]=(int*)malloc((n+1)*sizeof(int*));
	for(j=0;j<n+1;j++)
	{
		F[0][j]=DELTA_GAP*j;
		printf("%d ",F[0][j]);
		
	}
	printf("\n");
	
	for(i=1;i<m+1;i++)
	{
		F[1][0]=DELTA_GAP*i;
		printf("%d ",F[1][0]);
		for(j=1;j<n+1;j++)
		{
			F[1][j]=min(F[1][j-1]+DELTA_GAP,F[0][j]+DELTA_GAP,F[0][j-1]+((S->seqX[i-1]==S->seqY[j-1])?0:DELTA_IJ));
			printf("%d ",F[1][j]);
		}
		printf("\n");
		for(j=0;j<n+1;j++)
		{
			F[0][j]=F[1][j];
			
		}
	}
	if(F[1][j]==F[0][j-1]+((S->seqX[i-1]==S->seqY[j-1])?0:DELTA_IJ))
	{
		*mini=1;
	}
	else if(F[0][j]==F[0][j-1]+DELTA_GAP)
	{
		*mini=0;
	}
	else//(F[i][j]==F[i-1][j]+DELTA_GAP)
	{
		*mini=2;
	}
	*mini=20;
	return F[1][n];
		
}

Nucleotides* SOL1(Seq *S,int** F)
{
	int i=S->sizeX,j=S->sizeY;
	Nucleotides *M=(Nucleotides*)malloc(sizeof(Nucleotides));
	M->nucleo1='X';
	M->nucleo2='Y';
	M->next=NULL;
	Nucleotides *N=(Nucleotides*)malloc(sizeof(Nucleotides));
	N->nucleo1='X';
	N->nucleo2='Y';
	N->next=NULL;
	while(i>0&&j>0)
	{
		if(F[i][j]==F[i-1][j-1]+((S->seqX[i-1]==S->seqY[j-1])?0:DELTA_IJ))
		{
			if(S->seqX[i-1]!=S->seqY[j-1]) 
				S->errors++;
			S->lenght++;
			addPair(N,S->seqX[--i],S->seqY[--j]);
			addPair(M,S->seqX[i],S->seqY[j]);
		}
		else if(F[i][j]==F[i][j-1]+DELTA_GAP)
		{
			S->gaps++;
			addPair(N,'-',S->seqY[--j]);
		}
		else//(F[i][j]==F[i-1][j]+DELTA_GAP)
		{
			S->gaps++;
			addPair(N,S->seqX[--i],'-');
		}
	
	}
	S->M=M;
	while(i>0)
		addPair(N,S->seqX[i--],'-');
	while(j>0)
		addPair(N,'-',S->seqY[j--]);
	return N;
	
}

void addPair(Nucleotides* N,char x,char y)
{
	Nucleotides *next=(Nucleotides*)malloc(sizeof(Nucleotides));
	next->nucleo1=x;
	next->nucleo2=y;
	next->next=NULL;
	while(N->next!=NULL)
	{
		N=N->next;
	}
	N->next=next;
}

void dispNucleotides(Nucleotides* N)
{
	printf("   _____\n"); 
	while(N->next!=NULL)
	{
		printf("  | %c %c |\n",N->nucleo1,N->nucleo2);
		N=N->next;
	}
	printf("  | %c %c |\n",N->nucleo1,N->nucleo2);
	printf("   -----\n");
}
