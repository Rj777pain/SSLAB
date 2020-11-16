#include<stdio.h>
#include<string.h>
#define max 10

typedef struct sym
{
    char    hname[10];
    int     address;
}symtab;

FILE *fout;
symtab s[15];

int hashValue(char c1[5]){
    // char c1[5]="abc";
    int a,val=0,i,c;
    
    for ( i = 0; c1[i]!='\0'; i++)
    {
        val=val*128;
        c=c1[i];
        a=(int)c;
        val+=a;

    }
    return val%max;
}

void dispSym(){
    for (int i = 0; i < 10; i++)
    {      
        if (s[i].address==0)
        {
           continue;
        }
        
        printf("\n%d %s %d",i,s[i].hname,s[i].address);
    }
    
}

void inp(){
    int v,st=1,add;
    char c[10];
    while (st)
    {
        printf("\nEnter the address: ");
        scanf("%d",&add);
        printf("\nEnter the label: ");
        scanf("%s",c);
        v=hashValue(c);
        while ((s[v].address!=0)) v++;
        strcpy(s[v].hname,c);
        s[v].address=add;
        printf("\nContinue(1.Yes,0.No)?");
        scanf("%d",&st);
    
    }

}

void search(){
    char c[10];int v,i;
    printf("\nEnter the label: ");
    scanf("%s",c);
    fprintf(fout,"\nEnter the label: %s",c);
    v=hashValue(c);
    i=v;
    while (1)
    {
        if (s[i].address==0){
            printf("\nSymbol not present");
            fprintf(fout,"\nSymbol not present");
            break;
        }
        if(strcmp(s[i].hname,c)==0){
            printf("The label %s is present at index %d",s[i].hname,i);
            fprintf(fout,"The label %s is present at index %d",s[i].hname,i);
            break;
        }
        i++;
        i=i%max;
    }
    
   
}


void main(){
    int choice;

    fout = fopen("output.txt", "w");
    if (fout == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < 10; i++)
    {
        strcpy(s[i].hname,"");
        s[i].address=0;
    }  
    while (1)
    {
        printf("\nEnter your choice(1.Insert 2.Search 3.Display 4.Exit)");
        scanf("%d",&choice);
        if(choice==1) inp();
        else if(choice==2) search();
        else if(choice==3) dispSym();
        else
            break;

    }

}