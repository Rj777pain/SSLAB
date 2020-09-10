#include<stdio.h>
#include<stdlib.h>

//Function for priority scheduling
void findPrioTime(int n, int *at, int *bt, int *tat, int *wt, int *prio){
    int i=0,j=0,min,p,k=0;
    while(k<n){
    	p=-1;
    	min=1000;
    	for (i=0; i < n; i++){
    		
    		if(*(at+i)<=j && *(wt+i)<0){
    			if(*(prio+i)<min){
    				p=i;
    				min=*(prio+i);
				}
			}
		}
		if(p<0){
			j++;
			continue;
		}
	
		*(tat+p) = abs(j - *(at+p))+ *(bt + p);
        *(wt+p) = *(tat+p) - *(bt+p);
        j += *(bt + p);
        k++;
	}
}

void main(){
    int n=0, *at, *bt, *tat, *wt, *prio;
    int a, b , c, i = 0;


    FILE *fptr;
    if ((fptr = fopen("input.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    while (!feof(fptr)){
        fscanf(fptr, "%d\t%d\t%d", &a, &b, &c);
        n++;
    }
    rewind(fptr);

    at = (int*) malloc(n * sizeof(int));
    bt = (int*) malloc(n * sizeof(int));
    tat = (int*) malloc(n * sizeof(int));
    wt = (int*) malloc(n * sizeof(int));
    prio = (int*) malloc(n * sizeof(int));
    
    while (!feof(fptr)){
        fscanf(fptr, "%d\t%d\t%d", at+i, bt+i, prio+i);
        i++;        
    }
    for (i=0; i < n; i++){
        *(wt + i)=-1;
    }
    
    //calling priority scheduling function
    findPrioTime(n, at, bt, tat,wt,prio);
    printf("Priroty\n");
    printf("Turn Arount Time\tWaiting Time\n");
    for (i=0; i < n; i++){
        printf("%d\t\t\t%d\n", *(tat + i), *(wt + i));
        *(wt + i)=-1;
    }
    
    
    
    
    free(at);
    free(bt);
    free(tat);
    free(wt);
    fclose(fptr);
}
