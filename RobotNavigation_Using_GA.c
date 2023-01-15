#include<stdio.h>
#include"RobotNavigation_Using_GA.h"
int main()
{
    FILE *fp;
    srand(time(NULL) * getpid()); 
    int itra = 0, sol_fond = 3, termi = 0;
    ramdom_population(chromosome);
    // fitness_value(fitness, chromosome);
    CC_RR();
    sort_swap(fitness, chromosome);
    show_value(fitness, chromosome);
    fp = fopen("Fittest_value.txt", "w+");
    fprintf(fp, "Itration\tchromosome\t\t\tOrientation bit\tDirection bit\t Fittest\t\tPath_length\t\tInfisible_steps\t\tTurns\n");
    while (sol_fond == 3 && itra<=6000)
    {
        cross_over(chromosome);
        mutation(chromosome);
        // fitness_value(fitness, chromosome);
        CC_RR();
        sort_swap(fitness, chromosome);
        // show_value(fitness, chromosome);
        itra++;
        sol_fond = check_func(itra);
        for (int i = 0; i < 1; i++)
        {
            if (sol_fond != 3)
            {
                termi = sol_fond;
            }
            fprintf(fp, "%d\t\t  ", itra);
            for (int j = 0; j < GridSize; j++)
            {
                fprintf(fp, "%d ", chromosome[i][j]);
            }
            fprintf(fp, "  \t %2d \t\t\t \t%2d\t \t\t\t %.2f\t\t%2d \t\t     %0.2f \t\t    %0.2f \n", O_B[termi], D_B[termi], fitness[termi], pt_leng[termi], inf_step[termi], turns[termi]);
            if (sol_fond != 3)
            {
                fprintf(fp, "The number of chromosome in which chromosome is found is: %d", termi);
            }
        }
        printf("%d\n", itra);
    }
    fclose(fp);
    if (sol_fond != 3)
    {
        printf("\nThe Solution Found in Generation %d\n", itra);
        printf("Orientation bit: %d    Direction Bit: %d   Fitness is: %.2f\n", O_B[sol_fond], D_B[sol_fond], fitness[sol_fond]);
        fitness_value(fitness, chromosome, sol_fond, sol_fond);
        Display_Solution(grid, path, pt_leng, sol_fond);

        // Display_sol(sol_fond, O_B, D_B, pt_leng);
    }
    else
    {
        printf("The Solution Didn't Found in generation %d", itra);
    }

    return 0;}