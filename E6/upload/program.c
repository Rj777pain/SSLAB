#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
FILE *fout;
void *producer (void *) ;
void *consumer(void *) ;
sem_t empty, full, mutex ;
int prate[20], crate[20],n,pcount = 0,ccount = 0 ;

int buffer[10] /*note extra long space!*/ ;
int ID[10] ;
int BUFFER_SIZE = 20 ;
int n;
int store=0;

void main() {
    pthread_t TID[10] ;
    FILE *fin;
    int i,j,count=0;
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

    sem_init(&empty, 0, BUFFER_SIZE) ;
    sem_init(&full, 0, 0) ;
    sem_init(&mutex, 0, 1) ;

    for(i = 0; i < 10; i++) {
        ID[i] = i ;
        buffer[i] = -1 ;
    }

    //for(i = 0; i < 5000; i += 2) {
        pthread_create(&TID[0], NULL, producer, (void *) &ID[0]) ;
        
        pthread_create(&TID[1], NULL, consumer, (void *) &ID[1]) ;
      

       
    //}

      
    
    for(i = 0; i < 1 ; i++) {
        pthread_join(TID[i], NULL) ;
    }
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    printf("Buffer space: %d\n",BUFFER_SIZE);
    fprintf(fout,"Buffer space: %d\n",BUFFER_SIZE);
   
    fclose(fout);
    fclose (fin);  
}

void *producer(void *Boo) {
    int *ptr;
    int ID;
    ptr = (int *) Boo;
    ID = *ptr;
    while (1) {
        
        sem_wait(&empty);
        sem_wait(&mutex);
        
        if (store+prate[pcount]<BUFFER_SIZE && pcount<=n)
        {         

            printf("Producer produced %d items\n",prate[pcount] );
            fprintf(fout,"Producer produced %d items\n",prate[pcount] );
            store+=prate[pcount];
            pcount = (pcount + 1);
            printf("Buffer space: %d\n\n", store);
            fprintf(fout,"Buffer space: %d\n\n", store);
        }

        sem_post(&mutex);
        sem_post(&full);
    }
 }

void *consumer (void *Boo) {
    static int nextConsumed = 0 ;
    int *ptr ;
    int ID ;
    ptr = (int *) Boo ;
    ID = *ptr ;
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);

        if (store-crate[ccount]>0 && ccount<=n)
        {
        

            printf("Consumer consumed %d items\n",crate[ccount] );
            fprintf(fout,"Consumer consumed %d items\n",crate[ccount] );

            store -= crate[ccount];
            ccount = (ccount+1);    
            printf("Buffer space: %d\n\n", store);
            fprintf(fout,"Buffer space: %d\n\n", store);
        
        }

        sem_post(&mutex);
        sem_post(&empty);

    }
}