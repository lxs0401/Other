#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RMOVE 'R'
#define LMOVE 'L'
#define UMOVE 'U'
#define DMOVE 'D'

#define SUCCESS 1
#define FAILURE 0
int cube[6][3][3];
int need[3][3];
void init(void) //初始化魔方
{
    int x, y, z;
    for (x = 0; x < 6; x++)
    {
        for (y = 0; y < 3; y++)
        {
            for (z = 0; z < 3; z++)
            {
                cube[x][y][z] = x;
            }
        }
    }
    return;
}
void zmove(int num, char diretion)
{
    int temp[3] = {};

    if (diretion == UMOVE)
    {
        for (int i = 0; i < 3; i++)
        {
            temp[i] = cube[0][i][num];
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cube[i][j][num] = cube[i + 1][j][num];
            }
        }
        for (int i = 0; i < 3; i++)
        {
            cube[3][i][num] = temp[i];
        }
    }
    else if (diretion == DMOVE)
    {
        for (int i = 0; i < 3; i++)
        {
            temp[i] = cube[3][i][num];
        }
        for (int i = 3; i > 0; i--)
        {
            for (int j = 0; j < 3; j++)
            {
                cube[i][j][num] = cube[i - 1][j][num];
            }
        }
        for (int i = 0; i < 3; i++)
        {
            cube[0][i][num] = temp[i];
        }
    }
    if (num == 0 || num == 2)
    {
        int a[3][3];
        if (diretion == DMOVE)
        {
            if (num == 0)
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        a[i][j] = cube[4][2 - j][i];
                    }
                }
            }
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        a[i][j] = cube[5][j][2 - i];
                    }
                }
            }

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    cube[num == 0 ? 4 : 5][i][j] = a[i][j];
                }
            }
        }
        else if (diretion == UMOVE)
        {
            if (num == 0)
            {
                for (int i = 2; i >= 0; i--)
                {
                    for (int j = 2; j >= 0; j--)
                    {
                        a[i][j] = cube[4][j][2 - i];
                    }
                }
            }
            else
            {
                for (int i = 2; i >= 0; i--)
                {
                    for (int j = 2; j >= 0; j--)
                    {
                        a[i][j] = cube[5][2 - j][i];
                    }
                }
            }

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    cube[num == 0 ? 4 : 5][i][j] = a[i][j];
                }
            }
        }
    }
}
void hmove(int num, char diretion)
{
    int temp[3];
    if (diretion == LMOVE)
    {
        for (int i = 0; i < 3; i++)
        {
            temp[i] = cube[4][num][i];
        }
        for (int i = 0; i < 3; i++)
            cube[4][num][i] = cube[0][num][i];
        for (int i = 0; i < 3; i++)
            cube[0][num][i] = cube[5][num][i];
        for (int i = 0; i < 3; i++)
            cube[5][num][i] = cube[2][2-num][2-i];
        for (int i = 0; i < 3; i++)
            cube[2][2-num][2-i] = temp[i];
    }
    else if (diretion == RMOVE)
    {
        for (int i = 0; i < 3; i++)
        {
            temp[i] = cube[4][num][i];
        }
        for (int i = 0; i < 3; i++)
            cube[4][num][i] = cube[2][2-num][2-i];
        for (int i = 0; i < 3; i++)
            cube[2][2-num][2-i] = cube[5][num][i];
        for (int i = 0; i < 3; i++)
            cube[5][num][i] = cube[0][num][i];
        for (int i = 0; i < 3; i++)
            cube[0][num][i] = temp[i];
    }
    if (num == 0 || num == 2)
    {
        int a[3][3];
        if (diretion == LMOVE)
        {
            if (num == 0)
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        a[i][j] = cube[3][2 - j][i];
                    }
                }
            }
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        a[i][j] = cube[1][j][2 - i];
                    }
                }
            }

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    cube[num == 0 ? 3 : 1][i][j] = a[i][j];
                }
            }
        }
        else if (diretion == RMOVE)
        {
            if (num == 0)
            {
                for (int i = 2; i >= 0; i--)
                {
                    for (int j = 2; j >= 0; j--)
                    {
                        a[i][j] = cube[3][j][2 - i];
                    }
                }
            }
            else
            {
                for (int i = 2; i >= 0; i--)
                {
                    for (int j = 2; j >= 0; j--)
                    {
                        a[i][j] = cube[1][2 - j][i];
                    }
                }
            }

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    cube[num == 0 ? 3 : 1][i][j] = a[i][j];
                }
            }
        }
    }
}
void move(int num, char diretion, int freq)
{
    int i;
    for (i = 0; i < freq; i++)
    {
        switch (diretion)
        {
        case RMOVE:
        case LMOVE:
            hmove(num, diretion);
            break;
        case UMOVE:
        case DMOVE:
            zmove(num, diretion);
            break;
        }
    }
}
int decide(void)
{
    for (int x = 0; x < 3; x++)
    {
        int s = cube[x][0][0];
        for (int y = 0; y < 3; y++)
        {
            for (int z = 0; z < 3; z++)
            {
                if (cube[x][y][z] != s)
                {
                    return FAILURE;
                }
            }
        }
    }
    return SUCCESS;
}
int enumerate(int step, int all, char up)
{

    if (decide() == SUCCESS)
        return SUCCESS;
    else if (step <= all)
    {
        for (int x = 0; x < 3 && up != RMOVE; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                move(x, RMOVE, y);
                if (enumerate(step + 1, all, RMOVE) == SUCCESS)
                {
                    if (y != 0)
                        printf("no.%d\tright\t%d\n", x, y);
                    return SUCCESS;
                }
                move(x, LMOVE, y);
            }
        }
        for (int x = 0; x < 3 && up != DMOVE; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                move(x, DMOVE, y);
                if (enumerate(step + 1, all, DMOVE) == SUCCESS)
                {
                    if (y != 0)
                        printf("no.%d\tdown\t%d\n", x, y);
                    return SUCCESS;
                }
                move(x, UMOVE, y);
            }
        }
    }
    return FAILURE;
}
int main()
{
    init();
    int num, freq;
    char diretion;
    while (scanf("%d %c %d", &num, &diretion, &freq) != EOF)
    {
        getchar();
        move(num, diretion, freq);
        for (int x = 0; x < 6; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                for (int z = 0; z < 3; z++)
                {
                    printf("%d ", cube[x][y][z]);
                }
                printf("\n");
            }
            printf("\n");
        }
        printf("\n");
    }
    enumerate(0, 20, 0);
}