#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Z_X 10
#define Z_y 10

#define X_S 15
#define Y_S 40
int main (void)
{
    char x_y[X_S][Y_S] = {0};
    int xx = 0 , yy = 0;

    for (int x = 0 ; x < X_S ; x ++)
    {
        for (int y = 0 ; y < Y_S ; y ++)
        {
            xx = abs(x - Z_X) * abs (x - Z_X); 
            yy = abs (y - Z_y) * abs (y - Z_y);
            if (sqrt(xx + yy) <= Z_X )
            {
                x_y[x][y] = 1;
                x_y[x][y+19] = 1;
            }
        }
    }

    for (int x = 0 ; x < X_S ; x ++)
    {
        for (int y = 0 ; y < Y_S ; y ++)
        {
            if (x_y[x][y] == 1)
            {
                printf ("* ");
            }
            else
            {
                printf ("  ");
            }
        }
        printf("\n");
    }
    for (int x = 37 ; x >= 0; x -= 2)
    {
        for (int y = 39 - x ; y >= 0 ; y --)
        {
            printf (" ");
        }
        for (int y = 0 ; y < x ; y ++)
        {
            printf ("* ");
        }
        printf ("\n");
    }
}