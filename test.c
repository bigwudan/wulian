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
	char *p_char = "aeqwe3423ccccContent-Length: 121212\r\nwudwnad\r\n";
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
		dest = atoi("21212wqwr");
	}
	
		
	
	printf("num:%d\n, str=%s\n", dest, buff);






}


