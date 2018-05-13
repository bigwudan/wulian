serivce:test_mysql.c mysql/mysql_connect.c
    gcc test_mysql.c mysql/mysql_connect.c -I/usr/include/mysql/  -L/usr/lib/mysql/ -lmysqlclient -o test_mysql && ./test_mysql
