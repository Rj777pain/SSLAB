#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int id;
	char val;
	int allocated;
}seqAl;

void main(){
	seqAl *seq;
    int i;
    FILE *fptr,*fout;
    int n=0, ind, len;
    char c[20];
    if ((fout = fopen("output.txt", "w")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
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
 	fclose(fout);
 	fclose(fptr);
 	free(seq);
}
