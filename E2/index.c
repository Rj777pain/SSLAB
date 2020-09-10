
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *fout;
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
    fprintf(fout,"\tIndexed Allocation");
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
			for(j=0;j<(p+i)->len;j++)
				printf("%d,",(indx+b-1)->a[j]);
				fprintf(fout,"%d,",(indx+b-1)->a[j]);
		}
		printf("\t\t%s\n",((p+i)->allocated == 1)? "Alloted":"Not Alloted");
		fprintf(fout,"\t\t%s\n",((p+i)->allocated == 1)? "Alloted":"Not Alloted");
	}
    
}
void main(){
	fout = fopen("output.txt", "w");
    if (fout == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    indAlloc();//calling Indexed allocation function
}
