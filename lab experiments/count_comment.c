#include <stdio.h>
int main(void){
    int c, prev=0, single=0, multi=0, inS=0, inM=0;
    while((c=getchar())!=EOF){
        if(inS){ if(c=='\n') inS=0; }
        else if(inM){ if(prev=='*' && c=='/') inM=0; }
        else if(prev=='/' && c=='/'){ single++; inS=1; }
        else if(prev=='/' && c=='*'){ multi++; inM=1; }
        prev=c;
    }
    printf("Single-line comments : %d\n", single);
    printf("Multi-line comments  : %d\n", multi);
    printf("Total comments       : %d\n", single+multi);
    return 0;
}
