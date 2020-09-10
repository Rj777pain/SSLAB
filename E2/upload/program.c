#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fout;

typedef struct{
	int id;
	char val;
	int allocated;
}seqAl;

void seqAlloc(){
	seqAl *seq;
    int i;
    FILE *fptr;
    int n=0, ind, len;
    char c[20];

    fprintf(fout,"\tSequencial Allocation\n");
    printf("\tSequencial Allocation\n");
    fprintf(fout,"------------------------------------------\n");
 	printf("------------------------------------------\n");
    if ((fptr = fopen("sequential_input.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    printf("Enter the number of blocks: ");
    scanf("%d", &n);
    fprintf(fout,"Enter the number of blocks: %d",n);
    seq = (seqAl*)malloc(n*sizeof(seqAl));
    for (i=0; i<n; i++){
        (seq+i)->id = i+1;
        (seq+i)->allocated = 0;
        (seq+i)->val = ' ';
    } 
    
    printf("Request's Starting Address: \n");
    fprintf(fout, "\nRequest's Starting Address: \n");
    while (!feof(fptr)) {
    	int j=0;
        fscanf(fptr, "%d\t%d\t%s", &ind, &len, c);
        if((ind+len-1)>n){
        	j=1;
		}
		for(i=0;i<len;i++){
			if((seq+ind+i-1)->allocated){
				j=1;
				break;
			}
		}
		if(j){
			printf("%d\tNot allocated\n", ind);
			fprintf(fout,"%d\tNot allocated\n", ind);
			continue;
		}
		printf("%d\tAllocated\n", ind);
		fprintf(fout,"%d\tAllocated\n", ind);
        for (j=0; j<len; j++){
            (seq+ind-1+j)->allocated = 1;
            (seq+ind-1+j)->val = c[j];
        }
    }
    printf("\nBlocks\tStatus\t\tContents\n");
    fprintf(fout,"\nBlocks\tStatus\t\tContents\n");
    for (i=0; i<n; i++){
    	printf("------------------------------------------\n");
        printf("%d\t%s\t  %c\n", (seq+i)->id, ((seq+i)->allocated == 0)? "Free":"Occupied", (seq+i)->val);
		fprintf(fout,"------------------------------------------\n");
        fprintf(fout,"%d\t%s\t  %c\n", (seq+i)->id, ((seq+i)->allocated == 0)? "Free":"Occupied", (seq+i)->val);
 	}
 	
 	fprintf(fout,"------------------------------------------\n");
 	printf("------------------------------------------\n");
 	
 	fclose(fptr);
 	free(seq);
}


typedef struct {
  int p_id;
  char val;
  int index;
  int next_index;
} linkAl;//structure for linked indexes 

typedef struct{
	int p_id;
	int start;
	int end;
	int allocated;
}process;//structre for processes

void linkAlloc(){
	process *p;
    linkAl *lin, *pointer;
    FILE *mem, *proc;
   
    int n=0, ind, next, len, p_id,i,cnt,last,j;
    char c[20];
    if ((mem = fopen("linked_memory_input.txt", "r")) == NULL) {//opening file for linked indexes
        printf("Error! opening memory link file");
        exit(1);
    }
    if ((proc = fopen("linked_process_input.txt", "r")) == NULL) {//opening file of process data
        printf("Error! opening process file");
        exit(1);
    }
    printf("\tLinked Allocation\n");
    fprintf(fout,"\tLinked Allocation\n");
    fprintf(fout,"------------------------------------------\n");
 	printf("------------------------------------------\n");
    printf("Enter the number of blocks: ");
    scanf("%d", &n);
    fprintf(fout,"Enter the number of blocks: %d",n);
    // n=10;
    lin = (linkAl*)malloc(n*sizeof(linkAl));
    p = (process*)malloc(n*sizeof(process));//allocating pointers
    for (i=0; i<n; i++){
        (lin+i)->index = i+1;
        (lin+i)->next_index = -1;
        (lin+i)->p_id = -1;
    }
    int free=1, links=0;
    while (!feof(mem)) {
        fscanf(mem, "%d\t%d", &ind, &next);
        (lin+ind-1)->next_index = next;  
        free++;   
    }
    //printf("\n%d",free);
    i=0;
    while (!feof(proc)) {
        fscanf(proc, "%d\t%d\t%s", &p_id, &len, c);
        (p+i)->p_id=p_id;
        (p+i)->allocated=0;
        (p+i)->start=0;
        (p+i)->end=0;
        i++;
	}
	rewind(proc);
	cnt=i;i=0;
	last=1;
    while (!feof(proc)) {
        fscanf(proc, "%d\t%d\t%s", &p_id, &len, c);
       	(p+i)->start=last;
       	//printf("%d",len);
		if(len<=free){
			for (j=0; j<len; j++){
           		(lin+last-1)->p_id= p_id;
            	(lin+last-1)->val = c[j];
            	(p+i)->end=last;
            	last=(lin+last-1)->next_index;
       		}
       		
       		(p+i)->allocated=1;
       		free=free-len;
       	//	printf("%d\t%d\t%d\t%s\n", (p+i)->p_id,(p+i)->start,(p+i)->end, ((p+i)->allocated == 1)? "Alloted":"Not Alloted");
		}
		i++;
	}
	printf("\nProcess\tStart\tEnd\tStatus\n");
	fprintf(fout,"\nCurrent Process\tStart\tEnd\tStatus\n");
	for (i=0; i<cnt; i++){    
        printf("%d\t%d\t%d\t%s\n", (p+i)->p_id,(p+i)->start,(p+i)->end, ((p+i)->allocated == 1)? "Alloted":"Not Alloted");
        fprintf(fout,"%d\t%d\t%d\t%s\n", (p+i)->p_id,(p+i)->start,(p+i)->end, ((p+i)->allocated == 1)? "Alloted":"Not Alloted");
 	}
 	printf("\nContents of process\n");
 	fprintf(fout,"\nContents of process\n");
 	last=1;
 	for(i=0; i<cnt; i++){
 		printf("P%d\n",(p+i)->p_id);
 		fprintf(fout,"P%d\n",(p+i)->p_id);
 		while((p+i)->p_id==(lin+last-1)->p_id){
 			printf("\t%d\t%c\n",(lin+last-1)->index,(lin+last-1)->val);
 			fprintf(fout,"\t%d\t%c\n",(lin+last-1)->index,(lin+last-1)->val);
 			last=(lin+last-1)->next_index;
		}
		printf("------------------------------------------\n");
		fprintf(fout,"------------------------------------------\n");
	 }
	 
	 fclose(mem);
	 fclose(proc);
	
	 
}

typedef struct {
	int p_id;
    int allocated;
    int index;
    char val;
    int a[20];
}indAl;//structure of memory loaction
typedef struct{
	int p_id;
	int allocated;
	int index;
	int len;
}pro;//structure of processes


void indAlloc(){//Indexed allocation function
	indAl *indx;
	pro *p;
	int i,j,last;
	
	
	FILE *proc;
    int n=0, ind, p_id, len;
    char c[20];
    if ((proc = fopen("indexed_input.txt", "r")) == NULL) {
        printf("Error! opening memory link file");
        exit(1);
    } 
    printf("\tIndexed Allocation\n");
    fprintf(fout,"\tIndexed Allocation\n");
    fprintf(fout,"------------------------------------------\n");
 	printf("------------------------------------------\n");
    printf("Enter the number of blocks: ");
    scanf("%d", &n);
    // n = 10;
    fprintf(fout,"Enter the number of blocks: %d",n);
    indx = (indAl*)malloc(n*sizeof(indAl));
    for (i=0; i<n; i++){
        (indx+i)->allocated = 0;
        (indx+i)->val = ' ';
        (indx+i)->p_id = -1;
        (indx+i)->index = i+1;
    }
    int free = n;
    int cnt=0;i=0;
    p=(pro*)malloc(n*sizeof(pro));
    while (!feof(proc)) {
        fscanf(proc, "%d\t%d\t%d\t%s", &p_id, &len, &ind, c);
        (p+i)->p_id=p_id;
        
        (p+i)->allocated=0;
        (p+i)->index=ind;
        (p+i)->len=len;
        i++;
	}
	cnt=i;//count of processes
	rewind(proc);
	i=0;
	last=1;
	while (!feof(proc)) {
        fscanf(proc, "%d\t%d\t%d\t%s", &p_id, &len, &ind, c);
        if(len<free && (indx+ind-1)->allocated==0){
        	(p+i)->allocated=1;//giving flag that process is completed
			
        	(indx+ind-1)->allocated=1;
        	int j=0;
        	int k;
        	for(k=0;k<len;k++){
        		(indx+last-1)->val = c[k];
        		(indx+last-1)->allocated=1;//giving flag that location is filled
        		(indx+last-1)->p_id=p_id;
        		(indx+ind-1)->a[j++]=last;
        		while((indx+last-1)->allocated)
        			last++;
			}
			free-=len;
		}
		i++;
	}
	printf("Process\t\tIndex\t\tBlocks\t\tStatus\n");
	fprintf(fout,"Process\t\tIndex\t\tBlocks\t\tStatus\n");
    printf("-----------------------------------------------------\n");
    fprintf(fout,"------------------------------------------\n");
	for(i=0;i<cnt;i++){
		
		printf("P%d\t\t%d\t",(p+i)->p_id,(p+i)->index);
		fprintf(fout,"P%d\t\t%d\t",(p+i)->p_id,(p+i)->index);
		int b=(p+i)->index;
		if((p+i)->allocated){
			for(j=0;j<(p+i)->len;j++){
				printf("%d,",(indx+b-1)->a[j]);
				fprintf(fout,"%d,",(indx+b-1)->a[j]);
				
			}
		}
		printf("\t\t%s\n",((p+i)->allocated == 1)? "Alloted":"Not Alloted");
		fprintf(fout,"\t\t%s\n",((p+i)->allocated == 1)? "Alloted":"Not Alloted");
	}
	printf("\nAllocation\n");
	fprintf(fout,"\nAllocation\n");
	printf("Index\tBlock\tContents\n");
	fprintf(fout,"Index\tBlock\tContents\n");
	for(i=0;i<cnt && (p+i)->allocated;i++){
		int b=(p+i)->index;
		for(j=0;j<(p+i)->len;j++){
			int d=(indx+b-1)->a[j];
				printf("%d\t%d\t%c\n",b,(indx+b-1)->a[j],(indx+d-1)->val);
				fprintf(fout,"%d\t%d\t%c\n",b,(indx+b-1)->a[j],(indx+d-1)->val);
				
		}
	}
	
    
}

void main(){
	  // Setting the output file
    fout = fopen("output.txt", "w");
    if (fout == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
	printf("\n");
	fprintf(fout,"\n");
	seqAlloc();//calling sequential allocation function
	printf("\n");
	fprintf(fout,"\n");
	linkAlloc();//calling Linked allocation function
	printf("\n");
	fprintf(fout,"\n");
	indAlloc();//calling indexed allocation function
}
