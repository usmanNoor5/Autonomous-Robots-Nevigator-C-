#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#define N_Q 8
#define ROWS 10
int chromosome[ROWS][N_Q];
int fitness[ROWS]; // Where ROWS is  the population & N_Q is the Number of Queens
void random_population(int chromosome[ROWS][N_Q]);
void fitness_value(int fitness[ROWS], int chromosome[ROWS][N_Q]);
void show_value(int fitness[ROWS], int chromosome[ROWS][N_Q]);
void sort_swap(int fitness[ROWS], int chromosome[ROWS][N_Q]);
void cross_over(int chromosome[ROWS][N_Q]);
int is_solution_found(int fitness[ROWS]);
void mutation(int chromosome[ROWS][N_Q]);
int main()
{
    int itra = 0;
    int solfond = 0;
    random_population(chromosome);
    fitness_value(fitness, chromosome);

    while (itra < 1000 && solfond == 0)
    {
        itra++;
        sort_swap(fitness, chromosome);
        show_value(fitness, chromosome);
        cross_over(chromosome);
        mutation(chromosome);
        fitness_value(fitness, chromosome);

        

        solfond = is_solution_found(fitness);

        printf("\n\n\n\n");
    }
    if (solfond == 1)
    {
        show_value(fitness, chromosome);
        printf("\nSolution found in %d generation\n", itra);
    }
    else if (solfond == 0)
    {
        printf("\nSolution is not found in 1000 generation\n");
    }

    return 0;
}
/*Generate random on each rows according to ROWS That is define above.This puts each queen in each columns
without repeating it. */
void random_population(int chromosome[ROWS][N_Q])
{
    srand(time(NULL));
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < N_Q; j++)
        {
            chromosome[i][j] = ((rand() % N_Q) + 1);
        }
    }
}
/*This check the fitness means all the possible condition for each queen that can attack on another queens
and also gives the number of attack by all the queens. if the attack is zero then we get the desire solution
of our n-queen problem */
void fitness_value(int fitness[ROWS], int chromosome[ROWS][N_Q])
{
    // This chech the number of Attacking Rows0000
    int fitness_value = 0;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < (N_Q); j++)
        {
            for (int k = j + 1; k < (N_Q); k++)
            {
                if (chromosome[i][j] == chromosome[i][k])
                {
                    fitness_value++;
                }
            }
        }
        fitness[i] = fitness_value;
        fitness_value = 0;
    }
    // This check the number of Attacking diagonal
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < N_Q; j++)
        {
            for (int k = j + 1; k < N_Q; k++)
            {
                if ((j != k) && (abs(chromosome[i][j] - chromosome[i][k]) == abs(j - k)))
                {
                    fitness_value++;
                }
            }
        }
        fitness[i] += fitness_value;
        fitness_value = 0;
    }
}
/*This function tells us about if we find the solution by checking the fitness means attacks. If the return is
1 then we break out of the loop in main() and get the result */
int is_solution_found(int fitness[ROWS])
{
    int sol_fnd = 0;
    for (int i = 0; i < ROWS; i++)
    {
        if (fitness[i] == 0)
        {
            sol_fnd = 1;
            break;
        }
    }
    return sol_fnd;
}
/*This function Swaps the choromosome and fitness value according to the assending fitness order*/
// 
void sort_swap(int fitness[ROWS], int chromosome[ROWS][N_Q])
{
    int swap, arr_swap[N_Q];
    for (int i = 0; i < ROWS-1; i++)
    {
        
        {
            if (fitness[i] > fitness[i+1])
            {
                swap = fitness[i];
                fitness[i] = fitness[i+1];
                fitness[i+1] = swap;

                for (int k = 0; k < N_Q; k++)
                {
                    arr_swap[k] = chromosome[i][k];
                    chromosome[i][k] = chromosome[i+1][k];
                    chromosome[i+1][k] = arr_swap[k];
                }
            }
        }
    }
}
/*iss  ka rehta ha ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////*/
void cross_over(int chromosome[ROWS][N_Q])
{
    int parents = ROWS / 2;

    for (int i = 0; i < parents; i = i + 2)
    {
        for (int j = 0; j < N_Q / 2; j++)
        {
            chromosome[parents + i][j] = chromosome[i][j];
            chromosome[parents + i + 1][j] = chromosome[i + 1][j];
        }
        for (int k = N_Q / 2; k < N_Q; k++)
        {
            chromosome[parents + i][k] = chromosome[i + 1][k];
            chromosome[parents + i + 1][k] = chromosome[i][k];
 }
}
}
// void cross_over(int chromosome[ROWS][N_Q])
// {
//     int crossover_pt = ROWS % 2 == 0 ? ROWS / 2 : (ROWS - 1) / 2, temp;
//     temp = crossover_pt;
//     int pt = N_Q % 2 == 0 ? N_Q / 2 : (N_Q - 1) / 2;

//     for (int i = 0; i < crossover_pt; i)
//     {
//         for (int j = crossover_pt; j < ROWS; j++)
//         {
//             for (int k = 0; k < pt; k++)
//             {
//                 chromosome[j][k] = chromosome[i][k];
//             }
//             i++;
//         }
//     }
//     for (int i = 1; i < crossover_pt; i = i + 2)
//     {

//         for (int j = crossover_pt; j < ROWS; j++)
//         {
//             for (int k = pt; k < N_Q; k++)
//             {
//                 chromosome[j][k] = chromosome[i][k];
//             }
//             if (j == temp)
//             {
//                 i--;
//             }
//         }
//         i++;
//     }
// }
/*Thus function will take a random index number & a random value between 1 - 8 for chromosome and then assign that
index to that value & also we are only changing one value of chromosome in each row (population)*/
void mutation(int chromosome[ROWS][N_Q])
{
    // srand(time(NULL));
    int value, index;
    for (int i = 0; i < ROWS; i=i+2)
    {
        index = (rand() % N_Q);
        value = (rand()% N_Q)+1;
        chromosome[i][index] = value;
    }
}
/*This shows the result of chromosome And the number of attack on that perticular set of(size define by number of queens)
choromosome on tewrminal */
void show_value(int fitness[ROWS], int chromosome[ROWS][N_Q])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < N_Q; j++)
        {
            printf("%d", chromosome[i][j]);
        }
        printf("\t%d\n", fitness[i]);
    }
}
// END OF PROGRAM
