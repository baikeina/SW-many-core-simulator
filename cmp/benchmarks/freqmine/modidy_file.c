#include<stdio.h>

int main(){
    int k;
int i;
int j=0.5;
int l=1;
    FILE * f1;
    FILE * f2;
    f1=fopen("rFreqFei.txt","r");
    f2=fopen("rFreq20-0.5.txt","w+");
    for(i=0;!feof(f1);i++)
    {
        fscanf(f1,"%d",&k);
        if(k!=0)
        {   
            fprintf(f2,"%d\n",j); 
         }
        else fprintf(f2,"%d\n",l);
    }
fclose(f1);
fclose(f2);
return 1;
}
