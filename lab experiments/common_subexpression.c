#include <stdio.h>
#include <string.h>
int main(void){
    int n; if(scanf("%d",&n)!=1) return 1;
    char lhs[32][32], rhs[32][128], line[256];
    for(int i=0;i<n;i++){ if(scanf("%255s",line)!=1) return 1; /* no spaces expected: t1=a+b */ 
        char *eq=strchr(line,'='); strncpy(lhs[i],line,(size_t)(eq-line)); lhs[i][eq-line]='\0'; strcpy(rhs[i],eq+1); }
    char mapFrom[32][32], mapTo[32][32]; int nm=0;
    printf("Optimized TAC (after CSE):\n");
    for(int i=0;i<n;i++){
        char useRhs[128]; strcpy(useRhs,rhs[i]);
        /* substitute mapped temps in rhs tokens: simple whole-token replace for single temps */
        for(int m=0;m<nm;m++){ /* replace occurrences of mapFrom as whole rhs */
            if(strcmp(useRhs,mapFrom[m])==0) strcpy(useRhs,mapTo[m]); }
        int dup=-1; for(int j=0;j<i;j++) if(strcmp(rhs[j],useRhs)==0 && strchr(useRhs,'+')!=NULL){ dup=j; break; }
        /* duplicate detection only for binary exprs (contains operator) */
        if(dup>=0 && (strchr(useRhs,'+')||strchr(useRhs,'-')||strchr(useRhs,'*')||strchr(useRhs,'/'))){
            printf("/* %s = %s eliminated (common subexpression, use %s) */\n", lhs[i], useRhs, lhs[dup]);
            strcpy(mapFrom[nm],lhs[i]); strcpy(mapTo[nm],lhs[dup]); nm++;
        } else {
            /* substitute any mapped temp appearing as operand: handle a op b form */
            printf("%s = %s\n", lhs[i], useRhs);
            strcpy(rhs[i],useRhs);
        }
    }
    return 0;
}
