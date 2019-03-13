#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
sem_t resource;
sem_t rmutex;
int rcount=0,data=0;

void *reader(void *arg)
{
  sem_wait(&rmutex);
  rcount = rcount + 1;
  if(rcount==1)
   sem_wait(&resource);
  sem_post(&rmutex);
  printf("Data read by the reader %d\n",data);  
	sleep(1);
  sem_wait(&rmutex);
  rcount = rcount - 1;
  if(rcount==0)
   sem_post(&resource);
  sem_post(&rmutex);
}

void *writer(void *arg)
{
  sem_wait(&resource);
  data++;
  printf("Data writen by the writer %d\n",data);
  sleep(1);
  sem_post(&resource);
}
void main()
{
	int i,b,r,w; 
	pthread_t rtid[5],wtid[5];
	sem_init(&resource,0,1);
	sem_init(&rmutex,0,1);
	printf("\nEnter the number of readers:");
	scanf("%d",&r);
	printf("\nEnter the number of writers:");
	scanf("%d",&w);
	int rc=0,wc=0;
	for(i=0;i<=r||i<=w;i++){
		if(wc<w)
    		{	wc++;
			pthread_create(&wtid[i],NULL,writer,(void *)i);
		}
		if(rc<r){
		    	rc++;
			pthread_create(&rtid[i],NULL,reader,(void *)i);
		}	
	}
	rc=0;
	wc=0;
  	for(i=0;i<=2;i++)
  	{
			pthread_join(wtid[i],NULL);
			pthread_join(rtid[i],NULL);
  	}
} 

