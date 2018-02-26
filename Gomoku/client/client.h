#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
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


//SDL_control.c
int update_qipan(char checkerboard[15][15]);   											//显示棋盘
struct message * luozi (struct channel *mult);											//用户输入招数


//net_control.c
char referee (char checkerboard[15][15]);   											//判断输赢
struct channel * update_qi (struct sockaddr_in *server , int channel_num); 	   			//在网络上更新棋盘 
int send_qi (struct message *mess , struct sockaddr_in *server);   					    //发送招数
struct channel * new_game (struct sockaddr_in *server);									//新游戏
void clear_channel (struct sockaddr_in *server,int channel_num); 						//清理频道
SOCKET load_socket(struct sockaddr_in *server);											//建立连接
void Load_pack( char *ip , int port , struct sockaddr_in *server );						//加载soket配置信息
char *load_ip (void);																	//获取服务器端ip

SDL_Surface *windows ;