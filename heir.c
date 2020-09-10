#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	int id;
	int fc;
	int dlink;
	int flink;
	int type;
	int loc;
	char nam[20];
}heir;
void inHeir(heir *h, int id, int fc,int type, int loc){
	
}
void dispH(heir *h,int n,int i){
//function to display directory h is heir structure pointer,n is id of node, i is the level
	int j=i;
	while(j>0){
		printf("\t");j--;
	}
	printf("%s",(h+n)->nam);
	if((h+n)->type){
		printf("\\");
		if((h+n)->flink>0){
			printf("\n");
		dispH(h,(h+n)->flink,i+1);
		}
	}
	if((h+n)->dlink>0){
		printf("\n");
	dispH(h,(h+n)->dlink,i);
	}
	//printf("%d\t%d\t%d\t%d\t%d\t%d\t%s\n",(h)->id,(h)->fc,(h)->dlink,(h)->flink,(h)->type,(h)->loc,(h)->nam);
}
void main(){
	FILE *fptr;
	int n=0, i, id, fc, dlink, flink, type, loc;
	char nam[20];
	heir *h;
	if ((fptr = fopen("hinput1.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    h = (heir*)malloc(10*sizeof(heir));
    while (!feof(fptr)) {
    	fscanf(fptr, "%d\t%d\t%d\t%d\t%d\t%d\t%s",&id,&fc,&dlink,&flink,&type,&loc,nam);
    	(h+n)->id=id;
    	(h+n)->fc=fc;
    	(h+n)->dlink=dlink;
		(h+n)->flink=flink;
		(h+n)->type=type;
		(h+n)->loc=loc;
	
    	strcpy((h+n)->nam,nam);
    	
    	printf("%d\t%d\t%d\t%d\t%d\t%d\t%s\n",(h+n)->id,(h+n)->fc,(h+n)->dlink,(h+n)->flink,(h+n)->type,(h+n)->loc,(h+n)->nam);
    	n++;
    	//printf("%d\t%d\t%d\t%d\t%d\t%d\t%s\n",id,fc,dlink,flink,type,loc,nam);
    }
    dispH(h,0,0);
   
}
