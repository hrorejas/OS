#include <iostream>
#include <signal.h>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <values.h>

using namespace std;

void prekidna_rutina(int signal)
{
   int i;
   for (i = 1; i < MAXLONG; i++) 
   {
      if (shmctl(i, IPC_RMID, NULL) != -1)
         printf("Obrisao zajednicku memoriju %d\n", i); 

      if (semctl(i, 0, IPC_RMID, 0) != -1)
         printf("Obrisao skup semafora %d\n", i); 

      if (msgctl(i, IPC_RMID, NULL) != -1)
         printf("Obrisao red poruka %d\n", i); 
   }
}


int main (int BrojArgumenta, char *Argumenti[])
{
	sigset(SIGINT,prekidna_rutina);

	if(BrojArgumenta/2 > 5)
		{
			cout <<"Unijeli ste previse stranica!" <<endl;
			exit(1);
		}


	int j = 1;
	for (int i = 1; i <= (BrojArgumenta/2); i++)
	{
		
		int BrojStranica = atoi(Argumenti[j]);
		float DuzinaStranice = atof(Argumenti[j+1]);
		j+=2;
		float Povrsina, Opseg;
		int fork();

		if (fork() == 0 )
		{
				cout << "a = " << BrojStranica << endl;
				cout << "n = " << DuzinaStranice << endl;
				Povrsina =(0.25 * BrojStranica * DuzinaStranice * DuzinaStranice)/(tan(3.14159265358979 / BrojStranica));
				cout <<"Povrsina stranice: "<< Povrsina << endl;
				sleep(1);

				Opseg = BrojStranica * DuzinaStranice;
				cout <<"Opseg stranice "<< Opseg <<endl;
				exit(0);
		}		
		
	}
	for (int i = 0; i < 5; i++)
		wait(NULL);
	return 0;
}


