#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <time.h>
//line_snake 的状态
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
struct snake					//小蛇
{
	char x , y;
	struct snake *next;
};

char   send_farm           (struct snake_farm * farm , SOCKET jack);	//发送场地
SOCKET load_socket         (struct sockaddr_in *server);			    //加载socket
struct sockaddr_in load_ip (int port);						            //装载IP
char   line_snake          (struct snake_farm *p , char action);		//行蛇
char   snake_loss_status   (struct snake *p);					        //判断输赢
char   button_status       (struct snake *p , char action);			    //按键失误检测
void   initialize          (struct snake_farm *p);						//初始化蛇场