#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include <winsock2.h>

#define LOSS    0
#define BLOCK   1
//终端双方
#define	RED     1
#define BLUE    2
//信息的形式
#define MAKE    0
#define UPDATE  1
#define R_OR_B  3
//用户动作
#define LEFT    0
#define RIGHT   1
#define DOWN    2
#define UP	    3
#define OTHER   4
//蛇的身体
#define BUTTON  1
#define NOTHING 0

struct snake_farm 				//贪吃蛇的场地
{
	char farm[20][40];
	char who_set;
	char food_y,food_x;
};
struct farm_message				//终端动作
{
	char behavior;
	char action;
	char name;
};

void update_farm (struct snake_farm *pool , SDL_Surface *windows , char name);  //更新蛇场
struct sockaddr_in load_ip (int port);											//加载连接信息
SOCKET load_socket (struct sockaddr_in *server);								//连接服务器
void send_message(SOCKET jack,char behavior,char action,char name);				//发送消息
char get_action (void);															//获取用户动作
void recv_farm (SOCKET jack ,struct snake_farm *farm);							//接收场地