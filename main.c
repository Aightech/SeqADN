#include "seqlib.h"

int main()
{
	Seq *S=getSeq("Inst_0000010_44.adn");
	int **F=COUT1(S);
	int i=9,j=2,m=0 ;
	OUT2(S,i,j,&m);
	printf("F(%d,%d)=%d, min=%d\n",i,j,COUT2(S,i,j,&m),m);
	
	
	Nucleotides *N=SOL1(S,F);
	/*printf("N:\n");
	dispNucleotides(N);
	printf("M:\n");
	dispNucleotides(S->M);
	printf("Conclusion:\n");
	printf("Alignement's lenght: %d\n",S->lenght);
	printf("Alignement's errors: %d\n",S->errors);
	printf("Alignement's gaps: %d\n",S->gaps);*/
	
	
}
