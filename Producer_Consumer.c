//Name     : Shyamal Khachane
//Batch    : L 10
//Roll no. : 33227
//Problem Statement : Application to demonstrate producer-consumer problem with counting semaphores and mutex.


#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define buffer_size 100
#define max 20
typedef struct
{
	int in,out;
	int buffer[buffer_size];
	sem_t empty;				//Semaphore empty
	sem_t full;				//Semaphore full
	pthread_mutex_t buffer_lock;	//Semaphore mutex
}Buffer;

Buffer b;

void initialise_func();
void * producer(void * arg);
void * consumer(void * arg);
int k;

int main()
{
	int no_p,no_c,i;
	pthread_t prod[max],cons[max];	//Declaring threads of size 20 for producer and consumer
	
	initialise_func();
	
	printf("\nEnter the number of producers : ");
	scanf("%d",&no_p);					//Scan number of producers
	
	printf("\nEnter the number of consumers : ");
	scanf("%d",&no_c);					//Scan number of consumers
	
	for(i=0;i<no_p;i++)
	{
		void *arg=&i;
		pthread_create(&prod[i],NULL,*producer,(void *)arg);	//Create threads for producer
	}
	
	for(i=0;i<no_c;i++)
	{
		void *arg=&i;
		pthread_create(&cons[i],NULL,*consumer,(void *)arg);	//Create threads for consumer
	}
	
	for(i=0;i<no_p;i++)
	{
		pthread_join(prod[i],NULL);		//Join producer threads
	}
	
	for(i=0;i<no_p;i++)
	{
		pthread_join(cons[i],NULL);		//Join consumer threads
	}
	return 0;
}

void initialise_func()
{
	printf("\n-----------------Initialising all parameters -----------------");
	b.in=0;
	b.out=0;
	sem_init(&b.empty,0,buffer_size);	//buffer_size i.e 100 slots are empty
	sem_init(&b.full,0,0);		//0 slots are full
	pthread_mutex_init(&b.buffer_lock,NULL);	
}

void *producer(void *arg)
{
	int i=*(int *)arg;
	int item;
	while(1)
	{
		item=rand()%10;	//Produce random item
		
		printf("\nProducer waits ");
		sleep(rand()%7);	//Sleeps for random time
		
		sem_wait(&b.empty);	//Wait till empty slot
		
		printf("\n\n----------Producer %d produced item %d ----------",i+1,item);
		printf("\nProducer - locking buffer");
		
		pthread_mutex_lock(&b.buffer_lock);	//Lock buffer
		b.buffer[(b.in++)%buffer_size]=item;	//Put item in buffer
		
		printf("\nProducer - unlocking buffer");
		pthread_mutex_unlock(&b.buffer_lock);	//Unlock buffer
		sem_post(&b.full);				//signal full
	}	

}

void *consumer(void * arg)
{
	int i=*(int *)arg;
	int removed_item;
	while(1)
	{
		printf("\n\t\t\t\t\t\t\tConsumer waits");
		
		sleep(rand()%7);	//Sleeps for random time
		sem_wait(&b.full);	//Wait till empty slot
		
		printf("\n\n\t\t\t\t\t\t\tConsumer - locking buffer\t\t");
		
		pthread_mutex_lock(&b.buffer_lock);	//Lock buffer
		removed_item=b.buffer[(b.out++)%buffer_size];	//Put item in buffer
		
		printf("\n\t\t\t\t\t----------Consumer %d removed item %d ----------",i+1,removed_item);
		printf("\n\t\t\t\t\t\t\tConsumer - unlocking buffer");
		pthread_mutex_unlock(&b.buffer_lock);	//Unlock buffer
		sem_post(&b.empty);	//signal empty
	}
}

