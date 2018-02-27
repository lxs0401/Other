#include "client.h"

char *load_ip (void)
{
	struct sockaddr_in server;
	SOCKET socker;
	int connected;
	char *ip;

	ip = (char *) malloc (sizeof (char) * 16);
	memset (&server,0,sizeof (server));
	socker = socket (AF_INET,SOCK_STREAM,0);
	if (socker == -1)
	{
		return NULL;
	}
	server . sin_family = AF_INET;
	server . sin_addr . s_addr = htonl(INADDR_ANY);
	server . sin_port = htons(5432);
	
	if (-1 == bind (socker , (struct sockaddr*)&server , sizeof (server) ) )
	{
		return NULL;
	}
	if (-1 == listen(socker , 10))
	{
		return NULL;
	}
	connected = accept (socker , (struct sockaddr *)NULL , NULL);
	recv(connected,(char *)ip,sizeof (char)*16,0);
	closesocket(socker);
	return ip;
}
void Load_pack ( char *ip , int port , struct sockaddr_in *server )
{
	memset (server,0,sizeof (struct sockaddr_in));
	server -> sin_family = AF_INET;
	server -> sin_port = htons(port);
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
int send_qi (struct message *mess , struct sockaddr_in *server)
{
	SOCKET socker;

	mess -> request = MAKE;

	socker = load_socket(server);
	send (socker , (char *)mess , sizeof (struct message) , 0);
	closesocket(socker);

	return 1;
}
struct channel * update_qi (struct sockaddr_in *server , int channel_num)
{
	SOCKET socker;
	struct channel *mult;
	struct message *mess;

	mess = (struct message *) malloc (sizeof (struct message));
	mult = (struct channel *) malloc (sizeof (struct channel));
	
	mess -> request = UPDATE;
	mess -> channel_num = channel_num;
	socker = load_socket(server);
	send (socker , (char *)mess , sizeof (struct message) , 0);
	recv (socker , (char *)mult , sizeof (struct channel) , 0);
	closesocket(socker);
	return mult;
}
void clear_channel (struct sockaddr_in *server,int channel_num)
{
	SOCKET socker;
	struct message *mess;

	
	mess = (struct message *) malloc (sizeof (struct message));
	mess -> request = CLEAR;
	mess -> channel_num = channel_num;
	

	socker = load_socket(server);
	send (socker , (char *)mess, sizeof (struct message) , 0);
	closesocket(socker);

	return ;
}
struct channel * new_game (struct sockaddr_in *server)
{
	SOCKET  socker;
	int a = 0;
	struct channel *mult;
	struct message *mess;

	
	mess = (struct message *) malloc (sizeof (struct message));
	mult = (struct channel *) malloc (sizeof (struct channel));
	mess -> request = NEW_GAME;

	socker = load_socket(server); 
	send (socker , (char *)mess , sizeof (struct message) , 0);
	recv (socker , (char *)mult , sizeof (struct channel) , 0);
	closesocket( socker );

	return mult;
}