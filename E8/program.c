#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define MAX 100
int start, lc;

FILE *f1,*f2;
void symtab(char label[20])
{
	char* filename = "symtab.txt";
	if(f1 == NULL)
	{
		printf("Could not open file : %s", filename);
		return;
	}
	fprintf(f1,"%d\t%s\n",lc,label);
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
	f1 = fopen(symtabname, "w");

	char* copyProgram = "copy.txt";
	f2 = fopen(copyProgram, "w");
	
    	fp = fopen(filename, "r");
    	if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    	}
	fscanf(fp,"%s	%s	%d",label,operation,&st);
	fprintf(f2,"%s\t%s\t%d\n",label,operation,st);
	if(strcmp(operation , "START") == 0)
	{
		start = st;
		lc = start;
	}
	else 
	{
		lc=0;
	}
	printf("LC::%d\n",lc);
	fscanf(fp,"%s	%s",label,operation);
    	while (!feof(fp))
    	{    
        	fscanf(fp,"%s",address);
        	if(strcmp(label,"-") != 0)
        	{
        		symtab(label);
        	}
        	printf("%d\t%s\t%s\t%s\n",lc,label,operation,address);
        	fprintf(f2,"%d\t%s\t%s\t%s\n",lc,label,operation,address);
        	searchOptab(operation);
        	searchVariables(operation , address);
		fscanf(fp,"%s%s",label,operation);
		if(strcmp(operation , "END") == 0)
		{
			plength = lc - st;
		}
    	}
    	printf("Program Length : %d\n", plength);
    	fclose(fp);
	fclose(f1);
	fclose(f2);
}

void main()
{
    readFile();
}
