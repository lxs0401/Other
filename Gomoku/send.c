#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
void Load_pack ( char *ip , int port , struct sockaddr_in *server );
SOCKET load_socket(struct sockaddr_in *server);

int main (void)
{
	WSADATA wsadata;
	struct sockaddr_in server;
	SOCKET socker;
	char *ip , *ip2;

	ip  = (char *) malloc (sizeof (char) * 16);
	ip2 = (char *) malloc (sizeof (char) * 16);

	if(WSAStartup(MAKEWORD(1,1),&wsadata) == SOCKET_ERROR)
	{
		return -1;
	}
	scanf ("%s" , ip);
	scanf ("%s" , ip2);
	
	Load_pack (ip , 5432 , &server);
	socker = load_socket (&server);
	send (socker , (char *)ip2 , sizeof (char) * 16 , 0);
	closesocket(socker);
}

void Load_pack ( char *ip , int port , struct sockaddr_in *server )
{
	memset (server,0,sizeof (struct sockaddr_in));
	server -> sin_family = AF_INET;
	server -> sin_port   = htons(port);
	server -> sin_addr . s_addr = inet_addr(ip);
}
SOCKET load_socket(struct sockaddr_in *server)
{
	SOCKET socker ;
	socker = socket (AF_INET , SOCK_STREAM , 0);
	
	if (socker == -1)
	{
		return 0;
	}
	if( connect(socker,(struct sockaddr *)server,sizeof(* server)) == -1)
	{
		return 0;
	}
	return socker;
}