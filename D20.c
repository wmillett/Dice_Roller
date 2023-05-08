#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int getRandomNumber(int min, int max) {
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    return min + rand() % (max - min + 1);
}

int pdam(int attack)
{
    int roll;
    int roll2;
    if (attack == 1)
    {
        roll = getRandomNumber(1, 8);
        roll2 = getRandomNumber(1, 8);
        printf("Damage:%i\n",roll + roll2 + 7);
        return(roll + roll2 + 7);
    }
    if (attack == 2)
    {
        roll = getRandomNumber(1, 8);
        printf("Damage:%i\n",roll + 7);
        return(roll + 7);
    }
    if (attack == 3)
    {
        roll = getRandomNumber(1, 12);
        if (roll == 1 || roll == 2)
            roll = getRandomNumber(1, 12);
        roll2 = getRandomNumber(1, 12);
        if (roll2 == 1 || roll2 == 2)
            roll2 = getRandomNumber(1, 12);
        printf("Damage:%i\n",roll + roll2 + 6);
        return(roll + roll2 + 6);

    }
    if (attack == 4)
    {
        roll = getRandomNumber(1, 12);
        if (roll == 1 || roll == 2)
            roll = getRandomNumber(1, 12);
        roll2 = getRandomNumber(1, 12);
        if (roll2 == 1 || roll2 == 2)
            roll2 = getRandomNumber(1, 12);
        printf("Damage:%i\n",roll + roll2 + 16);
        return(roll + roll2 + 16);

    }
    if (attack == 5)
    {
        roll = getRandomNumber(1, 12);
        if (roll == 1 || roll == 2)
            roll = getRandomNumber(1, 12);
        printf("Damage:%i\n",roll + 6);
        return(roll + 6);

    }
    if (attack == 6)
    {
        roll = getRandomNumber(1, 12);
        if (roll == 1 || roll == 2)
            roll = getRandomNumber(1, 12);
        printf("Damage:%i\n",roll + 16);
        return(roll + 16);
    }
    else
        return(0);
}

void    adrax(char**argv)
{
    int d8 = atoi(argv[2]);
    int d12 = atoi(argv[3]);
    int mod = atoi(argv[4]);
    int GWM = atoi(argv[5]);
    int ADV = atoi(argv[6]);
    int AC = atoi(argv[7]);
    int roll;
    int roll2;
    int tmp;
    int GWDIF = 0;
    int tdam = 0;
    if(argv[1][0] == 'a')
    {
        printf("----------------------\n");
        printf("Adrax's attacks:\n");
        while (d8--)
        {
            roll = getRandomNumber(1, 20);
            if (ADV == 1)
            {
                if ((roll2 = getRandomNumber(1, 20)) > roll)
                    roll = roll2;
            }
            if (roll == 20 || roll == 1)
            {
                if (roll == 1)
                    printf("-Fumble(d8)...\n");
                else
                {
                    printf("-CRIT!(d8) ");
                    tdam += pdam(1);
                }
            }
            else if (roll + mod + 13 >= AC)
            {
                printf("-Hit(d8) ");
                tdam += pdam(2);
            }
            else
            {
                tmp = AC - (roll + mod + 7);
                printf("-Miss(d8, by %i)\n", tmp);
            }
            // printf("////\n");
        }
        if (GWM == 1)
                GWDIF = -5;
        while(d12--)
        {
            roll = getRandomNumber(1, 20);
            if (ADV == 1)
            {
                if ((roll2 = getRandomNumber(1, 20)) > roll)
                    roll = roll2;
            }
            if (roll == 20 || roll == 1)
            {
                if (roll == 1)
                    printf("-Fumble(d12)...\n");
                else
                {
                    printf("-CRIT!(d12) ");
                    if (GWM == 1)
                        tdam += pdam(4);
                    else
                        tdam += pdam(3);
                }
            }
            else if (roll + mod + 12 + GWDIF >= AC)
            {
                printf("-Hit(d12) ");
                if (GWM == 1)
                    tdam += pdam(6);
                else
                    tdam += pdam(5);
            }
            else
            {
                tmp = AC - (roll + mod + 12 + GWDIF);
                printf("-Miss(d12, by %i)\n", tmp);
            }
            // printf("////\n");
        }
    // else
    // {
    //     printf("test\n");
    // }
    printf("Total damage: %i\n", tdam);
    // int i = 0;
    // printf("Potential damage with maneuvers: ");
    // while(i < (d8 + d12))
    // {
    //     roll = getRandomNumber(1, 12);
    //     printf("%i", roll);
    //     i++;
    // }
    // printf("\n");
    printf("END OF ATTACKS\n");
    printf("----------------------\n");
    }
}


void adrax_fix(char**argv)
{
    int d8 = atoi(argv[2]);
    int d12 = atoi(argv[3]);
    const char *missed_by = argv[4];
    int GWP = atoi(argv[5]);
    int len_m = strlen(missed_by);
    int i = 0;
    int roll = 0;
    int tdam = 0;

    if (d12 + d8 != len_m)
    {
        printf("ERROR\nYour string says you have %i instead of %i attacks\n", len_m, d12 + d8);
        exit(0);
    }
    printf("----------------------\n");
    printf("Reroll attacks:\n");
    while(i < len_m)
    {   
        if (i < d8)
        {
            roll = getRandomNumber(1, 12);
            if (roll + 48 >= missed_by[i])
            {
                printf("Hit! ");
                tdam += pdam(2);
            }
            else
                printf("Miss...\n");
        }
        if (i >= d8)
        {
            roll = getRandomNumber(1,12);
            if (roll + 48 >= missed_by[i])
            {
                if(GWP)
                {
                    printf("Hit! ");
                    tdam += pdam(6);
                }
                else
                {
                    printf("Hit! ");
                    tdam += pdam(5);
                }
            }
            else
                printf("Miss...\n");
        }
        i++;
    }
    printf("Total potential damage: %i\n", tdam);
    printf("End of attack rerolls.\n");
    printf("----------------------\n");



}





int main(int argc, char**argv)
{
    int roll;
    int maxv;
    int nbroll;
    int tmp;
    int mod;
    int tdam = 0;

    if (argc <= 1)
    {
        printf("(Investigation check to find your roll has failed.)\n");
        exit(0);
    }
    else if(argc == 2)
    {
        maxv = atoi(argv[1]);
         if (maxv <= 0)
        {
            printf("(You were sucked into a parallel universe where it's possible to make that roll.)\n");
            exit(0);
        }
        roll = getRandomNumber(1, maxv);
        printf("%i\n",roll);
    }
    else if(argc == 3)
    {
        maxv = atoi(argv[1]);
        nbroll = atoi(argv[2]);
        if (nbroll <= 0 || maxv <= 0)
        {
            printf("(You were sucked into a parallel universe where it's possible to make that roll.)\n");
            exit(0);
        }
        if (maxv == 20)
        {
            tmp = nbroll;
            while(tmp--)
            {
                roll = getRandomNumber(1, maxv);
                if (roll == 20)
                    printf("%i! ",roll);
                else if (roll == 1)
                     printf("%i? ",roll);
                else
                     printf("%i ",roll);
            }
        }
        else
        {
            roll = 0;
            tmp = nbroll;
            while(tmp--)
                roll += getRandomNumber(1, maxv);
            printf("Total damage: %i", roll);
        }
        printf("\n");

    }
    else if (argc == 4)
    {
            maxv = atoi(argv[1]);
            mod = atoi(argv[3]);
            nbroll = atoi(argv[2]);
            if (nbroll <= 0 || maxv <= 0)
            {
                printf("(You were sucked into a parallel universe where it's possible to make that roll.)\n");
                exit(0);
            }
            if (maxv == 20)
            {
                tmp = nbroll;
                while(tmp--)
                {
                    roll = getRandomNumber(1, maxv);
                    roll += mod;
                    if (roll - mod == 20)
                        printf("%i! ",roll);
                    else if (roll - mod == 1)
                        printf("%i? ",roll);
                    else
                        printf("%i ",roll);
                }
            }
            else
            {
                roll = 0;
                tmp = nbroll;
                while(tmp--)
                    roll += getRandomNumber(1, maxv) + mod;
                printf("Total damage: %i", roll);
            }
            printf("\n");
    }
    else if (argc == 8 && (argv[1][0] == 'a'))
            adrax(argv);
    else if (argc == 6 && (argv[1][0] == 'b'))
            adrax_fix(argv);
    else
        printf("Oops, you made a mistake in your request.\n");
}