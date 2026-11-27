#include <stdio.h>
#include <string.h>
#define MAXP 32
#define MAXS 128
char lhs[MAXP]; char rhs[MAXP][MAXS]; int n;
char firstSet[256][MAXS]; char followSet[256][MAXS];
int isNT(char c){ return c>='A' && c<='Z'; }
void addTo(char *set, char c){ if(!strchr(set,c)){ int l=(int)strlen(set); set[l]=c; set[l+1]='\0'; } }
void computeFirstAll(void){
    int changed=1;
    while(changed){ changed=0;
        for(int i=0;i<n;i++){ char L=lhs[i]; char *r=rhs[i];
            if(r[0]=='e' && r[1]=='\0'){ if(!strchr(firstSet[(unsigned char)L],'e')){addTo(firstSet[(unsigned char)L],'e');changed=1;} continue; }
            int allEps=1;
            for(int j=0;r[j];j++){ char s=r[j];
                if(!isNT(s)){ if(!strchr(firstSet[(unsigned char)L],s)){addTo(firstSet[(unsigned char)L],s);changed=1;} allEps=0; break; }
                char *fs=firstSet[(unsigned char)s];
                for(int k=0;fs[k];k++) if(fs[k]!='e' && !strchr(firstSet[(unsigned char)L],fs[k])){addTo(firstSet[(unsigned char)L],fs[k]);changed=1;}
                if(!strchr(fs,'e')){ allEps=0; break; } }
            if(allEps && !strchr(firstSet[(unsigned char)L],'e')){addTo(firstSet[(unsigned char)L],'e');changed=1;} } }
}
int main(void){
    if(scanf("%d",&n)!=1) return 1;
    char line[MAXS];
    for(int i=0;i<n;i++){ if(scanf("%127s",line)!=1) return 1; lhs[i]=line[0]; strcpy(rhs[i],line+2); }
    computeFirstAll();
    addTo(followSet[(unsigned char)lhs[0]],'$');
    int changed=1;
    while(changed){ changed=0;
        for(int i=0;i<n;i++){ char *r=rhs[i]; int len=(int)strlen(r);
            for(int j=0;j<len;j++){ char B=r[j]; if(!isNT(B)) continue;
                /* FIRST of beta = r[j+1..] */
                int nullable=1;
                for(int k=j+1;k<len;k++){ char s=r[k];
                    if(!isNT(s)){ if(!strchr(followSet[(unsigned char)B],s)){addTo(followSet[(unsigned char)B],s);changed=1;} nullable=0; break; }
                    char *fs=firstSet[(unsigned char)s];
                    for(int t=0;fs[t];t++) if(fs[t]!='e' && !strchr(followSet[(unsigned char)B],fs[t])){addTo(followSet[(unsigned char)B],fs[t]);changed=1;}
                    if(!strchr(fs,'e')){ nullable=0; break; } }
                if(j==len-1) nullable=1;
                if(nullable){ char *fl=followSet[(unsigned char)lhs[i]];
                    for(int t=0;fl[t];t++) if(!strchr(followSet[(unsigned char)B],fl[t])){addTo(followSet[(unsigned char)B],fl[t]);changed=1;} } } } }
    char seen[256]={0};
    for(int i=0;i<n;i++){ char L=lhs[i]; if(seen[(unsigned char)L]) continue; seen[(unsigned char)L]=1;
        printf("FOLLOW(%c) = { ",L); char *s=followSet[(unsigned char)L];
        for(int k=0;s[k];k++) printf("%c%s",s[k],s[k+1]?", ":" ");
        printf("}\n"); }
    return 0;
}
