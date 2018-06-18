#ifndef _LINKED_NODE_H_
#define _LINKED_NODE_H_
typedef struct Linked_Node
{
	char *p_data;
}linked_node,*p_linked_node;

typedef struct Linked_list
{
	p_linked_node top;
	p_linked_node bottom;
	int linked_num;

}linked_list, *p_linked_list;

//初始化链表
void init_linkedlist(p_linked_list );

//插入链表
void linkedlist_push(p_linked_list, char*);

//弹出链表
void linkedlist_pop(p_linked_list, char*);

//链表是否为空
int is_empty_linkedlist(p_linked_list);

//链表是否满
int is_full_linkedlist(p_linked_list);

//清空链表
void clear_linkedlist(p_linked_list);

//删除链表
void del_linkedlist(p_linked_list);


#endif
