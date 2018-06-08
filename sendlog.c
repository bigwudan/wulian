#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>


int main()
{
	syslog(LOG_MAIL|LOG_NOTICE, "testwudan");
	printf("ok\r\n");


}

