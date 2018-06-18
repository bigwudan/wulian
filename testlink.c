#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist/linkedlist.h"


int main()
{
	char buf[1200] = {0};
	linked_list list;
	init_linkedlist(&list);
	linkedlist_push(&list, "test1");
	linkedlist_push(&list, "test2");
	linkedlist_push(&list, "test3");
	linkedlist_push(&list, "test4");

	
    linkedlist_pop(&list, buf);
	
	printf("buf=%s\n", buf);

    linkedlist_pop(&list, buf);
	
	printf("buf=%s\n", buf);
    linkedlist_pop(&list, buf);
	
	printf("buf=%s\n", buf);

	printf("end\n");



}
