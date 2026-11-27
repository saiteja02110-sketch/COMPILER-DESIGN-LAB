#include <stdio.h>
#include <string.h>
#define MAXP 32
#define MAXS 128
char lhs[MAXP]; char rhs[MAXP][MAXS]; int n;
char firstSet[256][MAXS];
int isNT(char c){ return c>='A' && c<='Z'; }
void addTo(char *set, char c){ if(!strchr(set,c)){ int l=(int)strlen(set); set[l]=c; set[l+1]='\0'; } }
int main(void){
    if(scanf("%d",&n)!=1) return 1;
    char line[MAXS];
    for(int i=0;i<n;i++){ if(scanf("%127s",line)!=1) return 1; lhs[i]=line[0]; strcpy(rhs[i],line+2); }
    int changed=1;
    while(changed){
        changed=0;
        for(int i=0;i<n;i++){
            char L=lhs[i]; char *r=rhs[i];
            if(r[0]=='e' && r[1]=='\0'){ if(!strchr(firstSet[(unsigned char)L],'e')){addTo(firstSet[(unsigned char)L],'e'); changed=1;} continue; }
            int allEps=1;
            for(int j=0;r[j];j++){
                char s=r[j];
                if(!isNT(s)){ if(!strchr(firstSet[(unsigned char)L],s)){addTo(firstSet[(unsigned char)L],s); changed=1;} allEps=0; break; }
                char *fs=firstSet[(unsigned char)s];
                for(int k=0;fs[k];k++) if(fs[k]!='e' && !strchr(firstSet[(unsigned char)L],fs[k])){ addTo(firstSet[(unsigned char)L],fs[k]); changed=1; }
                if(!strchr(fs,'e')){ allEps=0; break; }
            }
            if(allEps && !strchr(firstSet[(unsigned char)L],'e')){ addTo(firstSet[(unsigned char)L],'e'); changed=1; }
        }
    }
    char seen[256]={0};
    for(int i=0;i<n;i++){ char L=lhs[i]; if(seen[(unsigned char)L]) continue; seen[(unsigned char)L]=1;
        printf("FIRST(%c) = { ",L); char *s=firstSet[(unsigned char)L];
        for(int k=0;s[k];k++) printf("%c%s",s[k],s[k+1]?", ":" ");
        printf("}\n"); }
    return 0;
}
