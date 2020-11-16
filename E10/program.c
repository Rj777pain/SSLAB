// 0000	ALPHA
// 0000	BETA
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define MAX 100
int start, lc,len;
typedef struct s{
	int old;
	int mod;
}md;
FILE *f1,*f2,*fo,*fi,*fsym,*fopt,*fot;
void symtab(char label[20])
{
	char* filename = "symtab.txt";
	if(f1 == NULL)
	{
		printf("Could not open file : %s", filename);
		return;
	}
	fprintf(f1,"%d\t%s\n",lc,label);
	fprintf(fsym,"0000\t%s\n",label);
	
}

void searchOptab(char operation[20])
{
	FILE *f2;
	char op[20],id[20];
	char* filename = "optab.txt";
	f2 = fopen(filename , "r");
	if (f2 == NULL){
        	printf("Could not open file %s",filename);
        	return;
    	}
    	while(!feof(f2))
    	{
    		fscanf(f2,"%s	%s",op,id);
    		if(strcmp(operation , op) == 0)
		{
			lc = lc + 3;
			break;
		}
	}
	fclose(f2);
	//printf("LC::%d\n",lc);
}

void searchVariables(char operation[20], char address[20])
{
	if(strcmp(operation,"WORD") == 0)
	{
		lc = lc+3;
	}
	else
		if(strcmp(operation,"RESW") == 0)
		{
			int n = atoi(address);
			lc = lc + (3*n);
		}
}
int readFile()
{
    	int i=0,st,plength;
    	char label[20],operation[20],address[20];
    	FILE *fp;
	char* filename = "input.txt";
 
	char* symtabname = "symtab.txt";
	f1 = fopen(symtabname, "r+");
	fprintf(f1,"*\tALPHA\n");
	fprintf(f1,"*\tBETA\n");
	char* copyProgram = "copy.txt";
	f2 = fopen(copyProgram, "w");
	
    	fp = fopen(filename, "r");
    	if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    	}
	fscanf(fp,"%s	%s	%d",label,operation,&st);
	fprintf(f2,"-\t%s\t%s\t%d\n",label,operation,st);
	if(strcmp(operation , "START") == 0)
	{
		start = st;
		lc = start;
	}
	else 
	{
		lc=0;
	}
	
	fscanf(fp,"%s	%s",label,operation);
    	while (!feof(fp))
    	{    
        	fscanf(fp,"%s",address);
        	if(strcmp(label,"-") != 0)
        	{
        		symtab(label);
        	}
        	
        	fprintf(f2,"%d\t%s\t%s\t%s\n",lc,label,operation,address);
        	searchOptab(operation);
        	searchVariables(operation , address);
		fscanf(fp,"%s%s",label,operation);
		if(strcmp(operation , "END") == 0)
		{
			plength = lc - st;
		}
    	}
		len=plength;
    	fclose(fp);
	
	fclose(f2);
}

void modRec(){

}

void outCode(){
	md m[5];
	char c[10];
	int i,starti,temp,a,b;
    char lab[10],mn[10],op[10],addr[10],name[10],temps[10],start[10]="00";
    fi=fopen("copy.txt","r");
    fopt=fopen("optab.txt","r");
    fo=fopen("result.txt","w");
	fot=fopen("output.txt","w+");
	
    fscanf(fi,"%s %s %s %s",addr,lab,mn,op);
    if(strcmp(mn,"START")==0){
        strcpy(start,op);
        strcpy(name,lab);
        fscanf(fi,"%s %s %s %s",addr,lab,mn,op);
    }
    starti=atoi(start);
	printf("\nRESULT\n");
    printf("H^%s^%06d^%06d\nT^%06d^%d",name,starti,len,starti,len);
    fprintf(fo,"H^%s^%06d^%06d\nT^%06d^%d",name,starti,len,starti,len);
    while(strcmp(mn,"END")!=0){
        fseek(fopt,0,SEEK_SET);
        fscanf(fopt,"%s %d",temps,&temp);
        while(!feof(fopt))
        {
            if(strcmp(temps,mn)==0)
            {
                printf("^%02d",temp);
                fprintf(fo,"^%02d",temp);
				fprintf(fot,"%d",temp);
                fseek(fsym,0,SEEK_SET);
                fscanf(fsym,"%d %s",&temp,temps);
                while(!feof(fsym))
                {
                    if(strcmp(temps,op)==0)
                    {	
						
                        printf("%04d",temp);
                        fprintf(fo,"%04d",temp);
						fprintf(fot,"\t%d\n",temp);
                        break;
                    }
                    fscanf(fsym,"%d %s",&temp,temps);
                }
                break;
            }
            fscanf(fopt,"%s %d",temps,&temp);
        }
        if(strcmp(mn,"WORD")==0)
        {
            printf("^%06d",atoi(op));
            fprintf(fo,"^%06d",atoi(op));
        }
        else if (strcmp(mn,"BYTE")==0)
        {
            printf("^");
            fprintf(fo,"^");
            for(i=2;i<strlen(op)-1;i++)
            {
                printf("%d",op[i]);
                fprintf(fo,"%d",op[i]);
            }
        }
        fscanf(fi,"%s %s %s %s",addr,lab,mn,op); 
    }
	rewind(f1);
	fscanf(f1,"%s\t%s\n",&c,temps);
	fscanf(f1,"%s\t%s\n",&c,temps);
	b=1001;
	while (!feof(f1))
	{	
		fscanf(f1,"%d\t%s\n",&a,temps);
		//printf("%d",a);
		fprintf(fot,"%d\t%d\n",a,b);
		b=b+3;
	}
	rewind(fot);
	
	while (!feof(fot))
	{
		fscanf(fot,"%d\t%d\n",&a,&b);
		if(b==0)
			continue;
		fprintf(fo,"\nT^%d^02^%d",b,a);
		printf("\nT^%d^02^%d",b,a);
		
	}
	
	
	
    printf("\nE^%06d",starti);
    fprintf(fo,"\nE^%06d",starti);
	rewind(f1);rewind(fsym);
	printf("\n\n");
	// while(!feof(fsym)){
	// 	fscanf("")
	// }
	fprintf(f1,"*\tALPHA\n");
	fprintf(f1,"*\tBETA\n");
	
	fclose(fi);
    fclose(fo);
    fclose(fopt);
    fclose(fsym);
	fclose(f1);
}

void main()
{
	fsym=fopen("symbol.txt","r+");
    readFile();
	outCode();
}
