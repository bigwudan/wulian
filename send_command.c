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
#define MAXBUF 1024  

 #define PORT 8743
 #define DINADDR_ANY "180.101.147.89" 


int main(){

	int i,j,sockfd, len, fd, size, flag;  
	char fileName[50],sendFN[20];  
	struct sockaddr_in dest;  
	char buffer[MAXBUF + 1];  
	SSL_METHOD *meth;
	SSL_CTX *ctx;  
	SSL *ssl;  
	char pwd[100];
	char* temp;
    char taken[80] = {0};

	SSL_library_init();
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	meth=SSLv23_client_method();
	ctx=SSL_CTX_new(meth);
	if(!ctx){
		exit(1);
	}
  /* 创建一个 socket 用于 tcp 通信 */  
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
  {  
    perror("Socket");  
    exit(errno);  
  }  
  printf("socket created\n");  

  /* 初始化服务器端（对方）的地址和端口信息 */  
  bzero(&dest, sizeof(dest));  
  dest.sin_family = AF_INET;  
  dest.sin_port = htons(8743);  
  if (inet_aton("180.101.147.89", (struct in_addr *) &dest.sin_addr.s_addr) == 0)  
  {  
    perror("inet_aton");  
    exit(errno);  
  }  
  printf("address created\n");  

  /* 连接服务器 */  
  if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0)  
  {  
    perror("Connect ");  
    exit(errno);  
  }  
  printf("server connected\n\n");  
  if (SSL_CTX_use_certificate_file(ctx,"client.pem", SSL_FILETYPE_PEM) <= 0)  
  {  
    ERR_print_errors_fp(stdout);  
    exit(1);  
  }  


 if (SSL_CTX_use_PrivateKey_file(ctx, "clientkey.pem", SSL_FILETYPE_PEM) <= 0)  
  {  
    ERR_print_errors_fp(stdout);  
    exit(1);  
  }
	    /* 基于ctx 产生一个新的SSL */
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);


 // flag=  SSL_connect(ssl);
    if (SSL_connect(ssl) == -1)
        ERR_print_errors_fp(stderr);
    else {
		printf("connected\n");
        printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
    }
char *p_head1 = "/iocm/app/sec/v1.1.0/login/";
char *p_head2 = "180.101.147.89:8743";
int bodynum = 70;
char *p_appid = "Xqwyn4lJPuLIPYqHBH8UN_zK8fsa";
char *p_appkey = "XIcGewffJE8LpfMWksO4Vipvfsga";

 ssize_t size_len = 0;
 char buff[300];
 sprintf(
              buff,
              "POST %s HTTP/1.1\nHost: %s\nContent-Type:application/x-www-form-urlencoded\nContent-Length: %d\r\n\r\nappId=%s&secret=%s",
              p_head1,
              p_head2,
              bodynum,
              p_appid,
              p_appkey
      );


	/*printf("buff=%s\n", buff);*/



	len = SSL_write(ssl, buff, 300);

	char buffer_len[1024];

    /* 接收服务器来的消息*/
    len = SSL_read(ssl, buffer_len, 1024);
    if (len > 0){
        /*printf("接收消息成功:'%s'，共%d 个字节的数据\n",*/
               /*buffer_len, len);*/
    }    
    else {
        printf
        ("消息接收失败！错误代码是%d，错误信息是'%s'\n",
         errno, strerror(errno));
		exit(1);
    }
    char *p_add = NULL;
    p_add = strstr(buffer_len, "\"accessToken\":");
    p_add = p_add+17;

    char *p_start = NULL;
    int dur = 0;
    p_start =  strstr(p_add, "\"");
    dur = p_start- p_add;
    memcpy(taken, p_add, dur*sizeof(char)); 

	printf("taken=%s\n",taken);
	return 1;
}

