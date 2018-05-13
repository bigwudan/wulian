#include <stdio.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/socket.h>  
#include <resolv.h>  
#include <stdlib.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <openssl/ssl.h>  
#include <openssl/err.h>  
#include "mysql/mysql_connect.h"
void sig_int(int num)
{
    printf("testover\n");
    exit(1);
};
int main()
{
    int sockfd = 0;
    int client_fd = 0;
    int err = 0;
	struct sockaddr_in dest;  
	struct sockaddr_in client_addr;  
    char buff[1024]= {0};
    signal(SIGINT, sig_int);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
    {  
    perror("Socket");  
    exit(errno);  
    }  
    printf("socket created\n");  

    /* 初始化服务器端（对方）的地址和端口信息 */  
    bzero(&dest, sizeof(dest));  
    dest.sin_family = AF_INET;  
    dest.sin_port = htons(8111);  
    dest.sin_addr.s_addr = htonl(INADDR_ANY);  
    err = bind(sockfd, (struct sockaddr *)&dest, sizeof(dest));
    if(err < 0){
        printf("bind error\n");
    }
    err = listen(sockfd, 2);
    if(err < 0){
        printf("listen error\n");
    }
    while(1){
        bzero(buff, 1024);
        socklen_t addrlen = sizeof(struct sockaddr);
        client_fd= accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);
        read(sockfd, buff, 1024);    
        close(client_fd);        

    
    }

    close(sockfd);
    return 1;
    int flag_mysql = 0;
    flag_mysql = init_mysql();

    insert("insert into user (name) value(\"nihao\")");


    close_mysql();
    
}


