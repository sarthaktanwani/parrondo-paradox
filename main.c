#include <unistd.h>     //for definition of STDIN_FILENO
#include <stdio.h>
#include <stdlib.h>
#include <time.h>       //for srand(time(NULL))
#include <termios.h>    //to immediately respond to keystrokes on the terminal

int gameA(void);
int gameB(int);
int gameC(int);

void printStats(int, int, int, int);

int main()
{
    int iter = 0;
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


    while(balGameC <= 0)
    {
        // float random_number = (float)rand() / (float) RAND_MAX;
        // printf("random number 1 is: %f\n", random_number);
        // random_number = (float)rand() / (float) RAND_MAX;
        // printf("random number 2 is: %f\n", random_number);
        // printf("Enter the number of iterations: ");
        // scanf(" %d", &iter);
        // printf("iterations are: %d\n", iter);
        iter = 1000;
        for(int i = 0; i < iter; i++)
        {
            int res = gameA();
            if(res == 0)
            {
                balGameA--;
                lossesA++;
            }
            else
            {
                balGameA++;
                winsA++;
            }

            res = gameB(balGameB);
            if(res == 0)
            {
                balGameB--;
                lossesB++;
            }
            else
            {
                balGameB++;
                winsB++;
            }


            res = gameC(balGameC);
            if(res == 0)
            {
                balGameC--;
                lossesC++;
            }
            else
            {
                balGameC++;
                winsC++;
            }
        }

        printStats(iter, winsA, winsB, winsC);

        printf("iterations complete\n");

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
        winsA = winsB = winsC = lossesA = lossesB = lossesC = 0;
    }

    printf("Hello World\n");
    return 0;
}

void printStats(int iter, int winsA, int winsB, int winsC)
{
    int lossA = iter - winsA;
    int lossB = iter - winsB;
    int lossC = iter - winsC;
    int balA = winsA - lossA, balB = winsB - lossB, balC = winsC - lossC;
    
    printf("******Game A Stats******\n");
    printf("Final Balance: %d\n", balA);
    printf("Wins: %d/%d\tLosses: %d/%d\t\n", winsA, iter, lossA, iter);
    printf("%% Wins: %0.2f%%\tLosses: %0.2f%%\t\n\n", (float)winsA/iter*100, (float)lossA/iter*100);

    printf("******Game B Stats******\n");
    printf("Final Balance: %d\n", balB);
    printf("Wins: %d/%d\tLosses: %d/%d\t\n", winsB, iter, lossB, iter);
    printf("%% Wins: %0.2f%%\tLosses: %0.2f%%\t\n\n", (float)winsB/iter*100, (float)lossB/iter*100);

    printf("******Game C Stats******\n");
    printf("Final Balance: %d\n", balC);
    printf("Wins: %d/%d\tLosses: %d/%d\t\n", winsC, iter, lossC, iter);
    printf("%% Wins: %0.2f%%\tLosses: %0.2f%%\t\n\n", (float)winsC/iter*100, (float)lossC/iter*100);
}


int gameA(void)
{
    float random_number = (float)rand() / (float) RAND_MAX;

    if(random_number < 0.495)
    {
        //Win with a chance of 49.5%
        return 1;
    }
    else
    {
        //Lose with a chance of 50.5%
        return 0;
    }
}

int gameB(int balance)
{
    float random_number = (float)rand() / (float) RAND_MAX;

    if(balance % 3 == 0)
    {
        if(random_number < 0.01)
        {
            //win with a 1% chance
            return 1;
        }
        else
        {
            //lose with a 99.9% chance
            return 0;
        }
    }
    else
    {
        if(random_number < 0.75)
        {
            //Win with a 75% chance
            return 1;
        }
        else
        {
            //lose with a 25% chance
            return 0;
        }
    }
}


int gameC(int balance)
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
        return gameA();
    }
    else if(random_number < 0.5)
    {
        return gameB(balance);
    }
    else
    {
        return gameC(balance);
    }
}
