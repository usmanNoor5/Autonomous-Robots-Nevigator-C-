#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#define GridSize 12
#define Pop 400// will control numberr of Pop
int chromosome[Pop][GridSize], D_B[Pop], O_B[Pop], pt_leng[Pop], path[GridSize * GridSize][2], length;
float fitness[Pop];
float pathlen[Pop], inf_step[Pop], turns[Pop];
int grid[GridSize][GridSize] =
{{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
{0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
{0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0},
{0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
{1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};



void show_value(float fitness[Pop], int chromosome[Pop][GridSize]);
void ramdom_population(int chromosome[Pop][GridSize]);
void evaluate(float arr[Pop], int maxi, int mini);
void fitness_value(float fitness[Pop], int chromosome[Pop][GridSize], int k, int sol_fond);
void maxi_mini(float arr[Pop]);
void evaluate(float arr[Pop], int maxi, int mini);
void fitnes(float pathlen[Pop], float turns[Pop], float inf_step[Pop]);
void sort_swap(float fitness[Pop], int chromosome[Pop][GridSize]);
void cross_over(int chromosome[Pop][GridSize]);
void mutation(int chromosome[Pop][GridSize]);
void Display_sol(int sol_fond, int O_B[Pop], int D_B[Pop], int pt_leng[Pop]);
void Display_Solution(int grid[GridSize][GridSize], int path[length][2], int pt_leng[Pop], int sol_fond);
int check_func(int intra);
void CC_RR();
//
int random_1_0();
void CC_RR()
{for (int k = 0; k < Pop; k++)
    {   O_B[k] = random_1_0();
        D_B[k] = random_1_0();
        D_B[k] = random_1_0();
        fitness_value(fitness, chromosome, k, 3);}
    maxi_mini(pathlen);
    maxi_mini(turns);
    maxi_mini(inf_step);
    fitnes(pathlen, turns, inf_step);}
    int check_func(int itra)
{    if (fitness[0] == 400) return 0;
    else if (itra >= Pop / 5)
    {  for (int i = 0; i < 4; i++)
        {  
            // if (inf_step[i]>=0.95&& turns[i]>=0.90) return i;
             if (inf_step[i] == 1 )return i;
        }
    }
    return 3;
}
/* This function will generate a random value according to the parameters. But the first value
of Row is always = 0; & the last value will be GridSize-1 */
void ramdom_population(int chromosome[Pop][GridSize])
{   for (int i = 0; i < Pop; i++)
    {   chromosome[i][0] = 0;
        for (int j = 1; j < GridSize - 1; j++)
        {chromosome[i][j] = ((rand() % GridSize));
        }
        chromosome[i][GridSize - 1] = GridSize - 1; 
    }
}
/*This is the function to evaluate the formulas given in Atonomous Robot.pdf. For
Infeasible steps,path_length & Number of turns. The general formula is f = 1-((S-Smi)/(Sma-Smi))*/
void fitness_value(float fitness[Pop], int chromosome[Pop][GridSize], int k, int sol_fond)
{   if (sol_fond != 3)
    {   length = pt_leng[sol_fond];
        path[length][2];}
    int turn = 0, j = 0, paths = 0, infesi = 0;
    // loop for the number of turns
    int num = 0;
    turn = 0;
    for (int j = 0; j < GridSize - 1; j++)
    { if (chromosome[k][j] != chromosome[k][j + 1]) turn++;}
    turns[k] = turn;
    /*If O_B (Orientation Bit )=1 then that individual chromosome will check for
    column wise. else Row wise. Moreover, for column wise if D_B (direction bit ) =1
    then it will check for column first other wise row first.On the other hand for
     Row Wise if D_B =1 then it will check for Row First other wise Column First. */
    paths = 0;
    infesi = 0;
    if (O_B[k] == 1) /*For Column First Orientation Bit = 1*/
    {   if (D_B[k] == 1) /*Column wise,D.B = 1 means(Column First) */
        {   j = 0;
            for (int i = 0; i < GridSize; i)
            {     if (i == chromosome[k][j + 1] && (j + 1 != GridSize || i + 1 != GridSize))
                {   j++;
                    if (grid[i][j] == 1)infesi++;
                    path[num][0] = i;
                    path[num][1] = j;
                    num++;
                    paths++;}
                else if (i != chromosome[k][j + 1] && (j + 1 != GridSize || i + 1 != GridSize))
                {if (chromosome[k][j] - chromosome[k][j + 1] > 0)
                    {   i--;
                        if (grid[i][j] == 1)infesi++;
                        path[num][0] = i;
                        path[num][1] = j;
                        num++;
                        paths++;}
                    else if (chromosome[k][j] - chromosome[k][j + 1] < 0)
                    {   i++;
                        if (grid[i][j] == 1)infesi++;
                        path[num][0] = i;
                        path[num][1] = j;
                        num++;
                        paths++;
                    }
                }
                else break;}}
        else /*column wise D.B =0 means(row first)*/
        {    j = 0;
            for (int i = 0; i < GridSize; i)
            {if (i == chromosome[k][j] && (i + 1 != GridSize || j + 1 != GridSize))
                {   j++;
                    if (grid[i][j] == 1) infesi++;
                    path[num][0] = i;
                    path[num][1] = j;
                    num++;
                    paths++;
                }
                else if (i != chromosome[k][j] && (j + 1 != GridSize || i + 1 != GridSize))
                { if (chromosome[k][j - 1] - chromosome[k][j] > 0)
                    {   i--;
                        if (grid[i][j] == 1) infesi++;
                        path[num][0] = i;
                        path[num][1] = j;
                        num++;
                        paths++;
                    }
                    else if (chromosome[k][j - 1] - chromosome[k][j] < 0)
                    {   i++;
                        if (grid[i][j] == 1) infesi++;
                        path[num][0] = i;
                        path[num][1] = j;
                        num++;
                        paths++;
                    }
                }
                else break;
            }
        }
    }
    else /*For Row Wise Orinentation bit =0 */
    {  if (D_B[k] == 1) /*row first of row wise means D.B =1,by interchanging the values of colume first colume wise D.B =1*/
        {j = 0;
            for (int i = 0; i < GridSize; i)
            {if (j == chromosome[k][i + 1] && (j + 1 != GridSize || i + 1 != GridSize))
                { i++;
                    if (grid[i][j] == 1) infesi++;
                    path[num][0] = i;
                    path[num][1] = j;
                    num++;
                    paths++;
                }
                else if (j != chromosome[k][i + 1] && (j + 1 != GridSize || i + 1 != GridSize))
                {   if (chromosome[k][i] - chromosome[k][i + 1] > 0)
                    {  j--;
                        if (grid[i][j] == 1) infesi++;
                        path[num][0] = i;
                        path[num][1] = j;
                        num++;
                        paths++;
                    }
                    else if (chromosome[k][i] - chromosome[k][i + 1] < 0)
                    { j++;
                        if (grid[i][j] == 1) infesi++;
                        path[num][0] = i;
                        path[num][1] = j;
                        num++;
                        paths++;
                    }
                }
                else break;
            }
        }
        else /*column first of row wise means D.B =0,by interchanging the values of row first colume wise D.B =0*/
        {    j = 0;
            for (int i = 0; i < GridSize; i)
            { if (j == chromosome[k][i] && (i + 1 != GridSize || j + 1 != GridSize))
                {    i++;
                    if (grid[i][j] == 1) infesi++;
                    path[num][0] = i;
                    path[num][1] = j;
                    num++;
                    paths++;}
                else if (j != chromosome[k][i] && (j + 1 != GridSize || i + 1 != GridSize))
                { if (chromosome[k][i - 1] - chromosome[k][i] > 0)
                    {   j--;
                        if (grid[i][j] == 1) infesi++;
                        path[num][0] = i;
                        path[num][1] = j;
                        num++;
                        paths++;}
                    else if (chromosome[k][i - 1] - chromosome[k][i] < 0)
                    { j++;
                        if (grid[i][j] == 1) infesi++; 
                     path[num][0] = i;
                        path[num][1] = j;
                        num++;
                        paths++; 
                    }
                }
                else break;
            }
        }
    }
    pathlen[k] = paths;
    pt_leng[k] = paths;
    inf_step[k] = infesi;}
void show_value(float fitness[Pop], int chromosome[Pop][GridSize])
{    printf("\n\t     paths length   \tinfeasible step\t Turns\tOrientationBit\tDirectionBit\tFitness\t\tpt_leng\n");
    for (int i = 0; i < Pop; i++)
    {   for (int j = 0; j < GridSize; j++)
        {            printf("%d", chromosome[i][j]);}
        printf("\n\t             %.2f\t%.2f\t         %.2f\t%d\t\t%d\t\t %.4f  \t%d", pathlen[i], inf_step[i], turns[i], O_B[i], D_B[i], fitness[i], pt_leng[i]);
        printf("\n");
    }
}
/*This function will give the maximum and minimum values of an array which can be pathlen[Pop],
Turns[Pop],Infesible[Pop].Then this function will go to evaluate  */
void maxi_mini(float arr[Pop])
{  int mini = arr[0], maxi = arr[0];
    if (arr[0] == inf_step[0]) mini = 0;
    for (int i = 0; i < Pop; i++)
    {if (maxi < arr[i]) maxi = arr[i]; 
        if (mini > arr[i]) mini = arr[i];}
    evaluate(arr, maxi, mini);
}
/*This function which is call in maxi_mini() will new value to array,that array which
is called in maxi_mini() according to the given Formula
func = 1 - ((arr[i] - mini) / (maxi - mini)) */
void evaluate(float arr[Pop], int maxi, int mini)
{float func;
    for (int i = 0; i < Pop; i++)
    {  func = 1 - ((arr[i] - mini) / (maxi - mini));
        arr[i] = func;
    }
}
/*This Function will give the fitness value. If the fitness value is 1200 then
that chromosome is fittess in his population*/
void fitnes(float pathlen[Pop], float turns[Pop], float inf_step[Pop])
{float inter = 0;
    for (int i = 0; i < Pop; i++)
    { // inter = (pathlen[i] + turns[i] + inf_step[i]) / 3;
        inter = (100 * 4 * inf_step[i]) * ((2 * turns[i] + 2 * pathlen[i]) / (2 + 2));
        fitness[i] = inter;
    }
}
/*This function will swap the values according to the fitness. The more the fit
value is the more it will go higher */
void sort_swap(float fitness[Pop], int chromosome[Pop][GridSize])
{ float swap; int arr_swap[GridSize];
    for (int j = 0; j < Pop; j++)
    {for (int i = Pop - 1; i >= 1; i--)
        { if (fitness[i] > fitness[i - 1])
            {swap = fitness[i - 1];
            fitness[i - 1] = fitness[i]; 
            fitness[i] = swap;
            swap = pathlen[i - 1];
             pathlen[i - 1] = pathlen[i];
             pathlen[i] = swap;
            swap = inf_step[i - 1]; 
            inf_step[i - 1] = inf_step[i];
            inf_step[i] = swap;
            swap = turns[i - 1];
            turns[i - 1] = turns[i];
            turns[i] = swap;
            swap = D_B[i - 1];
            D_B[i - 1] = D_B[i];
            D_B[i] = swap;
            swap = O_B[i - 1];
            O_B[i - 1] = O_B[i];
            O_B[i] = swap;
            swap = pt_leng[i - 1];
            pt_leng[i - 1] = pt_leng[i];
            pt_leng[i] = swap;
                for (int k = GridSize - 1; k >= 0; k--)
                { arr_swap[k] = chromosome[i - 1][k];
                    chromosome[i - 1][k] = chromosome[i][k];
                    chromosome[i][k] = arr_swap[k];
                }
            }
        }
    }
}
/*This function will do the cross_over like select the parent which are more fit
then swap it with the cross_over_pt ehich is half of the population
This will swap in such a wat that the first half of the first chromosome and the
second half of the second chromosome will make a new daughter chromosome.*/
void cross_over(int chromosome[Pop][GridSize])
{    int crossover_pt = Pop % 2 == 0 ? Pop / 2 : (Pop - 1) / 2;
    srand(time(NULL) * getpid());
    int pt = rand() % GridSize;
    for (int i = 0; i < crossover_pt; i = i + 2)
    { for (int j = 0; j < GridSize / 2; j++)
        {chromosome[crossover_pt + i][j] = chromosome[i][j];
        chromosome[crossover_pt + i + 1][j] = chromosome[i + 1][j];}
        for (int k = pt; k < GridSize; k++)
        { chromosome[crossover_pt + i][k] = chromosome[i + 1][k];
            chromosome[crossover_pt + i + 1][k] = chromosome[i][k];}}}
/*This function will mutate means change any random value from any ramdom place in a chromosome */
void mutation(int chromosome[Pop][GridSize])
{   int value, index;
    for (int i = 0; i < Pop; i = i + 3)
    {    index = (rand() % GridSize);
        if (index == 0 || index == GridSize - 1) continue;
        value = (rand() % GridSize);
        chromosome[i][index] = value;
    }
}
/*This will generate a random Number which may be 0 or 1 */
int random_1_0()
{if (rand() % 2 == 0) return 0;
else return 1;}
void Display_Solution(int grid[GridSize][GridSize], int path[length][2], int pt_leng[Pop], int sol_fond)
{    int length = pt_leng[sol_fond];
    const char emptySpace = ' ';
    const char obstacle = 178;
    const char start = 219;
    const char goal = 219;
    const char rStep = 46;
    char sGrid[GridSize][GridSize];
    for (int i = 0; i < GridSize; i++)
    { for (int j = 0; j < GridSize; j++)
        { if (grid[i][j] == 0) sGrid[i][j] = ' ';
        else if (grid[i][j] == 1) sGrid[i][j] = obstacle;
        }}
        sGrid[0][0] = 'X';
    for (int i = 0; i < length; i++)
    { if(grid[path[i][0]][path[i][1]]==1)sGrid[path[i][0]][path[i][1]] = '.';
        else sGrid[path[i][0]][path[i][1]] = 'X';
        printf("(%d,%d)", path[i][0], path[i][1]); }
    sGrid[GridSize - 1][GridSize - 1] = 'X';
    printf(" \n---------------------------------");
    for (int i = 0; i < GridSize; i++)
    {printf("\n%2d|", i);
     for (int j = 0; j < GridSize; j++)
        {printf("%c", sGrid[i][j]);
            printf("|");}}
    printf("\n ----------------------------------\n");
    for (int i = 0; i < GridSize; i++)
    { printf("%3d", i);}
    printf("\n");}
// END OF PROGRAM