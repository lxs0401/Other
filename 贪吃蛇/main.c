#include "SDL/SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define DOWN  0
#define UP    1
#define LEFT  2
#define RIGHT 3
typedef struct python 
{
	int x , y;
	struct python *next;
}*python;

int xx = 0 , yy = 0;
int zt = 4 ;

char cwjc(python s_weiz)
{
	python point = s_weiz , list = s_weiz;
	if (s_weiz == NULL) return 0;
	while (list -> next != NULL)
	{
		/*if ( (list -> x > 20) || (list -> y > 20) || (list -> y < 0) || (list -> x < 0) )
		{
			return 1;
		}*/
		while ( (point != list) && (point -> next != NULL) )
		{
			if ( (point -> x == list -> x) && (point -> y == list -> y) )
			{
				return 1;
			}
			point = point -> next;
		}
		point = s_weiz;
		list = list -> next;
	}
	return 0;
}
python cl_ah (python s_weiz , int anjian )
{
	python list = s_weiz , point , perent;
	
	if (list == NULL)
	{
		list = ( python ) malloc (sizeof (struct python)) ;
		point = list;
		for (int x = 10 ; x < 15 ; x++ )
		{
			point -> next = ( python ) malloc ( sizeof ( struct python ) ) ;
			point = point -> next;
			point -> x = x;
			point -> y = 10;
		}
		point -> next = NULL;
		list = list -> next;
		return list;
	}
	
	point = list;
	while (point -> next != NULL)
	{
			perent = point;
			point = point -> next;
	}
	
	if (anjian == UP)
	{
		point -> next = ( python ) malloc ( sizeof ( struct python ) ) ;
		perent = perent -> next;
		point = point -> next;
		if (perent -> y - 1 < 0)
		{
			point -> y = 20;
		}
		else
		{
			point -> y = perent -> y - 1;
		}
		point -> x = perent -> x;
		point -> next = NULL;
	}
	else if (anjian == DOWN)
	{
		point -> next = ( python ) malloc ( sizeof ( struct python ) ) ;
		perent = perent -> next;
		point = point -> next;
		if (perent -> y + 1 > 20)
		{
			point -> y = 0;
		}
		else
		{
			point -> y = perent -> y + 1;
		}
		point -> x = perent -> x;
		point -> next = NULL;
	}
	else if (anjian == LEFT)
	{
		point -> next = ( python ) malloc ( sizeof ( struct python ) ) ;
		perent = perent -> next;
		point = point -> next;
		if (perent -> x - 1 < 0)
		{
			point -> x = 20;
		}
		else
		{
			point -> x = perent -> x - 1;
		}
		point -> y = perent -> y;
		point -> next = NULL;
	}
	else if (anjian == RIGHT)
	{
		point -> next = ( python ) malloc ( sizeof ( struct python ) ) ;
		perent = perent -> next;
		point = point -> next;
		if (perent -> x + 1 > 20)
		{
			point -> x = 0;
		}
		else
		{
			point -> x = perent -> x + 1;
		}
		point -> y = perent -> y;
		point -> next = NULL;
	}
	
	if (point -> x != xx || point -> y != yy)
	{
		list = list -> next;
	}
	else
	{
		xx = 0;
		yy = 0;
	}
	return list;
}
int SDL_main(int argc, char *argv[])
{
	python s_weiz = NULL , point;
	SDL_Surface *windows = NULL , *snack = NULL , *desktop = NULL;
	SDL_Surface *g_over = NULL;
	SDL_Event shijian;
	SDL_Rect z_biao;
	
	
	SDL_Init( SDL_INIT_EVERYTHING ); //初始化
	windows = SDL_SetVideoMode( 360, 360, 32, SDL_SWSURFACE );
	
	desktop = SDL_LoadBMP (".\\desktop.bmp");
	snack = SDL_LoadBMP (".\\snack.bmp");
	g_over = SDL_LoadBMP (".\\g_over.bmp");
	SDL_BlitSurface(desktop,NULL,windows,NULL);
	SDL_Flip( windows );
	while (1) //检测事件
	{
		if ( SDL_PollEvent( &shijian ) )
		{
			if( shijian.type == SDL_KEYDOWN )
			{
				switch ( shijian . key . keysym . sym )
				{
					case SDLK_UP:
						if (zt != DOWN)
						{
							zt = UP;
							s_weiz = cl_ah (s_weiz , UP);
						}
						break;
					case SDLK_DOWN:
						if (zt != UP)
						{
							zt = DOWN;
							s_weiz = cl_ah (s_weiz , DOWN);
						}
						break;
					case SDLK_LEFT:
						if (zt != RIGHT)
						{
							zt = LEFT;
							s_weiz = cl_ah (s_weiz , LEFT);
						}
						break;
					case SDLK_RIGHT:
						if (zt != LEFT)
						{
							zt = RIGHT;
							s_weiz = cl_ah (s_weiz , RIGHT);
						}
						break;
				}
			}else if (shijian.type == SDL_QUIT)
			{
				SDL_Quit();
				return 0;
			}
		}
		else if (s_weiz != NULL )
		{
			s_weiz = cl_ah (s_weiz , zt);
		}
		
		if (xx == 0 && yy == 0)
		{
			srand((int)time(NULL));
			xx = rand () % 20;
			yy = rand () % 20;
		}

		if (cwjc (s_weiz))
		{
			
			SDL_BlitSurface (g_over , NULL , windows , NULL);
			SDL_Flip ( windows );
			/*SDL_Delay (3000);
			SDL_Quit();
			return 0;*/
			zt = 4;
			s_weiz = NULL;
			continue;
			
		}
		point = s_weiz;
		if (point != NULL)
		{
			SDL_BlitSurface (desktop , NULL , windows , NULL);
			while (point -> next != NULL)
			{
				z_biao . x = point -> x * 18;
				z_biao . y = point -> y * 18;
				SDL_BlitSurface ( snack , NULL , windows , &z_biao );
				point = point -> next;
			}
			if (xx != 0 || yy != 0)
			{
				z_biao . x = xx * 18;
				z_biao . y = yy * 18;
				SDL_BlitSurface ( snack , NULL , windows , &z_biao );
			}
			SDL_Flip( windows );
		}

		SDL_Delay (100);
	}
}