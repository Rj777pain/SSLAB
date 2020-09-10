#include<stdio.h>
#include<stdlib.h>

//Function for SJF scheduling
void findSjfTime(int n, int *at, int *bt, int *tat, int *wt){
    int i=0,j=0,min,p,k=0;
    while(k<n){
    	p=-1;
    	min=1000;
    	for (i=0; i < n; i++){
    	
    		if(*(at+i)<=j && *(wt+i)<0){
    			if(*(bt+i)<min){
    				p=i;
    				min=*(bt+i);
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
    for (i=0; i < n; i++){
        *(wt + i)=-1;
    }
    
    //calling sjf scheduling function
    findSjfTime(n, at, bt, tat,wt);
    printf("SJF\n");
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
