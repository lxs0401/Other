#include <stdio.h>
#include <stdlib.h>
int num = 0;
int p_duan (char moto[8])
{
	for (int n = 0 ; n < 8 ; n ++)
	{
		for (int a = 0 ; a < 8 ; a ++)
		{
			if (n != a && moto [n] == moto [a] )
			{
				return 0;
			}
		}
		
		int b1 = n, b2 = moto[n];
		
		while (b1 > 0 && b2 > 0)
		{
			b1 -= 1 , b2 -= 1;
		}
		while (b1 < 8 && b2 < 8)
		{
			if ( b1 != n  && moto[b1] == b2)
			{
				return 0;
			}
			b1 += 1 , b2 += 1;
		}
		
		

		int c1 = n, c2 = moto[n];
		while (c1 > 0 && c2 < 6)
		{
			c1 -= 1 , c2 += 1;
		}
		while (c1 < 8 && c2 >= 0)
		{
			if ( c1 != n  && moto [c1] == c2 )
			{
				return 0;
			}
			c1 += 1 , c2 -= 1;
		}
	}
	for (int x = 0 ; x < 8 ; x ++)
	{
		for (int y = 0 ; y < 8 ; y ++)
		{
			if (moto [x] == y)
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
		}
		printf ("\n");
	}
	printf ("\n");
	num += 1;
	return 1;
}
int main ()
{

	char moto [8] = {0};
	int n = 0;
	while (n <= 7)
	{
		while (moto [n] == 7)
		{
			moto [n] = 0;
			n += 1;
		}
		if (n < 8)
		{
			moto [n] += 1;
			n = 0;
			p_duan(moto);
		}
	}
	printf ("%d",num);
}