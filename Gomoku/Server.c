#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>


#define MAX_CHANNEL 10
#define WHITE 	     0
#define BLACK 		 1
#define NOTHING 	 2
#define OTHER 		 3

#define NEW_GAME	 0
#define UPDATE		 1
#define MAKE		 3
#define CLEAR		 4
struct channel
{
	int channel_num;
	char checkerboard[15][15];
	char b_or_w;
};
struct message
{
	int channel_num;
	char x , y;
	char b_or_w;
	char request;
};
char get_gomoku(char *line)
{
	for (int x = 0 ; x < 10 ; x ++)
	{
		if (line[x] < 2)
		{
			line [x] += 1;
			return x;
		}
	}
	return 10;
}
int main ()
{
	struct channel *mult;
	struct message *mess;
	int socker , connected;
	struct sockaddr_in server;
	char line[10] = {0}; //场次
	
	WSADATA wsadata;
	if(WSAStartup(MAKEWORD(1,1),&wsadata) == SOCKET_ERROR)
	{
		return -1;
	}
	
	mult = (struct channel *) malloc (sizeof (struct channel) * (MAX_CHANNEL + 1));
	mess = (struct message *) malloc (sizeof (struct message));
	for (int x = 0 ; x < MAX_CHANNEL ; x ++)
	{
		mult[x] . channel_num = -1;
	}
	mult[MAX_CHANNEL] . channel_num = -1;
	
	memset (&server,0,sizeof (server));
	socker = socket (AF_INET,SOCK_STREAM,0);
	if (socker == -1)
	{
		return -1;
	}
	server . sin_family = AF_INET;
	server . sin_addr . s_addr = htonl(INADDR_ANY);
	server . sin_port = htons(2345);
	
	if (-1 == bind (socker , (struct sockaddr*)&server , sizeof (server) ) )
	{
		return -1;
	}
	if (-1 == listen(socker , 10))
	{
		return -1;
	}
	printf ("Gomoku Server 0.1 OK\n");
	for (;;)
	{
		connected = accept (socker , (struct sockaddr *)NULL , NULL);
		if ( connected != -1 )
		{
			recv(connected,(char *)mess,sizeof (struct message),0);
			if (mess -> request == NEW_GAME)
			{
				int farm_num = get_gomoku(line);
				mult [farm_num] . channel_num = farm_num;
				if (farm_num < 10)
				{
					for (int y = 0 ; y < 15 ; y ++)
					{
						for (int x = 0 ; x < 15 ; x ++)
						{
							mult [farm_num] . checkerboard [y][x] = NOTHING;
						}
					}
					mult[farm_num] . b_or_w = line[farm_num] == 1 ? BLACK : WHITE;
				}
				send(connected,(char *)(mult + farm_num),sizeof (struct channel),0);
				printf ("Create Gomoku farm %d\n", (mult + farm_num) ->  channel_num);
				mult[farm_num] . b_or_w = BLACK;
			}
			else if (mess -> request == MAKE)
			{
				if (mult[mess -> channel_num].checkerboard[mess -> y][mess -> x] == NOTHING)
				{
					mult[mess -> channel_num] . checkerboard [mess -> y][mess -> x] = mess -> b_or_w;
					mult[mess -> channel_num] . b_or_w = (mult[mess-> channel_num] . b_or_w == BLACK) ? WHITE : BLACK;
					printf ("MAKE farm :%d\n",mess -> channel_num);
				}
			}
			else if (mess -> request == UPDATE)
			{
				send (connected ,(char *) (&mult[mess -> channel_num]) ,sizeof (struct channel) , 0 );
				printf ("updata farm : %d\n",mess -> channel_num);
			}
			else if (mess -> request == CLEAR)
			{
				line[mess -> channel_num] = 0;
			}
			
			closesocket(connected);
		}
	}
}