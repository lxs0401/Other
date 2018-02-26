#include "client.h"


char referee (char checkerboard[15][15])
{
	int h_num = 0 , s_num = 0 , x_num = 0 , xx_num = 0;
	for (int y = 0 ; y < 15 ; y ++)
	{
		for (int x = 0 ;x < 15 ; x ++)
		{
			for (int h = 0 ; (checkerboard[y][x] != NOTHING) && h < 5 ; h ++)
			{
				if (h + x < 15)
				{
					h_num = ( checkerboard [y][x] == checkerboard[y][h + x] ) ? (h_num + 1) : 0;
				}
				if (h + y < 15)
				{
					s_num = ( checkerboard [y][x] == checkerboard[h + y][x] ) ? (s_num + 1) : 0;
				}
				if ( (h + y < 15) && (h + x < 15) )
				{
					x_num = ( checkerboard [y][x] == checkerboard[h + y][h + x] ) ? (x_num + 1) : 0;
				}
				if ( (y + h < 15) && (x - h >= 0) )
				{
					xx_num = ( checkerboard [y][x] == checkerboard[y + h][x - h] ) ? (xx_num + 1) : 0;
				}
			}
			if (h_num >= 4 || s_num >= 4 || x_num >= 4 || xx_num >= 4)
			{
				return 0;
			}
			else
			{
				h_num = 0 , s_num = 0 , x_num = 0 , xx_num = 0;
			}
		}
	}
	return 1;
}