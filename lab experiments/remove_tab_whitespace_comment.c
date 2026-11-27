#include <stdio.h>
int main(void){
    int c, prev=0, inS=0, inM=0, lastWasSpace=1;
    while((c=getchar())!=EOF){
        if(inS){ if(c=='\n'){ inS=0; putchar('\n'); lastWasSpace=1; } prev=c; continue; }
        if(inM){ if(prev=='*' && c=='/'){ inM=0; prev=0; continue; } prev=c; continue; }
        if(prev=='/' && c=='/'){ inS=1; prev=c; continue; }
        if(prev=='/' && c=='*'){ inM=1; prev=c; continue; }
        if(prev=='/'){ if(lastWasSpace==0 || 1) putchar('/'); lastWasSpace=0; }
        if(c=='/' ){ prev=c; continue; }
        if(c=='\t'||c==' '){ if(!lastWasSpace){ putchar(' '); lastWasSpace=1; } prev=c; continue; }
        if(c=='\n'){ putchar('\n'); lastWasSpace=1; prev=c; continue; }
        putchar(c); lastWasSpace=0; prev=c;
    }
    return 0;
}
