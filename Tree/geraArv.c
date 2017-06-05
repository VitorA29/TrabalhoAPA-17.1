#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argI, char **argS){
	if(argI!=3)return 0;
	int nos=atoi(argS[1]);
	char nome[]="Vitor";
	FILE *fp=fopen(argS[2],"wt");
	if(!fp)exit(1);
	fprintf(fp, "5 0 666\n%s\n", nome);
	srand(time(NULL));
	int super, aux=nos-1;
	float cr;
	while(aux){
		super =1 + rand() %(nos-aux);
		cr = rand() %1000;
		fprintf(fp, "5 %d %f\n%s\n", super, cr, nome);
		aux--;
	}
	fclose(fp);
	return 0;
}
