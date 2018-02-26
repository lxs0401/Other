#include "snake.h"
int main()
{
	SOCKET jack , connected;
	WSADATA wsadata;
	struct sockaddr_in server;
	struct snake_farm farm;
	struct farm_message mess;
	char curret_action;
	
	line_snake (&farm,curret_action);
	
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
	while (1)
	{
		connected = accept(jack,(struct sockaddr*)NULL,NULL);
		recv (connected ,(char *) &mess , sizeof(struct farm_message) , 0);
		if (mess . behavior == UPDATE)
		{
			if (mess . name == farm . who_set)
			{
				if (curret_action != OTHER)
				{
					if (line_snake(&farm,curret_action) != LOSS)
					{
						send_farm ( &farm , connected );
					}
					else
					{
						curret_action = OTHER;
						line_snake (&farm,curret_action);
						farm . who_set = RED;
						send_farm ( &farm , connected );
					}
				}
				else
				{
					send_farm ( &farm , connected);
				}
			}
			else
			{
				send_farm ( &farm , connected);
			}
		}
		else if (mess . behavior == MAKE)
		{
			char status;
			
			if ( (status = line_snake(&farm,mess . action)) != BLOCK)
			{
				if (status == LOSS)
				{
					curret_action = OTHER;
					line_snake (&farm,curret_action);
					farm . who_set = RED;
					send_farm ( &farm , connected );
				}
				else 
				{
					curret_action = mess . action;
					send_farm ( &farm , connected );
				}
			}
		}
		else if (mess . behavior == R_OR_B)
		{
			if (farm . who_set == OTHER)
			{
				farm . who_set = RED;
				send_farm (&farm,connected);
			}
			else if (farm . who_set == RED)
			{
				farm . who_set = BLUE;
				send_farm (&farm,connected);
				farm . who_set = RED;
			}
		}
		closesocket(connected);
	}
}