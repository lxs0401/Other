#include "snake_client.h"
void update_farm (struct snake_farm *pool , SDL_Surface *windows , char name)
{
	SDL_Surface *desktop , * snake;
	SDL_Rect x_y;
	desktop = SDL_LoadBMP (".\\desktop.bmp");
	snake = SDL_LoadBMP (".\\snake.bmp");
	SDL_BlitSurface (desktop , NULL , windows , NULL);
	int add ;
	add = (name == RED) ? 0 : 20;
	for (int y = 0 ; y < 20 ; y ++)
	{
		for (int x = add; x < add + 20 ; x ++)
		{
			if (pool -> farm[y][x] == BUTTON)
			{
				x_y . y = y * 18;
				x_y . x = (x - add) * 18;
				SDL_BlitSurface (snake , NULL , windows , &x_y);
			}
		}
	}
	if ((name == BLUE) && (pool -> food_x >= 20))
	{
		x_y . x = (pool -> food_x - 20) * 18;
		x_y . y = pool -> food_y * 18;
	}
	else if ((name == RED) && (pool -> food_x < 20))
	{
		x_y . x = pool -> food_x * 18;
		x_y . y = pool -> food_y * 18;
	}
	SDL_BlitSurface (snake , NULL , windows , &x_y);
	SDL_Flip( windows );
}
char get_action (void)
{
	SDL_Event shijian;
	if ( SDL_PollEvent( &shijian ) )
	{
		if( shijian.type == SDL_KEYDOWN )
		{
			switch ( shijian . key . keysym . sym )
			{
				case SDLK_UP:
					return UP;
				case SDLK_DOWN:
					return DOWN;
				case SDLK_LEFT:
					return LEFT;
				case SDLK_RIGHT:
					return RIGHT;
			}
		}
	}
	return OTHER;
}