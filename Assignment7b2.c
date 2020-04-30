#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF

int main()
{
	int pipe_fd;
	int res;
	FILE *fp;
	int i;
	char buffer2[BUFFER_SIZE + 1];
	int ch;
	long int char_count=0;
	long int line_count=1;
	char get_data[513];
	int data_processed;
	long int word_count=1;
	long int store=0; 
	int open_mode = O_RDONLY;
	char buffer[BUFFER_SIZE + 1];
	int bytes_read = 0;
	memset(buffer, '\0', sizeof(buffer));
	printf("Process %d opening FIFO O_RDONLY\n", getpid());
	pipe_fd = open(FIFO_NAME, open_mode);
	printf("Process %d result %d\n", getpid(), pipe_fd);
	if (pipe_fd != -1) 
	{
		do 
		{
			res = read(pipe_fd, buffer, BUFFER_SIZE);
			bytes_read += res;
		} 
		while (res > 0);
		(void)close(pipe_fd);
	}
	else 
	{
		exit(EXIT_FAILURE);
	}
	char_count=strlen(buffer);
	for(i=0;i<strlen(buffer);i++)
	{
		if(buffer[i]==' ' || buffer[i]=='\t' || buffer[i]=='\n')
		{
			word_count++;
		}
		if(buffer[i]=='\n')
		{
			line_count++;
		}
	}
	fp=fopen("a.txt","w");
	if(fp==NULL)
	{
		printf("Error in opening file");
		exit(1);
	}
	
	fprintf(fp,"Data is : %s\nCharacter count : %ld\nWord count :  %ld\nLine count :  %ld",buffer,char_count,word_count,line_count);
	fclose(fp);
	fp= fopen("a.txt","r");
	if(fp==NULL)
	{
		printf("Error in opening file");
		exit(1);
	}
	fread(&get_data, sizeof(get_data), 1, fp);
	fclose(fp);
	
	pipe_fd = open(FIFO_NAME,O_WRONLY); 
	write(pipe_fd,get_data,strlen(get_data)+1);
	printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);
	
	
	
	exit(EXIT_SUCCESS);
}
