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
    int bal = 0;
    int winsA = 0, winsB = 0, winsC = 0;
    int lossesA = 0, lossesB = 0, lossesC = 0;
    char prompt = 'y';

    struct termios old_setting, new_setting;

    tcgetattr(STDIN_FILENO, &old_setting);
    new_setting = old_setting;

    new_setting.c_lflag &= (~ICANON);

    srand(time(NULL));
    while(1)
    {
        printf("Enter the number of iterations: ");
        scanf(" %d", &iter);
        printf("iterations are: %d\n", iter);
        for(int i = 0; i < iter; i++)
        {
            int res = gameA();
            if(res == 0)
            {
                lossesA++;
            }
            else
            {
                winsA++;
            }

            res = gameB(bal);
            if(res == 0)
            {
                lossesB++;
            }
            else
            {
                winsB++;
            }


            res = gameC(bal);
            if(res == 0)
            {
                lossesC++;
            }
            else
            {
                winsC++;
            }
        }

        printStats(iter, winsA, winsB, winsC);

        printf("iterations complete\n");
        printf("Enter the prompt: ");

        tcsetattr(STDIN_FILENO, TCSANOW, &new_setting);

        scanf(" %c", &prompt);
        
        tcsetattr(STDIN_FILENO, TCSANOW, &old_setting);
        
        printf("\n");
        printf("prompt is: %c\n", prompt);
        
        // printf("prompt is: %d\n", prompt);
        if(prompt != 'y' && prompt != 'Y')
        {
            break;
        }
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
    
    printf("******Game A Stats******\n");
    printf("Wins: %d/%d\tLosses: %d/%d\t\n", winsA, iter, lossA, iter);
    printf("%% Wins: %0.2f%%\tLosses: %0.2f%%\t\n\n", (float)winsA/iter*100, (float)lossA/iter*100);

    printf("******Game B Stats******\n");
    printf("Wins: %d/%d\tLosses: %d/%d\t\n", winsB, iter, lossB, iter);
    printf("%% Wins: %0.2f%%\tLosses: %0.2f%%\t\n\n", (float)winsB/iter*100, (float)lossB/iter*100);

    printf("******Game C Stats******\n");
    printf("Wins: %d/%d\tLosses: %d/%d\t\n", winsC, iter, lossC, iter);
    printf("%% Wins: %0.2f%%\tLosses: %0.2f%%\t\n\n", (float)winsC/iter*100, (float)lossC/iter*100);
}


int gameA(void)
{
    float random_number = (float)rand() / (float) RAND_MAX;

    if(random_number < 0.495)
    {
        return 1;
    }
    else
    {
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
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if(random_number < 0.75)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}


int gameC(int balance)
{
    float random_number = (float)rand() / (float) RAND_MAX;
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