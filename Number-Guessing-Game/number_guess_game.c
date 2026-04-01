#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int num,guess,again;
    int attempts=0;

    srand(time(0));

    num = rand() % 100 + 1;
    printf("You have to Guess a number between 1-100.\n");
    printf("You have 10 attempts. Good luck\n");

    while(1)
    {
        while(1)
        {
            printf("\nAttempts Remain:%d",10-attempts);
            printf("\nEnter Your Guess:");
            scanf("%d",&guess);
            attempts++;
            if(attempts == 10)
            {
                printf("You lose!");
                break;
            }

            if(guess > num)
            {
                printf("too Higher!\n");
            }
            else if(guess < num)
            {
                printf("too Lower!\n");
            }
            else 
            {
                printf("Congrats!!!");
                printf("\nAttempts:%d",attempts);
                break;
            }
        }
        printf("\nDo you want to play again[1.Yes|2.No]:");
        scanf("%d",&again);
        if(again == 1)
            continue;
        else if(again == 2)
            break;
        else
            printf("Invalid input!!!");
    }
}