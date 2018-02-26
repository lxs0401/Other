#include "client.h"

int main (int argc , char *argv[])
{
	char me_color;
	struct sockaddr_in server;
	struct channel *mult;
	struct message *mess;
	char operate = 0, *ip;
	int channel_num = 0;
	
	//初始化网络
	WSADATA wsadata;
	
	windows  = NULL;
	if(WSAStartup(MAKEWORD(1,1),&wsadata) == SOCKET_ERROR)
	{
		return -1;
	}
	
	ip = load_ip();                  			 //获取服务器端ip
	Load_pack (ip,2345,&server);     			 //加载socket

	//开始一个新的游戏
	mult = new_game (&server);
	channel_num = mult -> channel_num;
	me_color = mult -> b_or_w;
	free (mult);

	//游戏开始
	mult = update_qi(&server,channel_num);
	SDL_Init( SDL_INIT_EVERYTHING );
	while (referee (mult -> checkerboard))
	{
		
		if (mult -> b_or_w == me_color)
		{
			send_qi(luozi(mult),&server);
			mult = update_qi(&server,channel_num);
		}
		else
		{
			free (mult);
			mult = update_qi(&server,channel_num);
			update_qipan (mult -> checkerboard);
			SDL_Delay(800);
		}
	}
	SDL_Delay(1000);
	clear_channel(&server , mult -> channel_num);
	SDL_Quit();
	WSACleanup();
	return 0;
}