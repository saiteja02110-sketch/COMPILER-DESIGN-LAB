#include <stdio.h>
#include <string.h>
#define MAXS 128
int main(void){
    int n; if(scanf("%d",&n)!=1) return 1;
    char line[MAXS]; char prods[16][MAXS]; char L=0;
    for(int i=0;i<n;i++){ if(scanf("%127s",line)!=1) return 1; L=line[0]; strcpy(prods[i], line+2); }
    if(n<2){ printf("Need at least 2 productions\n"); return 0; }
    /* longest common prefix of first two productions */
    int p=0; while(prods[0][p] && prods[0][p]==prods[1][p]) p++;
    if(p==0){ printf("No common prefix, no left factoring needed\n"); return 0; }
    char prefix[MAXS]; strncpy(prefix, prods[0], p); prefix[p]='\0';
    printf("Left factored grammar:\n");
    printf("%c -> %s%c'\n", L, prefix, L);
    for(int i=0;i<n;i++){
        if(strncmp(prods[i], prefix, p)==0) printf("%c' -> %s\n", L, prods[i][p] ? prods[i]+p : "e");
        else printf("%c -> %s\n", L, prods[i]);
    }
    return 0;
}
