#include <unistd.h>     //for definition of STDIN_FILENO
#include <stdio.h>
#include <stdlib.h>
#include <time.h>       //for srand(time(NULL))

#define NUMBER_OF_GAMES 3

typedef struct
{
    int wins[NUMBER_OF_GAMES], losses[NUMBER_OF_GAMES];
    int gameBal[NUMBER_OF_GAMES];
    float avg_wins[NUMBER_OF_GAMES], avg_losses[NUMBER_OF_GAMES];
    float avg_gameBal[NUMBER_OF_GAMES];
}Stats; 

int gameA(Stats *s);
int gameB(Stats *s);
int gameC(Stats *s);

void printStats(int iter, Stats *);
void resetStats(Stats *);

int main()
{
    int iter = 0, runs = 0;
    Stats s1;
    resetStats(&s1);
    srand(time(NULL));

    for(int i = 0; i < NUMBER_OF_GAMES; i++)
    {
        s1.avg_wins[i] = 0;
        s1.avg_losses[i] = 0;
        s1.avg_gameBal[i] = 0;
    }

    printf("Enter the number of repetitions: ");
    scanf(" %d", &runs);
    printf("Runs are: %d\n", runs);

    printf("Enter the number of iterations: ");
    scanf(" %d", &iter);
    printf("iterations are: %d\n", iter);

    for(int i = 0; i < runs; i++)
    {
        resetStats(&s1);
        // iter = 1000;
        for(int j = 0; j < iter; j++)
        {
            gameA(&s1);
            gameB(&s1);
            gameC(&s1);
        }
        s1.avg_wins[0] += s1.wins[0];
        s1.avg_wins[1] += s1.wins[1];
        s1.avg_wins[2] += s1.wins[2];

        s1.avg_losses[0] += s1.losses[0];
        s1.avg_losses[1] += s1.losses[1];
        s1.avg_losses[2] += s1.losses[2];

        s1.avg_gameBal[0] += s1.gameBal[0];
        s1.avg_gameBal[1] += s1.gameBal[1];
        s1.avg_gameBal[2] += s1.gameBal[2];
        // runs++;

        // printf("%f,", (float)(s1.avg_losses[2] / runs));
    }
    for(int i = 0; i < NUMBER_OF_GAMES; i++)
    {
        s1.avg_wins[i] = (float)s1.avg_wins[i] / runs;
        s1.avg_losses[i] = (float)s1.avg_losses[i] / runs;
        s1.avg_gameBal[i] = (float)s1.avg_gameBal[i] / runs;
    }
    printStats(iter, &s1);
    printf("%d iterations complete\n", runs);
    printf("Hello World\n");
    return 0;
}

void resetStats(Stats *s)
{
    for(int i = 0; i < NUMBER_OF_GAMES; i++)
    {
        s->wins[i] = 0;
        s->losses[i] = 0;
        s->gameBal[i] = 0;
        // s->avg_wins[i] = 0;
        // s->avg_losses[i] = 0;
        // s->avg_gameBal[i] = 0;
    }
}

int  gameA(Stats *s)
{
    float random_number = (float)rand() / (float) RAND_MAX;

    if(random_number < 0.495)
    {
        //Win with a chance of 49.5%
        s->wins[0]++;
        s->gameBal[0]++;
        return 1;
    }
    else
    {
        //Lose with a chance of 50.5%
        s->losses[0]++;
        s->gameBal[0]--;
        return 0;
    }
}

int gameB(Stats *s)
{
    float random_number = (float)rand() / (float) RAND_MAX;

    if(s->gameBal[1] % 3 == 0)
    {
        if(random_number < 0.1)
        {
            //win with a 1% chance
            s->wins[1]++;
            s->gameBal[1]++;
            return 1;
        }
        else
        {
            //lose with a 99% chance
            s->losses[1]++;
            s->gameBal[1]--;
            return 0;
        }
    }
    else
    {
        if(random_number < 0.75)
        {
            //Win with a 75% chance
            s->wins[1]++;
            s->gameBal[1]++;
            return 1;
        }
        else
        {
            //lose with a 25% chance
            s->losses[1]++;
            s->gameBal[1]--;
            return 0;
        }
    }
}

int gameC(Stats *s)
{
    float random_number = (float)rand() / (float) RAND_MAX;

    if(random_number > 0.5)
    {
        random_number = (float)rand() / (float) RAND_MAX;
        if(random_number < 0.495)
        {
            //Win with a chance of 49.5%
            s->wins[2]++;
            s->gameBal[2]++;
            return 1;
        }
        else
        {
            //Lose with a chance of 50.5%
            s->losses[2]++;
            s->gameBal[2]--;
            return 0;
        }
    }
    else if(random_number <= 0.5)
    {
        if(s->gameBal[2] % 3 == 0)
        {
            random_number = (float)rand() / (float) RAND_MAX;
            if(random_number < 0.1)
            {
                //win with a 1% chance
                s->wins[2]++;
                s->gameBal[2]++;
                return 1;
            }
            else
            {
                //lose with a 99.9% chance
                s->losses[2]++;
                s->gameBal[2]--;
                return 0;
            }
        }
        else
        {
            random_number = (float)rand() / (float) RAND_MAX;
            if(random_number < 0.75)
            {
                //Win with a 75% chance
                s->wins[2]++;
                s->gameBal[2]++;
                return 1;
            }
            else
            {
                //lose with a 25% chance
                s->losses[2]++;
                s->gameBal[2]--;
                return 0;
            }
        }
    }
    return -1;
}

void printStats(int iter, Stats *s)
{
    printf("******Game A Stats******\n");
    printf("Final Balance: $%f\n", s->avg_gameBal[0]);
    if(s->avg_gameBal[0] < 0)
    {
        //On average, lost x amount per turn
        printf("On average, lost $%f amount per turn\n", (-1)*(float)s->avg_gameBal[0]/iter);
    }
    else if(s->avg_gameBal[0] >= 0)
    {
        //On average, won x amount per turn
        printf("On average, won $%f amount per turn\n", (float)s->avg_gameBal[0]/iter);
            }
    printf("Wins: %f/%d\tLosses: %f/%d\t\n", s->avg_wins[0], iter, s->avg_losses[0], iter);
    printf("%% Wins: %0.2f%%\tLosses: %0.2f%%\t\n\n", (float)s->avg_wins[0]/iter*100, (float)s->avg_losses[0]/iter*100);

    printf("******Game B Stats******\n");
    printf("Final Balance: $%f\n", s->avg_gameBal[1]);
    if(s->avg_gameBal[1] < 0)
    {
        //On average, lost x amount per turn
        printf("On average, lost $%f amount per turn\n", (-1)*(float)s->avg_gameBal[1]/iter);
    }
    else if(s->avg_gameBal[1] >= 0)
    {
        //On average, won x amount per turn
        printf("On average, won $%f amount per turn\n", (float)s->avg_gameBal[1]/iter);
    }
    printf("Wins: %f/%d\tLosses: %f/%d\t\n", s->avg_wins[1], iter, s->avg_losses[1], iter);
    printf("%% Wins: %0.2f%%\tLosses: %0.2f%%\t\n\n", (float)s->avg_wins[1]/iter*100, (float)s->avg_losses[1]/iter*100);

    printf("******Game C Stats******\n");
    printf("Final Balance: $%f\n", s->avg_gameBal[2]);
    if(s->avg_gameBal[2] < 0)
    {
        //On average, lost x amount per turn
        printf("On average, lost $%f amount per turn\n", (-1)*(float)s->avg_gameBal[2]/iter);
    }
    else if(s->avg_gameBal[2] >= 0)
    {
        //On average, won x amount per turn
        printf("On average, won $%f amount per turn\n", (float)s->avg_gameBal[2]/iter);
    }
    printf("Wins: %f/%d\tLosses: %f/%d\t\n", s->avg_wins[2], iter, s->avg_losses[2], iter);
    printf("%% Wins: %0.2f%%\tLosses: %0.2f%%\t\n\n", (float)s->avg_wins[2]/iter*100, (float)s->avg_losses[2]/iter*100);
}
