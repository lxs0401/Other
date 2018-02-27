#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 1
#define FAIL    0
#define MALLOC(x, y) ((x *)malloc(sizeof(x) * y))
void init(int ***xyz,int status)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = status ; k < 10; k++)
            {
                xyz[i][j][k] = 0;
            }
        }
    }
    return;
}
void updata(int ***xyz)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 9; k++)
            {
                if (xyz[i][k][0] > 0)xyz[i][j][xyz[i][k][0]] = 1;
                if (xyz[k][j][0] > 0)xyz[i][j][xyz[k][j][0]] = 1;
            }
            for (int k = i / 3 * 3; k < i / 3 * 3 + 3; k++)
            {
                for (int l = j / 3 * 3; l < j / 3 * 3 + 3; l++)
                {
                    if(xyz[k][l][0] > 0)xyz[i][j][xyz[k][l][0]] = 1;
                }
            }
        }
    }
}

int search(int ***xyz)
{
    init(xyz,1);
    updata(xyz);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (xyz[i][j][0] == 0)
            {
                for (int k = 1; k <= 9; k++)
                {
                    if (xyz[i][j][k] == 0)
                    {
                        xyz[i][j][0] = k;
                        if(search(xyz) == SUCCESS)return SUCCESS;
                        xyz[i][j][0] = 0;
                        init(xyz,1);
                        updata(xyz);
                    }
                }
                return FAIL;
            }
        }
    }
    return SUCCESS;
}
int main ()
{
    int ***xyz = MALLOC(int **,11);
    int T,t;
    for (int i = 0 ; i < 11 ; i ++)
    {
        xyz[i] = MALLOC(int *,11);
        for (int j = 0 ; j < 11 ; j ++)
        {
            xyz[i][j] = MALLOC(int,11);
        }
    }
    scanf("%d",&T);
    for (t = 0 ; t < T ; t ++)
    {
        init(xyz,0);
        for (int i = 0 ; i < 9 ; i ++)
        {
            for (int j = 0 ; j < 9 ; j ++)
            {
                scanf("%d",&xyz[i][j][0]);
            }
        }
        search(xyz);
        printf("\n");
        for (int i = 0 ; i < 9 ; i ++)
        {
            for (int j = 0 ; j < 9 ; j ++)
            {
                printf("%d ",xyz[i][j][0]);
            }
            printf("\n");
        }
    }
}