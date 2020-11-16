#include<stdio.h>
#include<string.h>


void main(){
    char c1[5]="abc",c2;
    int a,val=0,i;
    
    for ( i = 0; c1[i]!='\0'; i++)
    {
        val=val*128;
        a=(int)c1[i];
        val+=a;

    }
    printf("%d",val);
    
}