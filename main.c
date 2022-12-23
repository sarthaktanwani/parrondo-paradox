#include <unistd.h>     //for definition of STDIN_FILENO
#include <stdio.h>
#include <stdlib.h>
#include <time.h>       //for srand(time(NULL))
#include <termios.h>    //to immediately respond to keystrokes on the terminal

#define NUMBER_OF_GAMES 3

typedef struct
{
    int wins[NUMBER_OF_GAMES], losses[NUMBER_OF_GAMES], gameBal[NUMBER_OF_GAMES];
}Stats;

int gameA(Stats *s);
int gameB(Stats *s);
int gameC(Stats *s);

// void printStats(int, int, int, int);


void printStats(int iter, Stats *);
void resetStats(Stats *);

int main()
{
    int iter = 0;
    Stats s1;
    resetStats(&s1);
    
    int balGameA = 0,balGameB = 0, balGameC = 0;
    int winsA = 0, winsB = 0, winsC = 0;
    int lossesA = 0, lossesB = 0, lossesC = 0;
    char prompt = 'y';
    (void)prompt;

    struct termios old_setting, new_setting;

    tcgetattr(STDIN_FILENO, &old_setting);
    new_setting = old_setting;

    new_setting.c_lflag &= (~ICANON);

    srand(time(NULL));


    while(s1.gameBal[2] <= 0)
    // while(balGameC <= 0) 
    {
        // float random_number = (float)rand() / (float) RAND_MAX;
        // printf("random number 1 is: %f\n", random_number);
        // random_number = (float)rand() / (float) RAND_MAX;
        // printf("random number 2 is: %f\n", random_number);
        // printf("Enter the number of iterations: ");
        // scanf(" %d", &iter);
        // printf("iterations are: %d\n", iter);
        resetStats(&s1);
        winsA = winsB = winsC = lossesA = lossesB = lossesC = 0;
        balGameA = balGameB = balGameC = 0;
        iter = 1000;
        for(int i = 0; i < iter; i++)
        {
            int res = gameA(&s1);
            if(res == 0)
            {
                balGameA--;
                lossesA++;
                // s1.gameBal[0]--;
                // s1.losses[0]++;
            }
            else
            {
                balGameA++;
                winsA++;
                // s1.gameBal[0]++;
                // s1.wins[0]++;
            }

            res = gameB(&s1);
            if(res == 0)
            {
                balGameB--;
                lossesB++;
                // s1.gameBal[1]--;
                // s1.losses[1]++;
            }
            else
            {
                balGameB++;
                winsB++;
                // s1.gameBal[1]++;
                // s1.wins[1]++;
            }
            res = gameC(&s1);
            if(res == 0)
            {
                balGameC--;
                lossesC++;
                // s1.gameBal[2]--;
                // s1.losses[2]++;
            }
            else
            {
                balGameC++;
                winsC++;
                // s1.gameBal[2]++;
                // s1.wins[2]++;
            }
        }

        printStats(iter, &s1);

        printf("iterations complete\n");
        // printf("gameBalC = %d, finalgameBal: %d\n", balGameC, s1.gameBal[2]);
        // printf("iterations complete\n");

        // printf("Enter the prompt: ");

        // tcsetattr(STDIN_FILENO, TCSANOW, &new_setting);

        // scanf(" %c", &prompt);
        
        // tcsetattr(STDIN_FILENO, TCSANOW, &old_setting);
        
        // printf("\n");
        // printf("prompt is: %c\n", prompt);
        
        // if(prompt != 'y' && prompt != 'Y')
        // {
        //     break;
        // }
        // resetStats(&s1);  
    }

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
    }
}

void printStats(int iter, Stats *s)
{    
    printf("******Game A Stats******\n");
    printf("Final Balance: %d\n", s->gameBal[0]);
    printf("Wins: %d/%d\tLosses: %d/%d\t\n", s->wins[0], iter, s->losses[0], iter);
    printf("%% Wins: %0.2f%%\tLosses: %0.2f%%\t\n\n", (float)s->wins[0]/iter*100, (float)s->losses[0]/iter*100);

    printf("******Game B Stats******\n");
    printf("Final Balance: %d\n", s->gameBal[1]);
    printf("Wins: %d/%d\tLosses: %d/%d\t\n", s->wins[1], iter, s->losses[1], iter);
    printf("%% Wins: %0.2f%%\tLosses: %0.2f%%\t\n\n", (float)s->wins[1]/iter*100, (float)s->losses[1]/iter*100);

    printf("******Game C Stats******\n");
    printf("Final Balance: %d\n", s->gameBal[2]);
    printf("Wins: %d/%d\tLosses: %d/%d\t\n", s->wins[2], iter, s->losses[2], iter);
    printf("%% Wins: %0.2f%%\tLosses: %0.2f%%\t\n\n", (float)s->wins[2]/iter*100, (float)s->losses[2]/iter*100);
}


int gameA(Stats *s)
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
        if(random_number < 0.01)
        {
            //win with a 1% chance
            s->wins[1]++;
            s->gameBal[1]++;
            return 1;
        }
        else
        {
            //lose with a 99.9% chance
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
    (void)random_number;
    // if(balance % 3 == 0)
    // {
    //     return gameB(balance);
    // }
    // else
    // {
    //     return gameA();
    // }
    
    
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
    else if(random_number < 0.5)
    {
        random_number = (float)rand() / (float) RAND_MAX;

        if(s->gameBal[2] % 3 == 0)
        {
            if(random_number < 0.01)
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
    else
    {
        return gameC(s);
    }
}
