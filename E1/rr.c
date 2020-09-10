#include<stdio.h>
#include<stdlib.h>
#define q 3


//Function for round robin  scheduling
void findRRTime(int n, int *at, int *bt, int *tat, int *wt, int *prio){
    int *temp = (int *)malloc(n*sizeof(int));
    int cnt=0,j=0,i;
    for (i=0; i<n; i++){
        *(temp+i) = *(bt+i);
    }
    while(cnt<n){
    	for (i=0; i < n; i++){
    		if (*(at+i)<=j && *(at+i)>=0) {
                if (*(temp+i) <= q){
                    j += *(temp+i);
                    *(tat+i) = j - *(at+i);
                    *(wt+i)=*(tat+i)-*(bt+i);
                    *(at+i) = -1;
                    cnt++;
                } else {
                    j += q;
                    *(temp+i) -= q;
                }
            }
        }
        if (cnt >= n)
            break;
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
    
    //calling round robin scheduling function
    findRRTime(n, at, bt, tat,wt,prio);
    printf("Round Robin\n");
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
