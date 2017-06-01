#include "EmployeeList.h"

struct struct_employees_list{
	Employee *list;
	int size;
};

List create_list(void){return (List)malloc(sizeof(SList));}

void initialize_list(List l){
	l->list=NULL;
	l->size=0;
}

void clear_list(List l){
	if(l->list)free(l->list);
	initialize_list(l);
}

void add_list(List l, Employee e){
	if(!e)return;
	l->size++;
	l->list=(Employee*)realloc(l->list, (l->size)*sizeof(Employee));
	l->list[l->size-1]=e;
}

void join_list(List a, List b){
	int i=0;
	while(i<b->size)add_list(a, b->list[i++]);
}

void print_list(List l){
	printf("{ ");
	int i;
	for(i=0;i<l->size;i++){
		print_employee(l->list[i]);
		printf(" ");
	}
	printf("}\n");
}

void exclude_list(List l){
	free(l->list);
	free(l);
}
