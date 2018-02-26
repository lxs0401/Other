#include<stdio.h>
#include<stdlib.h>
#define MAX_l 10
#define MAX_o 10

void yonghu(char **map);
char **cesuan(char **map);
int main()
{
	char **map, **jieguo;

	map = (char **)malloc(sizeof(char **) * MAX_l);       /*分配存储空间 MAX_l*MAX_o*/

	for (int q = 0; q < MAX_l; q++)
		map[q] = (char *)malloc(sizeof(char) * MAX_o);
	yonghu(map);     /*用户输入节标*/
	while (getchar() != 'a')map=cesuan(map);       /* 计算生命游戏*/
	return 0;
}
char **cesuan(char **map)        /*  计算 生命游戏 地图函数*/

{
	char **jiegi;
	int num = 0;
	

	jiegi = (char **)malloc(sizeof(char **) * MAX_l);
	for (int q = 0; q < MAX_l; q++)
	{
		jiegi[q] = (char *)malloc(sizeof(char *) * MAX_o);
	}
	for (int y = 0; y < MAX_l; y++)
	{
		for (int x = 0; x < MAX_o; x++)        /*将欲存为生命游戏地图计算结果的字符型指针指向的内存设为0 */
		{
			jiegi[y][x] = 0;
		}
	}
	
	for (int a = 0; a < MAX_l; a++)   /* 生命游戏基本规则*/
		for (int n = 0; n < MAX_o; n++)
		
			for (int e = a - 1; e <=a + 1; e++)
			{
				for (int r = n - 1; r <= n + 1; r++){
					if ((e >= 0 && e < MAX_l) && (r >=0 && r < MAX_o)){
						if (map[e][r] == 1)
							num++;
					}
					if (map[a][n] == 1)
					{
						num--;
					}
				
					if ((num <=1) || (num > 3))
					{
						jiegi[a][n] = 0;
					}
					else if ( num == 3 )
					{
						jiegi[a][n] = 1;
					}
					else if(map[a][n]==1)
					{
						jiegi[a][n] = 1;
					}
					num = 0;
				}
			}

	
	for (int n = 0; n < MAX_l ; n++){    /*输出结果*/
		for (int a = 0; a < MAX_o ; a++)
		{
			printf("%c", jiegi[n][a] == 1 ? '#' : '-');
		}
		printf("\n");
	}
	for(int x=0;x<MAX_l;x++)
	{
		free(map[x]);
	}
	free(map);
	return jiegi;
}

void yonghu(char **map)

{
	char s = 0;
	int x, y;
	for (int x = 0; x < MAX_l; x++)
	{
		for (int y = 0; y < MAX_o; y++)
		{
			printf("%c", (map[x][y] == 1) ? '#' : '-');
		}
		printf("\n");
	}
	while (s != 'a')         /*输入 x坐标,y坐标,任意字符(如果是a则结束)*/
	{
		scanf("%d,%d,%c", &x, &y, &s);
		map[x][y] = 1;
	}
}	