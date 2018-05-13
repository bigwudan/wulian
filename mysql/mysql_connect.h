#ifndef _MYSQL_CONNECT_H
#define _MYSQL_CONNECT_H

#include <mysql/mysql.h>
extern MYSQL *g_conn;

extern int insert(const char *);
extern void print_mysql_error(const char *msg); 
extern int executesql(const char * sql);
extern int init_mysql();
extern void close_mysql(); 
#endif  
