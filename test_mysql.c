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
#include <syslog.h>
#include "mysql/mysql_connect.h"



void signal_crash_handler(int sig)
{
	syslog(LOG_MAIL|LOG_NOTICE, "error=crash_handler");
	exit(-1);
}
 
void signal_exit_handler(int sig)
{
	syslog(LOG_MAIL|LOG_NOTICE, "error=exit_handler");
	exit(0);
}

void server_on_exit(void)
{
	syslog(LOG_MAIL|LOG_NOTICE, "error=exit");
}

void sig_int(int num)
{
    printf("testover\n");
    exit(1);
};

//转椅
int change_word(char *dest, const char *buff)
{
	int num =0;
	while(*buff){
		if(*buff == '"'){
			*dest = '\\';
			dest = dest + 1;
			*dest = '"';
		}else{
			*dest = *buff;
		}
		buff++;
		dest++;
	}
	return 1;
}


//得到body大小
int get_body_num(char *p_char)
{
	char *p_addr = NULL;
	char *p_des = NULL;
	char buff[1000] = {0};
	int dest = 0;
	p_addr = strstr(p_char, "Content-Length: ");
	if(p_addr){
		p_addr = p_addr + 16;
		p_des = strstr(p_addr, "\r\n");
		dest = p_des - p_addr;
		strncpy(buff, p_addr, dest);
		dest = atoi(buff);
	}
	return dest;		
}


int main()
{
    int sockfd = 0;
    int client_fd = 0;
    int err = 0;
	int body_num = 0;
	struct sockaddr_in dest;  
	struct sockaddr_in client_addr;  
    char buff[1024]= {0};
	char *rev;
	char insertbuff[1024] = {0};
	char dest_buff[1024] = {0};
	char body_buff[1024] = {0};


	atexit(server_on_exit);
	signal(SIGTERM, signal_exit_handler);
	signal(SIGINT, signal_exit_handler);
//	signal(SIGPIPE, SIG_IGN);
	signal(SIGBUS, signal_crash_handler); 
	signal(SIGSEGV, signal_crash_handler);
	signal(SIGFPE, signal_crash_handler);
	signal(SIGABRT, signal_crash_handler); 



    //signal(SIGINT, sig_int);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
    {  
    perror("Socket");  
    exit(errno);  
    }  
    printf("socket created\n");  
	strcpy(insertbuff, "socket created");
	syslog(LOG_MAIL|LOG_NOTICE, "error=%s", insertbuff);
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
		bzero(insertbuff, 1024);
		bzero(body_buff, 1024);

        socklen_t addrlen = sizeof(struct sockaddr);
        client_fd= accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);
        read(client_fd, buff, 1024);    
		body_num =  get_body_num(buff);
		rev = strstr(buff, "\r\n\r\n");
		rev = rev +4;

		strncpy(body_buff, rev, body_num);
        close(client_fd);        
		sprintf(insertbuff, "insert into user (value) value ('%s')", body_buff);	
		err = init_mysql();
		if(err == -1){
			print_mysql_error("error");
			syslog(LOG_MAIL|LOG_NOTICE, "error=mysql_error");
			exit(1);
		}

		err = insert(insertbuff);

		if(err == -1){
			
			syslog(LOG_MAIL|LOG_NOTICE, "error=%s", insertbuff);

			//printf("error_sql=%s\n", insertbuff);
			//print_mysql_error("errori_1");
			//exit(1);
		}

		close_mysql();
    
    }

    close(sockfd);
    return 1;
    
}


