
#include<stdio.h>
#include<pthread.h>  	//library for multi threading
#include<semaphore.h>   //library to implement semaphores
#include<unistd.h>	//library for sleep() function

//size is the total buffer size and buffer is the current allocation of buffer
int size=0,buffer=0;
sem_t s; 
FILE *fp;

//structres for production rate and consumption rate data;
struct prod {
	int n, rate[10];
}P;

struct cons {
	int n, rate[10];
}C;


//producer function that runs on one thread
void *producer() {
	//current array index initialized to 0
	int current = 0;
	//loop till entire array items are produced
	while(current<P.n) {
		//wait till other function releases lock and then apply lock to begin next iteration
		sem_wait(&s);
		if(buffer + P.rate[current] <= size) {
			//producer can produce
			buffer += P.rate[current];
			current ++;
			printf("Producer produced succesfully\nBuffer Filled : %d\n\n",buffer);
			fprintf(fp,"Producer produced succesfully\nBuffer Filled : %d\n\n",buffer);
		}
		else {
			//producer cannot produce
			printf("Producer cannot produce\n\n");
			fprintf(fp,"Producer cannot produce\n\n");
		}
		//release locks
		sem_post(&s);
		sleep(2);
	}
}


//consumer function that runs on the other thread
void *consumer() {
	//current array index initialized to 0
	int current = 0;
	//loop till entire array items are consumed
	while(current<C.n) {
		//wait till other function releases lock and then apply lock to begin next iteration
		sem_wait(&s); 
		if(buffer - C.rate[current] > 0) {
			//consumer can consume
			buffer -= C.rate[current];
			current ++;
			printf("Consumer consumed succesfully\nBuffer Filled : %d\n\n",buffer);
			fprintf(fp,"Consumer consumed succesfully\nBuffer Filled : %d\n\n",buffer);
		}
		else {
			//consumer cannot consume
			printf("Consumer cannot consume\n\n");
			fprintf(fp,"Consumer cannot consume\n\n");
		}
		//release lock
		sem_post(&s); 
		sleep(1);
	}
}



int main() {
	int i;
	//initialise semaphore variable
	sem_init(&s, 0, 1);
	fp = fopen("output.txt","w");
	//recieve inputs
	scanf("%d",&size);
	scanf("%d",&P.n);
	for(i=0;i<P.n;i++)
		scanf("%d",&P.rate[i]);
	scanf("%d",&C.n);
	for(i=0;i<C.n;i++)
		scanf("%d",&C.rate[i]);
	//declare two thread id's
	pthread_t ptid,ctid;
	//pthread_create creates and calls the functions which are to be run in the thread
	pthread_create(&ptid,NULL,producer,NULL);
    	pthread_create(&ctid,NULL,consumer,NULL);
    	//pthread_join makes sure that the main() function will not run till the respecive threads have finished execution
    	pthread_join(ptid,NULL);
    	pthread_join(ctid,NULL);
	return 0;
}
