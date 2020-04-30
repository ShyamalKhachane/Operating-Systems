//Dining Philosopher starvation free solution

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define HUNGRY 0
#define EATING 1
#define THINKING 2
#define LEFT (pno + 4) % 5
#define RIGHT (pno + 1) % 5 


int state[5];
int phil[5]={0,1,2,3,4};
sem_t mutex;
sem_t P[5];

void check(int pno); 


void take_chopstick(int pno)
{
	//sem_wait(&mutex);
	state[pno]=HUNGRY;
	
	printf("\n\nPhilosopher %d is hungry ",pno+1);
	check(pno);
	
	if(state[pno]!=EATING )
	{
	sem_wait(&P[pno]);
	}
	if(state[pno]==EATING)
	{
	 printf("\n\n\t\t\t\tPhilosopher %d putting chopstick %d and %d down\n", pno +1, LEFT + 1, pno +1); 
		 
	}
	//sem_post(&mutex);
	 
    	sleep(1); 
}

void put_chopstick(int pno) 
{ 
  
    //sem_wait(&mutex); 
   
    state[pno] = THINKING; 

   
    printf("\n\n\t\t\t\tPhilosopher %d is thinking \n", pno+1); 
  
    check(LEFT); 
    check(RIGHT); 
  
    //sem_post(&mutex); 
} 

void check(int pno) 
{ 
    if (state[pno] == HUNGRY 
        && state[LEFT] != EATING 
        && state[RIGHT] != EATING) { 
      
        state[pno] = EATING;
         printf("\n\nPhilosopher %d takes Chopstick %d and %d\n",pno+1, LEFT + 1, pno+1); 
        printf("\n\nPhilosopher %d is Eating\n", pno +1); 
  	 sleep(1);
        sem_post(&P[pno]); 
    } 
} 
  
void * Din_phil(void * arg)
{
	int i=*(int *)arg;
	while(1)
	{
		sleep(1);
		take_chopstick(i);
		sleep(0);
		put_chopstick(i);
	}

}
void init()
{
	int i;
		sem_init(&mutex,0,1);
		for(i=0;i<5;i++)
		{
			sem_init(&P[i],0,1);
		}
	
}
int main()
{
	int i;
	pthread_t phil[5];
	init();
	printf("\n----Creating threads for philosophers----");
	for(i=0;i<5;i++)
	{
		int*arg=(int *)malloc(sizeof(int));
		*arg=i;
		pthread_create(&phil[i],NULL,*Din_phil,(void *)arg);
	}
	for(i=0;i<5;i++)
	{
		pthread_join(phil[i],NULL);
	}
	
}
