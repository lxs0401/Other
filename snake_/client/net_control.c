#include "snake_client.h"

void recv_farm (SOCKET jack ,struct snake_farm *farm)
{
	recv (jack,(char *)farm,sizeof(struct snake_farm),0);
	return ;
}
void send_message(SOCKET jack,char behavior,char action,char name)
{
	struct farm_message	mess;
	mess . behavior = behavior;
	mess . action = action;
	mess . name = name;
	send (jack,(char *)&mess,sizeof(struct farm_message),0);
}
struct sockaddr_in load_ip (int port)
{
	struct sockaddr_in server;
	memset(&server,0,sizeof(server));
	
	server . sin_family = AF_INET;
	
	server . sin_addr.s_addr = inet_addr ("127.0.0.1");			//连接到服务器ip
	
	server . sin_port = htons(port);
	
	return server;
}
SOCKET load_socket (struct sockaddr_in *server)
{
	SOCKET jack;
	
	jack = socket (AF_INET,SOCK_STREAM,0);
	if (jack == -1)
	{
		return -1;
	}
	if( connect(jack,(struct sockaddr *)server,sizeof(* server)) == -1)
	{
		return -1;
	}
	return jack;
}