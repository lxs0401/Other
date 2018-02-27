#include "client.h"

int update_qipan (char checkerboard[15][15])
{
	SDL_Surface *desktop , *w_piece , *b_piece ;
	SDL_Rect x_y;
	

	desktop = SDL_LoadBMP("./1.bmp");
	b_piece = SDL_LoadBMP("./2.bmp");
	w_piece = SDL_LoadBMP("./3.bmp");
	if (windows == NULL)
	{
		windows = SDL_SetVideoMode( 480, 480 , 32, SDL_SWSURFACE );
	}
	SDL_BlitSurface(desktop,NULL,windows,NULL);
	for (int y = 0 ; y < 15 ; y ++)
	{
		for (int x = 0 ; x < 15 ; x ++)
		{
			if (checkerboard[y][x] == BLACK)
			{
				x_y . x = x * 32;
				x_y . y = y * 32;
				SDL_BlitSurface(b_piece , NULL , windows , &x_y);
			}
			else if (checkerboard[y][x] == WHITE)
			{
				x_y . x = x * 32;
				x_y . y = y * 32;
				SDL_BlitSurface(w_piece , NULL , windows , &x_y);
			}
		}
	}
	SDL_Flip( windows );
	return 1;
}

struct message * luozi ( struct channel *mult)
{
	
	SDL_Event shijian;
	struct message *mess;
	int x , y ;
	if (windows == NULL)
	{
		windows = SDL_SetVideoMode( 480, 480 , 32, SDL_SWSURFACE );
	}
	mess = (struct message *) malloc (sizeof (struct message));
	
	
	update_qipan (mult -> checkerboard );
	
	while (1)
	{
		if ( SDL_PollEvent( &shijian ) )
		{
			if( shijian.type == SDL_MOUSEBUTTONDOWN )
			{
				//如果鼠标左键被按下了
				if( shijian.button.button == SDL_BUTTON_LEFT )
				{
					x = shijian. button . x;
					y = shijian . button . y;
					x /= 32;
					y /= 32;
					mess -> x = x;
					mess -> y = y;
					mess -> channel_num = mult -> channel_num;
					mess -> b_or_w = mult -> b_or_w;
					mess -> request = MAKE;
					return mess;
				}
			}
		}
	}
	
}