#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

FILE *f1, *f2, *f3, *f4, *f5;
char mne[20], opnd[20], la[20], name[20], mne1[20], opnd1[20], arg[20];

// pass1 of one pass macro assembler
void pass1()
{
    fscanf(f1, "%s%s%s", la, mne, opnd);
    while (strcmp(mne, "MEND") != 0)
    {
        if (strcmp(mne, "MACRO") == 0)
        {
            fprintf(f2, "%s\n", la);
            fprintf(f3, "%s\t%s\n", la, opnd);
        }
        else
            fprintf(f3, "%s\t%s\n", mne, opnd);
        fscanf(f1, "%s%s%s", la, mne, opnd);
    }
    fprintf(f3, "%s", mne);
    printf("PASS 1 completed");
    rewind(f1);
    rewind(f2);
    rewind(f3);
}

// pass2 od two pass macro assembler
void pass2()
{
    int len;
    fscanf(f1, "%s%s%s", la, mne, opnd);
    while (strcmp(mne, "END") != 0)
    {
        if (strcmp(mne, "MACRO") == 0)
        {
            fscanf(f1, "%s%s%s", la, mne, opnd);
            while (strcmp(mne, "MEND") != 0)
                fscanf(f1, "%s%s%s", la, mne, opnd);
        }
        else
        {
            fscanf(f2, "%s", name);
            if (strcmp(mne, name) == 0)
            {
                len = strlen(opnd);
                for (int i = 0; i < len; i++)
                {
                    if (opnd[i] != ',')
                        fprintf(f4, "%c", opnd[i]);
                    else
                        fprintf(f4, "\n");
                }
                fseek(f2, SEEK_SET, 0);
                fseek(f4, SEEK_SET, 0);
                fscanf(f3, "%s%s", mne1, opnd1);
                fprintf(f5, ".\t%s\t%s\n", mne1, opnd);
                fscanf(f3, "%s%s", mne1, opnd1);
                while (strcmp(mne1, "MEND") != 0)
                {
                    if ((opnd1[0] == '&'))
                    {
                        fscanf(f4, "%s", arg);
                        fprintf(f5, "-\t%s\t%s\n", mne1, arg);
                    }
                    else
                        fprintf(f5, "-\t%s\t%s\n", mne1, opnd1);
                    fscanf(f3, "%s%s", mne1, opnd1);
                }
            }
            else
                fprintf(f5, "%s\t%s\t%s\n", la, mne, opnd);
        }
        fscanf(f1, "%s%s%s", la, mne, opnd);
    }
    fprintf(f5, "%s\t%s\t%s\n", la, mne, opnd);
    printf("\nPASS 2 completed");
}

// display output
void out(){
    rewind(f5);
    printf("\nOutput\n");
    while (!feof(f5))
    {
        fscanf(f5, "%s\t%s\t%s\n", la, mne, opnd);
        printf("%s\t%s\t%s\n", la, mne, opnd);
    }
    
}

void main()
{

    char mne[20], opnd[20], la[20];

    f1 = fopen("minp2.txt", "r");
    f2 = fopen("ntab2.txt", "w+");
    f3 = fopen("dtab2.txt", "w+");
    f4 = fopen("atab2.txt", "w+");
    f5 = fopen("op2.txt", "w+");
    pass1();
    pass2();
    out();
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
}