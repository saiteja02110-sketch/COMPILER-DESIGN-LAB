#include <stdio.h>
#include <string.h>
int main(void){
    int n; if(scanf("%d",&n)!=1) return 1;
    char lhs[32][32], rhs[32][128], line[256];
    for(int i=0;i<n;i++){ if(scanf("%255s",line)!=1) return 1; char *eq=strchr(line,'='); strncpy(lhs[i],line,(size_t)(eq-line)); lhs[i][eq-line]='\0'; strcpy(rhs[i],eq+1); }
    int keep[32]={0}; char live[64][32]; int nl=0;
    /* final lhs is live result root: its rhs vars are live */
    strcpy(live[nl++], lhs[n-1]);
    for(int i=n-1;i>=0;i--){
        int isLive=0; for(int k=0;k<nl;k++) if(strcmp(live[k],lhs[i])==0) isLive=1;
        if(isLive){ keep[i]=1;
            /* add operand tokens (letters/temps) from rhs */
            char tmp[128]; strcpy(tmp,rhs[i]); char *tok=strtok(tmp,"+-*/");
            while(tok){ int exists=0; for(int k=0;k<nl;k++) if(strcmp(live[k],tok)==0) exists=1; if(!exists) strcpy(live[nl++],tok); tok=strtok(NULL,"+-*/"); }
        }
    }
    printf("Optimized TAC (after Dead Code Elimination):\n");
    for(int i=0;i<n;i++){ if(keep[i]) printf("%s = %s\n", lhs[i], rhs[i]); else printf("/* Dead code eliminated: %s = %s */\n", lhs[i], rhs[i]); }
    return 0;
}
