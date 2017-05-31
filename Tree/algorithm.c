#include "res/Tree.h"

typedef struct struct_employees_list{
	Employee *list;
	int size;
}*List, SList;

List create_list(void){return (List)malloc(sizeof(SList));}

void initialize_list(List l){
	if(l->list)free(l->list);
	l->list=NULL;
	l->size=0;
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

float resolver(Tree t, List l){
	if(!has_sub_tree(t)){
		add_list(l, get_employee_tree(t));
		return get_conviviality_tree(t);
	}
	int i=0, j;
	float A=0.0, B=get_conviviality_tree(t);
	List lA = create_list(), lB = create_list();
	initialize_list(lA);
	initialize_list(lB);
	while(get_sub_tree(t, i)){
		A+=resolver(get_sub_tree(t, i), lA);
		j=0;
		while(get_sub_tree(get_sub_tree(t, i), j))
			B+=resolver(get_sub_tree(get_sub_tree(t, i), j++), lB);
		i++;
	}
	if(B>A){
		add_list(lB, get_employee_tree(t));
		join_list(l, lB);
		return B;
	}
	join_list(l, lA);
	return A;
}
