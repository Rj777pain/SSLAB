#include<stdio.h>
#include<stdlib.h>

//Function for FCFS scheduling
void findFcfsTime(int n, int *at, int *bt, int *tat, int *wt){
    int cum=0,i;
    for (i=0; i < n; i++){
        *(tat+i) = abs(cum - *(at+i))+ *(bt + i);
        *(wt+i) = *(tat+i) - *(bt+i);
        cum += *(bt + i);
    }
}

void main(){
    int n=0, *at, *bt, *tat, *wt;
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
    
    while (!feof(fptr)){
        fscanf(fptr, "%d\t%d\t%d", at+i, bt+i, &c);
        i++;        
    }
    //calling fcfs schedulin g function
    findFcfsTime(n, at, bt, tat,wt);
    printf("FCFS\n");
    printf("Turn Arount Time\tWaiting Time\n");
    for (i=0; i < n; i++){
        printf("%d\t\t\t%d\n", *(tat + i), *(wt + i));
    }
    
    
    
    
    free(at);
    free(bt);
    free(tat);
    free(wt);
    fclose(fptr);
}
