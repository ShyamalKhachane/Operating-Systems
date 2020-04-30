#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc , char** argv) {
	int data_processed;
	int file_pipes[2];
	int file_pipes2[2];
	char get_data[513];
	char buffer[BUFSIZ + 1];
	pid_t fork_result;

	memset(buffer, '\0', sizeof(buffer));
	if (pipe(file_pipes) == 0 && pipe(file_pipes2)==0) {
		fork_result = fork();
		if (fork_result == -1) {
			fprintf(stderr, "Fork failure");
			exit(EXIT_FAILURE);
		}else if(fork_result==0) 
		{
			close(file_pipes[1]);
			data_processed = read(file_pipes[0], buffer, BUFSIZ);
			FILE *fp1;
			fp1= fopen(buffer,"r");
			printf("Read %d bytes: %s\n", data_processed, buffer);
			fread(&get_data, sizeof(get_data), 1, fp1);
			close(file_pipes[0]);
			close(file_pipes2[0]);
			write(file_pipes2[1],get_data,strlen(get_data));
			close(file_pipes2[1]); 
			exit(EXIT_SUCCESS);	
		}else if(fork_result > 0)
		{
			close(file_pipes[0]);
			data_processed = write(file_pipes[1],argv[1],strlen(argv[1]));
			printf("Wrote %d bytes\n", data_processed);
			close(file_pipes[1]);
			sleep(2);
			close(file_pipes2[1]);
			read(file_pipes2[0], buffer, BUFSIZ);
			printf("data is : \n%s",buffer);
			close(file_pipes2[0]);
		}
	}
	exit(EXIT_SUCCESS);	
}
