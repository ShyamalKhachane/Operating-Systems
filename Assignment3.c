//Matrix Multiplication using threads
//Name    : Shyamal Sanjay Khachane
//Roll No : 33227
//Batch   : L-10
//

#include<pthread.h>
#include<stdio.h>
#include<sys/wait.h>
#include<time.h>

int step=0;
int mat1[10][10],mat2[10][10],mat3[10][10];

//Code for matrix multiplication
void *cal(void * arg)
{
	int *size;
	size=(int *)arg;

	int i,j,k;
	for(i=step;i<(step+1);i++)
	{
		for(k=0;k<size[0]*size[1];k++)
		{
			for(j=0;j<size[0]*size[1];j++)
			{
				mat3[i][k]+=mat1[i][j]*mat2[j][k];
			}
		}
	}	
	step++;	
}

//Normal multiplication
void mul(int m1,int n2,int n1)
{
	int i,j,k;
	for(i=0;i<m1;i++)
	{
		for(j=0;j<n1;j++)
		{
			for(k=0;k<n2;k++)
			{
				mat3[i][k]+=mat1[i][j]*mat2[j][k];
			}
		}
	}
	for(i=0;i<m1;i++)
	{
		printf("\n|");
		for(j=0;j<n2;j++)
		{
			printf("%d\t",mat3[i][j]);
		}
		printf("|");
	}
	
}
int main()
{
	int i,j,m1,n1,m2,n2;
	clock_t start,end;
	double time1,time2;
	printf("\nEnter rows and columns for first matrix  :");
	scanf("%d %d",&m1,&n1);
	printf("\nEnter rows and columns for second matrix :");
	scanf("%d %d",&m2,&n2);
	int arg[2]={m1,n2};
	//Validation if matrix multiplication is possible
	if(n1!=m2)
	{
		printf("\nMatrix Multiplication is not possible as :\nNumber of columns of first matrix i.e. %d is not equal to number of rows of  			second matrix i.e. %d",n1,m2);
		return -1;
	}
	
	printf("\nENTER ELEMENTS FOR FIRST MATRIX");
	for(i=0;i<m1;i++)
	{
		for(j=0;j<n1;j++)
		{
			printf("\nElement [%d][%d]",i,j);
			scanf("%d",&mat1[i][j]);
		}
	}
	printf("\nENTER ELEMENTS FOR SECOND MATRIX");
	for(i=0;i<m2;i++)
	{
		for(j=0;j<n2;j++)
		{
			printf("\nElement [%d][%d]",i,j);
			scanf("%d",&mat2[i][j]);
		}
	}
	
	//Display Matrix 1
	printf("\nEntered First matrix is:\n");
	for(i=0;i<m1;i++)
	{
		printf("\n|");
		for(j=0;j<n1;j++)
		{
			printf("%d\t",mat1[i][j]);
		}
		printf("|");
		
	}
	
	//Display Matrix 2
	printf("\nEntered Second matrix is :\n");
	for(i=0;i<m2;i++)
	{
		printf("\n|");
		for(j=0;j<n2;j++)
		{
			printf("%d\t",mat2[i][j]);
		}
		printf("|");
	}
	
	//Initialize resultant matrix to 0
	for(i=0;i<m1;i++)
	{
		printf("\n");
		for(j=0;j<n2;j++)
		{
			mat3[i][j]=0;
		}
	}
	start=clock();
	mul(m1,n2,n1);
	printf("\nTime started for normal matrix multiplication");
	end=clock();
	time1 = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nTime taken by normal multiplication is : %f",time1);
	//Initialize resultant matrix to 0
	for(i=0;i<m1;i++)
	{
		printf("\n");
		for(j=0;j<n2;j++)
		{
			mat3[i][j]=0;
		}
	}
	//Declaring threads
	pthread_t thread[m1*n2];
	
	//Creating threads
	printf("\nTime started for multiplication using thread");
	start=clock();
	printf("\n-------------CREATING %d THREADS-------------\n",m1*n2);
	for(i=0;i<m1*n2;i++)
	{
		
		pthread_create(&thread[i],NULL,cal,(void*) arg);	
		printf("\nTHREAD %d CREATED",i+1);
	}
	
	//Joining threads
	printf("\n-------------JOINING THREADS-------------\n");
	for(i=0;i<m1*n2;i++)
	{
		
		pthread_join(thread[i],NULL);
		printf("\nThread joined is %d",i);
		sleep(1);
	}
	
	//Display resultant matrix
	printf("\n\nRESULT OF MATRIX MULTIPLICATION IS :\n");
	for(i=0;i<m1;i++)
	{
		printf("\n|");
		for(j=0;j<n2;j++)
		{
			printf("%d\t",mat3[i][j]);
		}
		printf("|");
	}
	printf("\n");
	
	end=clock();
	time2 = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nTime taken by thread multiplication is : %f",time2);
	return 0;
	
}
