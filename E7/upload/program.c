#include<stdio.h>
#include <pthread.h> 
#include <semaphore.h>
#define N 7 //Number of philosophers

sem_t fork[N];
sem_t max;
FILE *fout;
void *philosopher(int pno){
    int i,j;
    i=pno;
    j=(i+1)%N;
    printf("\nPhilosoper %d is Waiting to Eat",i+1);
    fprintf(fout,"\nPhilosoper %d is Waiting to Eat",i+1);
    sem_wait(&max);
    //printf("\nPhilosopher%d is Sitting on Table",i);
    //fprintf(fout,"\nPhilosopher%d is Sitting on Table",i);
    sem_wait(&fork[i]);
    sem_wait(&fork[j]);
    printf("\nPhilosopher %d is Eating",i+1);
    fprintf(fout,"\nPhilosopher %d is Eating",i+1);
    sem_post(&fork[i]);
    sem_post(&fork[j]);
    printf("\nPhilosopher %d Finished Eating",i+1);
    fprintf(fout,"\nPhilosopher %d Finished Eating",i+1);
    sem_post(&max);
    //printf("\nPhilosopher%d Left",i);
    //fprintf(fout,"\nPhilosopher%d Left",i);
}
void main(){
    int a[N];
    fout = fopen("output.txt", "w");
    pthread_t phil[N];
    sem_init(&max,0,N/2);
    for(int i=0;i<N;i++){
        sem_init(&fork[i],0,1);
        a[i]=i;
    }
    for(int i=0;i<N;i++)
        pthread_create(&phil[i],NULL,(void *)philosopher,(void *)a[i]);

    for(int i=0;i<N;i++){
        pthread_join(phil[i],NULL);
    }

    sem_destroy(&max);
    for(int i=0;i<N;i++)
        sem_destroy(&fork[i]);
}