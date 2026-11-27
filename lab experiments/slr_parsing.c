#include <stdio.h>
#include <string.h>
/* SLR parser, Dragon-book table for E->E+T|T, T->T*F|F, F->(E)|id ; tokens i=id */
int actionType[12][6]; int actionNum[12][6]; /* cols: i + * ( ) $ ; type 0 err 1 shift 2 reduce 3 accept */
int goTo_[12][3]; /* E T F */
char prodLhs[7]={' ', 'E','E','T','T','F','F'};
int prodLen[7]={0,3,1,3,1,3,1};
void setA(int s,int c,int t,int n){ actionType[s][c]=t; actionNum[s][c]=n; }
int colOf(char a){ if(a=='i') return 0; if(a=='+') return 1; if(a=='*') return 2; if(a=='(') return 3; if(a==')') return 4; return 5; }
int main(void){
    for(int i=0;i<12;i++) for(int k=0;k<3;k++) goTo_[i][k]=-1;
    setA(0,0,1,5); setA(0,3,1,4); goTo_[0][0]=1; goTo_[0][1]=2; goTo_[0][2]=3;
    setA(1,1,1,6); setA(1,5,3,0);
    setA(2,1,2,2); setA(2,2,1,7); setA(2,4,2,2); setA(2,5,2,2);
    setA(3,1,2,4); setA(3,2,2,4); setA(3,4,2,4); setA(3,5,2,4);
    setA(4,0,1,5); setA(4,3,1,4); goTo_[4][0]=8; goTo_[4][1]=2; goTo_[4][2]=3;
    setA(5,1,2,6); setA(5,2,2,6); setA(5,4,2,6); setA(5,5,2,6);
    setA(6,0,1,5); setA(6,3,1,4); goTo_[6][1]=9; goTo_[6][2]=3;
    setA(7,0,1,5); setA(7,3,1,4); goTo_[7][2]=10;
    setA(8,1,1,6); setA(8,4,1,11);
    setA(9,1,2,1); setA(9,2,1,7); setA(9,4,2,1); setA(9,5,2,1);
    setA(10,1,2,3); setA(10,2,2,3); setA(10,4,2,3); setA(10,5,2,3);
    setA(11,1,2,5); setA(11,2,2,5); setA(11,4,2,5); setA(11,5,2,5);
    char raw[256]; if(scanf("%255s",raw)!=1) return 1;
    char toks[256]; int j=0; for(int i=0;raw[i];i++){ if(raw[i]=='i'&&raw[i+1]=='d'){ toks[j++]='i'; i++; } else toks[j++]=raw[i]; } toks[j]='\0'; strcat(toks,"$");
    int st[256]; int sp=0; st[0]=0; int ip=0;
    printf("SLR Parsing:\n");
    while(1){
        int s=st[sp]; char a=toks[ip]; int c=colOf(a); int t=actionType[s][c];
        if(t==1){ printf("Shift %c  (state %d -> %d)\n", a=='i'?'i':a, s, actionNum[s][c]); st[++sp]=actionNum[s][c]; ip++; }
        else if(t==2){ int pn=actionNum[s][c]; sp-=prodLen[pn]; int ns=goTo_[st[sp]][prodLhs[pn]=='E'?0:prodLhs[pn]=='T'?1:2];
            printf("Reduce by %c -> production %d, goto state %d\n", prodLhs[pn], pn, ns); st[++sp]=ns; }
        else if(t==3){ printf("String Accepted\n"); return 0; }
        else { printf("String Rejected\n"); return 0; }
    }
}
