#include <stdio.h>
#include <string.h>
#define MAXP 32
#define MAXS 128
int main(void){
    int n; if(scanf("%d",&n)!=1) return 1;
    char line[MAXS]; char L=0; char alpha[MAXP][MAXS]; char beta[MAXP][MAXS]; int na=0, nb=0;
    for(int i=0;i<n;i++){ if(scanf("%127s",line)!=1) return 1;
        L=line[0]; char *r=line+2;
        if(r[0]==L){ strcpy(alpha[na++], r+1); } else { strcpy(beta[nb++], r); } }
    if(na==0){ printf("No direct left recursion\n"); return 0; }
    printf("Left recursion eliminated:\n");
    for(int i=0;i<nb;i++) printf("%c -> %s%c'\n", L, beta[i], L);
    printf("%c' -> ", L);
    for(int i=0;i<na;i++) printf("%s%c' %s ", alpha[i], L, i+1<na?"|":"");
    printf("| e\n");
    return 0;
}
