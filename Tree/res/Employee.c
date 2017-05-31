#include "Employee.h"

struct struct_employee{
	char* name;
};

Employee create_employee(void){return (Employee)malloc(sizeof(SEmployee));}

Employee gerate_employee(void){
	Employee resp=(Employee)malloc(sizeof(SEmployee));
	int i;
	printf("Which is the size of the name(counting with white spaces)? ");
	scanf("%d", &i);
	resp->name=(char*)malloc((i+1)*sizeof(char));
	printf("Type the name: ");
	resp->name[0]='\0';
	char aux[200];
	do{
		scanf(" %s", aux);
		if(strlen(resp->name)>0)strcat(resp->name,"_");
		if((strlen(resp->name)+strlen(aux)) > i-1){
			strncat(resp->name, aux, (i-strlen(resp->name)));
			return resp;
		}
		strcat(resp->name, aux);
		if(strlen(resp->name) >= i)return resp;
	}while(1);
}

void set_employee_name(Employee e, char *n){
	if(!e)return;
	if(e->name)free(e->name);
	int i=0;
	while(n[i]!='\0')i++;
	e->name=(char*)malloc(i*sizeof(char));
	strcpy(e->name, n);
}

char* get_employee_name(Employee e){return e->name;}

Employee copy_employee(Employee o){
	if(o){
		Employee resp=(Employee)malloc(sizeof(SEmployee));
		set_employee_name(resp, o->name);
		return resp;
	}
	return NULL;
}

int compare_employee(Employee a, Employee b){
	if(a && b)return strcmp(a->name, b->name);
	return 0;
}

void print_employee(Employee e){
	if(e)printf("[ %s ]", e->name);
	else printf("[ NULL ]");
}

void exclude_employee(Employee e){
	if(!e)return;
	free(e->name);
	free(e);
}
