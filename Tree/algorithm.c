#include "res/Tree.h"
#include "res/EmployeeList.h"

#define null -666

float *dinamicMax=NULL;
List *dinamicList=NULL;

float baile(Tree t, List l){
	if(dinamicMax[get_index_tree(t)-1]!=null){
		join_list(l, dinamicList[get_index_tree(t)-1]);
		return dinamicMax[get_index_tree(t)-1];
	}
	if(!has_sub_tree(t)){
		add_list(l, get_employee_tree(t));
		List auxL=create_list();
		initialize_list(auxL);
		join_list(auxL, l);
		dinamicList[get_index_tree(t)-1]=auxL;
		dinamicMax[get_index_tree(t)-1]=get_conviviality_tree(t);
		return get_conviviality_tree(t);
	}
	int i=0, j;
	float A=0.0, B=get_conviviality_tree(t);
	List lA = create_list(), lB = create_list();
	initialize_list(lA);
	initialize_list(lB);
	while(get_sub_tree(t, i)){
		A+=baile(get_sub_tree(t, i), lA);
		j=0;
		while(get_sub_tree(get_sub_tree(t, i), j))
			B+=baile(get_sub_tree(get_sub_tree(t, i), j++), lB);
		i++;
	}
	if(B>A){
		add_list(lB, get_employee_tree(t));
		dinamicList[get_index_tree(t)-1]=lB;
		join_list(l, lB);
		dinamicMax[get_index_tree(t)-1]=B;
		return B;
	}
	dinamicList[get_index_tree(t)-1]=lA;
	join_list(l, lA);
	dinamicMax[get_index_tree(t)-1]=A;
	return A;
}

float baileBurro(Tree t, List l){
	if(!has_sub_tree(t)){
		add_list(l, get_employee_tree(t));
		return get_conviviality_tree(t);
	}
	int i=0, j;
	float A=0.0, B=get_conviviality_tree(t), resp;
	List lA = create_list(), lB = create_list();
	initialize_list(lA);
	initialize_list(lB);
	while(get_sub_tree(t, i)){
		A+=baileBurro(get_sub_tree(t, i), lA);
		j=0;
		while(get_sub_tree(get_sub_tree(t, i), j))
			B+=baileBurro(get_sub_tree(get_sub_tree(t, i), j++), lB);
		i++;
	}
	if(B>A){
		add_list(lB, get_employee_tree(t));
		join_list(l, lB);
		resp=B;
	}
	else{
		join_list(l, lA);
		resp=A;
	}
	exclude_list(lA);
	exclude_list(lB);
	return resp;
}

List resolver(Tree t, int which){
	List l=create_list();
	initialize_list(l);
	if(which==1){
		int n=get_qtd_nodes_tree(t),i;
		dinamicMax=(float*)calloc(n, sizeof(float));
		dinamicList=(List*)calloc(n, sizeof(List));
		for(i=0;i<n;i++)dinamicMax[i]=null;
		baile(t, l);
		free(dinamicMax);
		for(i=0;i<n;i++)exclude_list(dinamicList[i]);
		return l;
	}
	baileBurro(t, l);
	return l;
}
