#include<stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#define max 500
FILE* fo;
int prt[20],crt[20],n,size;
pthread_mutex_t mutex;
int total=0,pc=0,cc=0;
int size=20;
sem_t empty;
sem_t full;
void produce(void *nop)
{
 for(int i=0;i<max;i++)
 {
  sem_wait(&empty);
  pthread_mutex_lock(&mutex);
  if(total+prt[pc]<size && pc<n)
  {
   printf("Buffer spaces filled   :%d\n",total);
   fprintf(fo,"Buffer spaces filled   :%d\n",total);
   printf("Producer produce %d items successfully\n",prt[pc]);
   fprintf(fo,"Producer produce %d items successfully\n",prt[pc]);
   total=total+prt[pc];
   pc=pc+1;
  } 
  pthread_mutex_unlock(&mutex);
  sem_post(&full);
 }
}
void consume(void *noc)
{
 for(int i=0;i<max;i++)
 {
  sem_wait(&full);
  pthread_mutex_lock(&mutex);
  if(total-crt[cc]<size && cc<n)
  {
   printf("Buffer spaces filled   :%d\n",total);
   fprintf(fo,"Buffer spaces filled   :%d\n",total);
   printf("consumer consume %d items successfully\n",crt[cc]);
   fprintf(fo,"consumer consume %d items successfully\n",crt[cc]);
   total=total-crt[cc];
   cc=cc+1;
  } 
  pthread_mutex_unlock(&mutex);
  sem_post(&empty);
 }
}
void main()
{
 int c=0,a=0,b=0;
 fo=fopen("output.txt","w");
 FILE* fp=fopen("input6.txt","r");
 if(fp==NULL)
 {
  printf("file not present/n");
 }
 else
 {
  fscanf(fp,"%d",&size);
  
  fscanf(fp,"%d %d",&a,&b);
  while(!(feof(fp)))
  {
   prt[c]=a;
   crt[c]=b;
   fscanf(fp,"%d %d",&a,&b);
   c++;
  }
  prt[c]=a;
  crt[c]=b;
  
 }
 fclose(fp);
 n=c;
 pthread_t pro[5],con[5];
 pthread_mutex_init(&mutex, NULL);
 sem_init(&empty,0,size);
 sem_init(&full,0,0);
 int k[5] = {1,2,3,4,5};
  for(int i = 0; i < 1; i++) 
  {
    pthread_create(&pro[i], NULL, (void *)produce, (void *)&k[i]);
  }
  for(int i = 0; i < 1; i++) 
  {
    pthread_create(&con[i], NULL, (void *)consume, (void *)&k[i]);
  }
  for(int i = 0; i < 1; i++) 
  {
    pthread_join(pro[i], NULL);
  }
  for(int i = 0; i < 1; i++) 
  {
    pthread_join(con[i], NULL);
  }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    printf("Buffer space   :%d\n",size);
    fprintf(fo,"Buffer space   :%d\n",size);
    fclose(fo);
    
 }
