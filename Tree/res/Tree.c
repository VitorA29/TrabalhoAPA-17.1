#include "Tree.h"

static float const null=666.666;

static int counter=0;

struct struct_employees_tree{
	Employee me;
	int numSubs, index;
	Tree *sub, super;//Employees that I supervise; Employee that supervise me.
	float cr;//Conviviality Rating.
};

Tree create_tree(void){return (Tree)malloc(sizeof(STree));}

void initialize_tree(Tree t){
	t->sub=NULL;
	t->super=NULL;
	t->me=NULL;
	t->index=0;
	t->numSubs=0;
	t->cr=null;
}

Tree search_tree(Tree t, Employee e){
	if(!compare_employee(e, t->me))return t;
	Tree aux;
	int i;
	for(i=0;i<t->numSubs;i++){
		aux = search_tree(t->sub[i], e);
		if(aux)return aux;
	}
	return NULL;
}

Tree get_sub_tree(Tree t, int i){
	if(!t || i>=t->numSubs)return NULL;
	return t->sub[i];
}

int get_index_tree(Tree t){return t->index;}

Tree get_super_tree(Tree t){return t->super;}

float get_conviviality_tree(Tree t){return t->cr;}

Employee get_employee_tree(Tree t){return t->me;}

int has_sub_tree(Tree t){return t->numSubs!=0;}

int insert_tree(Tree t, Employee emp, Tree super, float cr){
	if(!emp)return 0;
	if(!super){
		if(t->me)return 0;
		t->me=emp;
		t->cr=cr;
		t->index=++counter;
		return 1;
	}
	if(empty_tree(super))return 0;
	Tree new = create_tree();
	initialize_tree(new);
	new->super=super;
	new->me=emp;
	new->cr=cr;
	new->index=++counter;
	super->numSubs++;
	super->sub=(Tree*)realloc(super->sub, (super->numSubs)*sizeof(Tree));
	super->sub[super->numSubs-1]=new;
	return 1;
}

void print_node_tree(Tree t){
	if(empty_tree(t)){
		printf("NULL");
		return;
	}
	printf("{ %d - ", t->index);
	print_employee(t->me);
	if(t->cr==null)printf(" - null }");
	else printf(" - %.5f }", t->cr);
}

void print_super_subs(Tree t){
	if(!t)return;
	int i,j=t->numSubs/2;
	if(!(t->numSubs%2))j--;
	for(i=(t->numSubs-1);i>j;i--){
		printf("\t%d ", i);
		print_node_tree(t->sub[i]);
		printf("\n");
	}
	print_node_tree(t);
	printf("\n");
	for(;i>=0;i--){
		printf("\t%d ", i);
		print_node_tree(t->sub[i]);
		printf("\n");
	}
	return;
}

static void aux_print_tree(Tree t, int tab){
	if(!t)return;
	int i,j=t->numSubs/2;
	if(!(t->numSubs%2))j--;
	for(i=t->numSubs-1;i>j;i--)aux_print_tree(t->sub[i], tab+1);
	for(j=0;j<tab;j++)printf("\t");
	print_node_tree(t);
	printf("\n");
	for(;i>=0;i--)aux_print_tree(t->sub[i], tab+1);
	return;
}

void print_tree(Tree t){aux_print_tree(t, 0);}

int empty_tree(Tree t){return (!t->sub && !t->super && !t->me && !t->numSubs && t->cr==null && !t->index);}

static Tree search_index_tree(Tree t, int nodeCount){
	if(t->index==nodeCount)return t;
	Tree aux;
	int i;
	for(i=0;i<t->numSubs;i++){
		aux = search_index_tree(t->sub[i], nodeCount);
		if(aux)return aux;
	}
	return NULL;
}

static int insert_index_tree(Tree t, Employee emp, int superCount, float cr){
	if(!emp)return 0;
	if(superCount==0){
		if(t->me)return 0;
		t->me=emp;
		t->cr=cr;
		t->index=++counter;
		return 1;
	}
	Tree super=search_index_tree(t, superCount);
	if(empty_tree(super))return 0;
	Tree new = create_tree();
	initialize_tree(new);
	new->super=super;
	new->me=emp;
	new->cr=cr;
	new->index=++counter;
	super->numSubs++;
	super->sub=(Tree*)realloc(super->sub, (super->numSubs)*sizeof(Tree));
	super->sub[super->numSubs-1]=new;
	return 1;
}

void write_file_tree(Tree root){
	char fname[101], *name;
	printf("type the file name: ");
	scanf("%s", fname);
	strcat(fname, ".bin");
	FILE *fp=fopen(fname, "wb");
	int i, size, first=0;
	Tree t;
	for(i=1;i<=counter;i++){
		t=search_index_tree(root, i);
		name=get_employee_name(t->me);
		size=strlen(name);
		fwrite(&size, 1, sizeof(int), fp);
		fwrite(name, size, sizeof(char), fp);
		if(t->super)fwrite(&t->super->index, 1, sizeof(int), fp);
		else fwrite(&first, 1, sizeof(int), fp);
		fwrite(&t->cr, 1, sizeof(float), fp);
	}
	fclose(fp);
}

Tree read_file_tree(void){
	char fname[101];
	printf("type the file name: ");
	scanf("%s", fname);
	strcat(fname, ".bin");
	FILE *fp=fopen(fname, "rb");
	Tree resp=create_tree();
	initialize_tree(resp);
	char *name;
	int size, super, end;
	float cr;
	Employee emp = create_employee();
	fseek(fp, 0L, SEEK_END);
	end=ftell(fp);
	rewind(fp);
	while(ftell(fp)!=end){
		fread(&size, 1, sizeof(int), fp);
		name=(char*)malloc(size*sizeof(char));
		fread(name, size, sizeof(char), fp);
		fread(&super, 1, sizeof(int), fp);
		fread(&cr, 1, sizeof(float), fp);
		set_employee_name(emp, name);
		insert_index_tree(resp, emp, super, cr);
		free(name);
	}
	exclude_employee(emp);
	fclose(fp);
	return resp;
}

void exclude_tree(Tree t){
	if(!t)return;
	if(t->me)exclude_employee(t->me);
	int i;
	for(i=0;i<t->numSubs;i++)exclude_tree(t->sub[i]);
	free(t);
	return;
}
