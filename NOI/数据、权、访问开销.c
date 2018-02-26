#include <stdio.h>
#include <stdlib.h>

typedef struct Tree
{
	int value,data,frequency;
	struct Tree * lchild,*rchild;
}Tree;

Tree *tree_build (char *value,char *data,char *frequency,int len);
void zjinsert (char *value , char *data ,char *frequency, int len);
int tree_cost (Tree *tree);

int main (void)
{
	char value [7] = {1,2,3,4,5,6,7} , data [7] = {7,2,9,3,4,6,1} , frequency [7] = {1,2,3,4,5,6,7};
	Tree *tree = NULL;

	zjinsert (value , data , frequency , 7);
	tree = tree_build(value,data,frequency,7);
	printf ("%d",tree_cost (tree));
}

int tree_cost (Tree *tree)
{
	Tree **first_list , **last_list;
	int cost = 0;

	first_list = (Tree **) malloc (sizeof (Tree *) * 10);
	first_list [0] = tree;
	cost += first_list[0] -> frequency * 1;
	{//main
		int first_num = 1 , last_num = 0;
		int deep_num = 2;
		do 
		{
			for (int num = 0 ; num < first_num ; num ++)
			{
				if (first_list[num] -> lchild)
				{
					last_list[last_num] = first_list[num] -> lchild;
					cost += last_list[last_num] -> frequency * deep_num;
					last_num += 1;
				}
				if (first_list[num] -> rchild)
				{
					last_list[last_num] = first_list[num] -> rchild;
					cost += last_list[last_num] -> frequency * deep_num;
					last_num += 1;
				}

			}

			deep_num += 1;

			{//交换空间
				Tree **temp;

				temp = first_list;
				first_list = last_list;
				last_list = temp;

				first_num = last_num;
				last_num = 0;
			}
		}while (first_num > 0);

	}
	return cost;
}
void zjinsert (char *value , char *data ,char *frequency, int len)
{
	char temp;
	for (int num = 1 ; num < len ; num ++ )
	{
		for (int i = num - 1 ; value [i] < value [i + 1]  && i >= 0 ; i -- )
		{
			temp = value [i];
			value [i] = value[i + 1];
			value [i + 1] = temp;

			temp = data [i];
			data [i] = data [i + 1];
			data [i + 1] = temp;

			temp = frequency [i];
			frequency [i] = frequency [i + 1];
			frequency [i + 1] = temp;

		}
	}
}

Tree *tree_build (char *value,char *data,char *frequency,int len)
{
	Tree **first_list , **last_list , *tree;

	int last_point = len - 1;

	first_list = (Tree **) malloc (sizeof (Tree *) * 20);
	last_list = (Tree **) malloc (sizeof (Tree *) * 20);
	tree = (Tree *) malloc (sizeof (Tree));
 
	tree -> value = value [last_point];
	tree -> data = data[last_point];
	tree -> frequency = frequency[last_point];
	tree -> lchild = NULL , tree -> rchild = NULL;
	last_point -= 1;

	first_list [0] = tree;

	{//main

		int first_num = 1 , last_num = 0;

		do
		{
			for (int num = 0 ; num < first_num ; num ++)
			{
				if (first_list [num] -> data > data[last_point])
				{
					last_list[last_num] = (Tree *) malloc (sizeof (Tree));
					last_list[last_num] -> value = value [last_point];
					last_list[last_num] -> data = data[last_point];
					last_list[last_num] -> frequency = frequency[last_point];
					last_point -= 1;

					first_list[num] -> lchild = last_list[last_num];
					last_num += 1;
				}
				else
				{
					first_list[num] -> lchild = NULL;
				}
				if (last_point >= 0 && first_list [num] -> data < data[last_point])
				{
					last_list [last_num] = (Tree *) malloc (sizeof (Tree));
					last_list [last_num] -> value = value [last_point];
					last_list [last_num] -> data = data[last_point];
					last_list[last_num] -> frequency = frequency[last_point];
					last_point -= 1;

					first_list[num] -> rchild = last_list[last_num];
					last_num += 1;
				}
				else
				{
					first_list[num] -> rchild = NULL;
				}
			}
			Tree **temp;
			first_num = last_num;

			temp = first_list;
			first_list = last_list;
			last_list = temp;

			last_num = 0;
		}while ( (first_num > 0) && (last_point >= 0) );
		if (first_num > 0)
		{
			for ( int num = 0 ; num < first_num ; num ++ )
			{
				first_list [num] -> lchild = NULL;
				first_list [num] -> rchild = NULL;
			}
		}
		return tree;
	}
}