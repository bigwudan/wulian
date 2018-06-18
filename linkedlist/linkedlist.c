#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"

int limit_num = 10;

//初始化
void init_linkedlist(p_linked_list p_list )
{
	p_linked_node p_tmp =  malloc(sizeof(linked_node)*limit_num);
	p_list->top = p_tmp;
	p_list->bottom = p_tmp;
	p_list->linked_num = limit_num;
	return;
}

//插入链表
void linkedlist_push(p_linked_list p_list, char * p_str)
{
	if( (p_list->top - p_list->bottom) >= p_list->linked_num ){
		p_list->bottom =  realloc(p_list->bottom, sizeof(linked_node)*(limit_num + p_list->linked_num));
		p_list->top = p_list->bottom + p_list->linked_num;
		p_list->linked_num = p_list->linked_num + limit_num;
	}	
	int len = strlen(p_str)+1;
	p_list->top;
	p_list->top->p_data = malloc(sizeof(char)*len);
	strcpy(p_list->top->p_data, p_str);		
	p_list->top++;
	return ;
}
//弹出数据
void linkedlist_pop(p_linked_list p_list, char* p_val)
{
	char * p_tmp = (--p_list->top)->p_data;
	strcpy(p_val, p_tmp);
	free(p_tmp);
	p_tmp = NULL;

	//strcpy(p_val, p_list->top->p_data);
	//p_list->top--;
}

//链表是否为空
int is_empty_linkedlist(p_linked_list p_list)
{
	if(p_list->top == p_list->bottom){
		return 1;	
	
	}else{
		return 0;
	}	

}

//是否满链表
int is_full_linkedlist(p_linked_list p_list)
{
	if((p_list->top - p_list->bottom) >= p_list->linked_num ){
		return 1;
	}else{
		return 0;
	}
}




