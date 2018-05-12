#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mysql/mysql_connect.h"
int main()
{
    int flag_mysql = 0;
    flag_mysql = init_mysql();

    insert("insert into user (name) value(\"nihao\")");


    close_mysql();
    
}


