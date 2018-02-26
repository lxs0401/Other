#include "snake_client.h"

int main (int argc ,char *argv[])
{
	SOCKET jack;
	SDL_Surface *windows;
	struct snake_farm farm;
	struct sockaddr_in server;
	char name;
	WSADATA wsadata;
	
	SDL_Init( SDL_INIT_EVERYTHING ); //初始化
	windows = SDL_SetVideoMode( 360, 360, 32, SDL_SWSURFACE );
	if(WSAStartup(MAKEWORD(1,1),&wsadata) == SOCKET_ERROR)
	{
		printf("netowkr_error\n");
		return 0;
	}
	server = load_ip (7777);
	jack = load_socket (&server);
	if (jack == -1)
	{
		return 0;
	}
	send_message(jack,R_OR_B,LEFT,RED);
	recv_farm (jack ,&farm);
	name = farm . who_set;
	update_farm (&farm , windows , name);
	closesocket(jack);
	while (1)
	{
		jack = load_socket (&server);
		if (jack == -1)
		{
			return 0;
		}

		if (farm . who_set == name)
		{
			char prov_action = OTHER;
			prov_action = get_action();
			if (prov_action != OTHER)
			{
				send_message(jack,MAKE,prov_action,name);
			}
			else
			{
				send_message(jack,UPDATE,LEFT,name);
			}
		}
		else
		{
			send_message(jack,UPDATE,LEFT,name);
		}
		recv_farm (jack ,&farm);
		update_farm (&farm , windows , name);
		closesocket(jack);
		SDL_Delay(100);
	}
}