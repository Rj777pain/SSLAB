#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

void main (){
	process *p;
    linkAl *lin, *pointer;
    FILE *mem, *proc,*fout;
    if ((fout = fopen("output.txt", "w")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
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
}
