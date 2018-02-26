#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main ()
{
	struct sockaddr_in server;
	WSADATA wsadata;
	int socker = 0 ,connected;
	char *abc;

	abc = (char *) malloc (sizeof (char) * 100);
	if(WSAStartup(MAKEWORD(1,1),&wsadata) == SOCKET_ERROR)
	{
		return -1;
	}
	memset (&server,0,sizeof (server));
	socker = socket (AF_INET,SOCK_STREAM,0);
	if (socker == -1)
	{
		return -1;
	}
	server . sin_family = AF_INET;
	server . sin_addr . s_addr = htonl(INADDR_ANY);
	server . sin_port = htons(8000);
	if (-1 == bind (socker , (struct sockaddr*)&server , sizeof (server) ) )
	{
		return -1;
	}
	if (-1 == listen(socker , 10))
	{
		return -1;
	}
	connected = accept (socker , (struct sockaddr *)NULL , NULL);
	recv(connected,abc,100,0);
	printf("%s",abc);
}