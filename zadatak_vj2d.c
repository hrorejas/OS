#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int zadnji_broj = 0;
int TRAZIM[100] = {0};
int BROJ[100] = {0};
int br = 0;

void UlazimKO(int broj)
{   
    int i;
    TRAZIM[broj] = 1;
    BROJ[broj] = zadnji_broj +1;
    zadnji_broj = BROJ[broj];
    TRAZIM[broj] = 0;

    for (i = 0; i <= br; i++)
    {
        while (TRAZIM[i] == 1);
        while ( (BROJ[i] !=0 ) && ( BROJ[i] < BROJ[broj] || (BROJ[i] == BROJ[broj] && i < broj)));
    }
}

void IzlazimKO (int broj)
{
    BROJ[broj] = 0;
}

void *Dretva (void *brDretve)
{
    int broj = *((int*)brDretve);
    int m,j;
    for (m = 1; m <= 5; m++)
    {
        UlazimKO(broj);
        for (j = 1; j <= 5; j++)
        {
            printf("Dretva: %d, K.O. br: %d (%d/5)\n", broj ,m, j);
            sleep(1);
        }
    IzlazimKO(broj);
    }
    
       
}


int main (int brArgumenta, char *Argumenti[])
{
    
    br = brArgumenta + 1;
    pthread_t Pid[br];

    int brDretve = 0;
    int i,j;

    for (i = 0; i < br; i++)
    { 
        sleep(1);
        pthread_create (&Pid[i], NULL, Dretva, &brDretve);// ptread_t(PID) - sprema u neku varijablu
        brDretve++;
    }


    for (i = 0; i < br; i++)
    {
        pthread_join (Pid[i],NULL);
    }
    

    return 0;
}