//Assignment 8
//AIM: Application to demonstrate: Client and Server Programs in which server processcreates a shared memory segment and write the message to the
//shared memory segment.Client process reads the message from the shared memory segment and displays it to the screen.

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define TEXT_SZ 2048

struct shared_use_st
{
	int written_by_you;
	char some_text[TEXT_SZ];
};

int main()
{
	int running = 1;
	void *shared_memory = (void *)0;		
	struct shared_use_st *shared_stuff;
	int shmid;
	
	//seed random integer
	srand((unsigned int)getpid());		
	
	//int shmget(key_t key, size_t size, int shmflg);
	//A special bit defined by IPC_CREAT must be bitwise ORed with the permissions to create a new shared memory segment.
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);	 //0666 - permissions
	
	if(shmid == -1)									 //Returns -1 on error
	{
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}
	
	//void *shmat(int shm_id, const void *shm_addr, int shmflg);
	shared_memory = shmat(shmid, (void *)0, 0);
	
	//Check for error
	if(shared_memory == (void *)-1)		 		   		
	{
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Memory attached at %X\n", (int)shared_memory);
	
	 //Point the shared_stuff where shared_memory points
	shared_stuff = (struct shared_use_st *)shared_memory;			
	
	//Nothing is written
	shared_stuff->written_by_you = 0;						
	
	while(running)								
	{
		//If written
		if(shared_stuff->written_by_you)					
		{
			printf("You wrote: %s", shared_stuff->some_text);
			sleep( rand() % 4 );						//make the other process wait for us
			shared_stuff->written_by_you = 0;				//Set the flag to 0 
			if (strncmp(shared_stuff->some_text, "end", 3) == 0)	//If end is encountered
			{
				running = 0;
			}
		}
	}
	if(shmdt(shared_memory) == -1)						//Detach shared memory from current process
	{
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	if(shmctl(shmid, IPC_RMID, 0) == -1)					//Delete shared memory segment through RMID
	{
		fprintf(stderr, "shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
