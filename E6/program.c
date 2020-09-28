#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#define buffer 20
#define max 500

FILE *fout;
sem_t empty,full;
int prate[20], crate[20],n,pcount = 0,ccount = 0 ;
pthread_mutex_t mutex;
int store=0;

void *producer(void *pno)
{   
    int item;
    for (int i = 0; i < max; i++)
    {
        /* code */
    
    
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        //critical section
        if (store+prate[pcount]<buffer && pcount<=n)
        {         
            printf("Buffer space: %d\n", store);
            fprintf(fout,"Buffer space: %d\n", store);
            printf("Producer produced %d items\n\n",prate[pcount] );
            fprintf(fout,"Producer produced %d items\n\n",prate[pcount] );
            store+=prate[pcount];
            pcount = (pcount + 1);
        }
        
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *cno)
{   
    for(int i = 0; i < max; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        //critical secttion
        if (store-crate[ccount]>0 && ccount<=n)
        {
        
            printf("Buffer space: %d\n", store);
            fprintf(fout,"Buffer space: %d\n", store);
            printf("Consumer consumed %d items\n\n",crate[ccount] );
            fprintf(fout,"Consumer consumed %d items\n\n",crate[ccount] );

            store -= crate[ccount];
            ccount = (ccount+1);    
        
        }
         
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}


int main()
{   FILE *fin;
    int i,j,count=0,a[5] = {1,2,3,4,5};
    fin= fopen("input.txt","r");
    fout = fopen("output.txt", "w");
    if ( fin == NULL ) 
    { 
        printf( "input.txt file failed to open." ) ; 
    } 
    else{
        fscanf (fin, "%d %d ", &i, &j);    
        while (!feof (fin))
        {   
            prate[count] = i;
            crate[count] = j;

            // printf ("%d %d %d\n", i,j,k);
            fscanf (fin, "%d %d", &i, &j); 
            count++;
        }
        prate[count] = i;
        crate[count] = j;
    }
    n = count;

    printf("\n\n------Output------\n\n");
    fprintf(fout,"------Output------\n\n");
    pthread_t pro[5],con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,buffer);
    sem_init(&full,0,0);

        for(int i = 0; i < 1; i++) {
          pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
        }
        for(int i = 0; i < 1; i++) {
           pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
        }
        
    
    
  
    for(int i = 0; i < 1; i++) {
        pthread_join(con[i], NULL);
    }
    for(int i = 0; i < 1; i++) {
        pthread_join(pro[i], NULL);
    }
    

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    printf("Buffer space: %d\n",buffer);
    fprintf(fout,"Buffer space: %d\n",buffer);
   
    fclose(fout);
    fclose (fin);  
    return 0;
    
}