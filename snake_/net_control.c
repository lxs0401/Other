#include "snake.h"

char send_farm (struct snake_farm * farm , SOCKET jack)
{
	char error = 0;
	error = send (jack ,(char *)farm,sizeof(struct snake_farm),0);
	return error;
}
SOCKET load_socket (struct sockaddr_in *server)
{
	SOCKET jack;
	
	jack = socket (AF_INET,SOCK_STREAM,0);
	if (jack == -1)
	{
		return -1;
	}
	if (bind(jack , (struct sockaddr *)server , sizeof(* server) ) == -1 )
	{
		return -1;
	}
	if ( listen(jack , 10) ==  -1)
	{
		return -1;
	}
	return jack;
}
struct sockaddr_in load_ip (int port)
{
	struct sockaddr_in server;
	memset(&server,0,sizeof(server));
	
	server . sin_family = AF_INET;
	
	server . sin_addr.s_addr = htonl(INADDR_ANY);
	
	server . sin_port = htons(port);
	
	return server;
}