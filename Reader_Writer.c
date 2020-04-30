//Reader writer problem

//Name     : Shyamal Khachane
//Batch    : L 10
//Roll no. : 33227

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define max 20
int readcnt=0;

pthread_mutex_t mutex1,wrt;			//declaration of semaphore 

void * Reader(void *arg)			//Code for reader
{
	int i=*(int *)arg;
	while(1)
	{
		printf("\nReader %d is waiting to read",i+1);
	
		wait(mutex1);
		readcnt++;
		if(readcnt==1)	//First reader
		{
			printf("\n\n----First reader entered. Wait on writers----");
			wait(wrt);
		}
		
		printf("\nReader %d is reading",i+1);
		sleep(1);
		signal(mutex1);
		
		wait(mutex1);
		readcnt--;
		if(readcnt==0)	//All readers finished reading
		{
			printf("\n\n----All readers finished reading----");
			signal(wrt);
		}
		printf("\nReader %d finished reading",i+1);
		signal(mutex1);
		
	}
	
}

void * Writer(void *arg)		//Code for  writer
{
	int i=*(int *)arg;
	while(1)
	{
		sleep(2);
		printf("\n\t\t\t\tWriter %d is waiting to write",i);
		wait(wrt);	
		printf("\n\n\t\t\t\tWriter %d is writing",i+1);
		signal(wrt);
	}
}
int main()
{
	int i,no_r,no_w;
	
	pthread_mutex_init(&mutex1,NULL);	//Initialisation of mutex
	pthread_mutex_init(&wrt,NULL);
	
	pthread_t reader[max],writer[max];
	
	printf("\nEnter number of readers :");
	scanf("%d",&no_r);
	printf("\nEnter number of writers :");
	scanf("%d",&no_w);
	
	printf("%d %d ",no_r,no_w);
	printf("\n----Creating threads for readers----");
	for(i=0;i<no_r;i++)
	{
		int*arg=(int *)malloc(sizeof(int));
		*arg=i;
		pthread_create(&reader[i],NULL,*Reader,(void *)arg);	//Create threads for reader
	}
	printf("\n----Creating threads for writers ");
	for(i=0;i<no_w;i++)
	{
		int*arg=(int *)malloc(sizeof(int));
		*arg=i;
		pthread_create(&writer[i],NULL,*Writer,(void *)arg);	//Create threads for writers
	}
	
	for(i=0;i<no_r;i++)
	{
		pthread_join(reader[i],NULL);		//Join reader threads
	}
	
	for(i=0;i<no_w;i++)
	{
		pthread_join(writer[i],NULL);		//Join writer threads
	}
}
