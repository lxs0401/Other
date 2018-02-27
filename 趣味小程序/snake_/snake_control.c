#include "snake.h"

void initialize (struct snake_farm *p)
{
	srand ((int)time(NULL));
	p -> food_x = rand () % 40;
	p -> food_y = rand () % 20;
	p -> who_set = OTHER;
	for (int y = 0 ; y < 20 ; y ++)
	{
		for (int x = 0 ; x < 40 ; x ++)
		{
			p -> farm [y][x] = NOTHING;
		}
	}
	return ;
}
char button_status (struct snake *p , char action)
{
	struct snake *child,*perent;
	child = p;
	while (child -> next != NULL)
	{
		perent = child;
		child = child -> next;
	}
	if (action == LEFT)
	{
		if (perent -> x == child -> x - 1)
			return 1;
	}
	else if (action == RIGHT)
	{
		if (perent -> x == child -> x + 1)
			return 1;
	}
	else if (action == DOWN)
	{
		if (perent -> y == child -> y + 1)
			return 1;
	}
	else if (action == UP)
	{
		if (perent -> y == child -> y - 1)
			return 1;
	}
	return 0;
}
char snake_loss_status (struct snake *p)
{
	struct snake *up , *down;
	for (up = p ; up != NULL ; up = up -> next)
	{
		if (up -> x >= 40 || up -> y >= 20 || up -> x < 0 || up -> y < 0)
		{
			return LOSS;
		}
		for (down = p ; (down != up) && (down != NULL) ; down = down -> next)
		{
			if (down -> x == up -> x && down -> y == up -> y)
			{
				return LOSS;
			}
		}
	}
	return 2;
}
char line_snake (struct snake_farm *p , char action)
{
	static struct snake * snake_master = NULL , *backup ,*perent;
	if (snake_master == NULL)
	{
		initialize (p);
		backup = snake_master = (struct snake *) malloc (sizeof (struct snake));
		for (int x = 7 ; x < 12 ; x ++)
		{
			backup -> next = (struct snake *) malloc (sizeof (struct snake));
			perent = backup;
			backup = backup -> next;
			p -> farm [10][x] = BUTTON;
			backup -> x = x;
			backup -> y = 10;
		}
		backup -> next = NULL;
		snake_master = snake_master -> next;
	}else
	{
		if (button_status(snake_master,action))
		{
			return BLOCK;
		}
		backup -> next = (struct snake *) malloc (sizeof (struct snake));
		perent = backup;
		backup = backup -> next;
		if (action == LEFT)
		{
			backup -> x = perent -> x - 1;
			backup -> y = perent -> y;
		}
		else if (action == RIGHT)
		{
			backup -> x = perent -> x + 1;
			backup -> y = perent -> y;
		}
		else if (action == DOWN)
		{
			backup -> y = perent -> y + 1;
			backup -> x = perent -> x;
		}
		else if (action == UP)
		{
			backup -> y = perent -> y - 1;
			backup -> x = perent -> x;
		}
	
		backup -> next = NULL;
		if (snake_loss_status(snake_master) == LOSS)
		{
			snake_master = NULL;
			return LOSS;
		}
		if ( (backup -> x == p -> food_x) && (backup -> y == p -> food_y) )
		{
			srand ((int)time(NULL));
			p -> food_x = rand () % 40;
			p -> food_y = rand () % 20;
		}
		else
		{
			p -> farm [snake_master -> y][snake_master -> x] = NOTHING;
			snake_master = snake_master -> next;
		}
		p -> farm [backup -> y][backup -> x] = BUTTON;
		if (backup -> x >= 20)
		{
			p -> who_set = BLUE;
		}
		else
		{
			p -> who_set = RED;
		}
	}
	return 2;
}