#include<stdio.h>
#include<stdlib.h>
#define start 0
#define end 199

FILE *fout;
void display(int ar[25],int n){//function for calculating head movement
    int i,cnt=0,t;
    for(i=0;i<n-1;i++){
        //printf("\t%d",order[i]);
        t=ar[i]-ar[i+1];
        cnt+=t<0?t*-1:t;
    }
    printf("Total head movement:%d\n\n",cnt);
    fprintf(fout,"Total head movement:%d\n\n",cnt);
}

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// A function to implement bubble sort 
void bubbleSort(int arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
}

void printArray(int arr[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 

void fcfs(int ar[20],int n,int head){//function for fcfs disc sheduling
    int i,order[25];
    order[0]=head;
    
    for ( i=0; i < n; i++)
    {   
        order[i+1]=ar[i];
    }
    printf("FCFS:\n");
    fprintf(fout,"FCFS:\n");
    display(order,n+1);
}

void scan(int ar[20],int n,int head){//function for scan disc sheduling
    int i,order[25], dir,ord[25];
    order[0]=head;
    printf("Enter direction: 1.Larger 0.Smaller:");
    scanf("%d",&dir);
    for ( i=0; i < n; i++)
    {   
        order[i+1]=ar[i];
    }
    order[++i]=start;
    order[++i]=end;
    n+=3;
    bubbleSort(order,n);
    int j=0,k;
    if(dir){
        for(i=0;i<n && 1;i++){
            if(order[i]==head){
                k=i;
                ord[j]=order[i];j++;
            }
            else if(order[i]>head)
            {
                ord[j]=order[i];j++;
            
            }
        }
        i=k-1;
        while (i>0)
        {
            ord[j]=order[i];j++;
            i--;
        }
        
    }else{
    	for(i=n-1;i>=0;i--){
            if(order[i]==head){
                k=i;
                ord[j]=order[i];j++;
            }
            else if(order[i]<head)
            {
                ord[j]=order[i];j++;
            
            }
        }
        i=k+1;
        while (i<n-1)
        {
            ord[j]=order[i];j++;
            i++;
        }
	}
    //display(ord,n-1);
    printArray(ord,n);
    //printArray(order,n+3);
    // printf("FCFS:\n");
    // fprintf(fout,"FCFS:\n");
    // display(order,n+1);
}

void cscan(int ar[20],int n,int head){//function for scan disc sheduling
    int i,order[25], dir,ord[25];
    order[0]=head;
    printf("Enter direction: 1.Larger 0.Smaller:");
    scanf("%d",&dir);
    for ( i=0; i < n; i++)
    {   
        order[i+1]=ar[i];
    }
    order[++i]=start;
    order[++i]=end;
    n+=3;
    bubbleSort(order,n);
    int j=0,k;
    if(dir){
        for(i=0;i<n && 1;i++){
            if(order[i]==head){
                k=i;
                ord[j]=order[i];j++;
            }
            else if(order[i]>head)
            {
                ord[j]=order[i];j++;
            
            }
        }
        i=0;
        while (i<k)
        {
            ord[j]=order[i];j++;
            i++;
        }
        
    }else{
    	for(i=n-1;i>=0;i--){
            if(order[i]==head){
                k=i;
                ord[j]=order[i];j++;
            }
            else if(order[i]<head)
            {
                ord[j]=order[i];j++;
            
            }
        }
        i=n-1;
        while (i>k)
        {
            ord[j]=order[i];j++;
            i--;
        }
	}
    display(ord,n);
    //printArray(ord,n);
    //printArray(order,n+3);
    // printf("FCFS:\n");
    // fprintf(fout,"FCFS:\n");
    // display(order,n+1);
}
void main(){
    FILE *fptr;
    int i=0,ar[20],a,head;
    //opening input and output files
    if ((fout = fopen("output.txt", "w")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    if ((fptr = fopen("input.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    printf("------------------------------------------\n");
    fprintf(fout,"------------------------------------------\n");
    fprintf(fout,"Input\n");
    printf("Input\n");
    if(!feof(fptr)){
        fscanf(fptr,"%d",&head);//head pointer
        fprintf(fout,"Current head position :%d\n",head);
        printf("Current head position : %d\n",head);
    }
    
    printf("Sectors numbered from : %d to %d\n",start,end);
    fprintf(fout,"Sectors numbered from : %d to %d\n",start,end);
    
    
    printf("Requests are:");//inputing requests
    fprintf(fout,"Requests are:");
    i=0;
    while (!feof(fptr)){
        fscanf(fptr,"%d",&a);
        ar[i]=a;
        fprintf(fout,"\t%d",ar[i]);
        printf("\t%d",ar[i]);i++;
    }

    printf("\n------------------------------------------\n");
    fprintf(fout,"\n------------------------------------------\n");
    fprintf(fout,"Output\n");//showing output
    printf("Output\n");
   // fcfs(ar,i,head);
   cscan(ar,i,head);
    printf("------------------------------------------\n");
    fprintf(fout,"------------------------------------------\n");
}
