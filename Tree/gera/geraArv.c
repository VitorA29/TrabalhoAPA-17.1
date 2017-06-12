#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argI, char **argS){
	if(argI!=3)return 0;
	int nos=atoi(argS[1]);
	char nome[]="Vitor";
	FILE *fp=fopen(argS[2],"wt");
	if(!fp)exit(1);	
	srand(time(NULL));
	int auxCr = rand() %1000000;
	float cr=auxCr/1000;
	fprintf(fp, "5 0 %.3f\n%s\n", cr, nome);
	int super, aux=nos-1;
	while(aux){
		super =1 + rand() %(nos-aux);
		auxCr = rand() %1000000;
		cr=auxCr/1000;
		fprintf(fp, "5 %d %.3f\n%s\n", super, cr, nome);
		aux--;
	}
	fclose(fp);
	return 0;
}
