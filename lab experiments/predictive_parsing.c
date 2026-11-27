#include <stdio.h>
#include <string.h>
/* LL(1) for E->T R, R->+T R|e, T->F Y, Y->*F Y|e, F->(E)|id ; tokens: i=id, + * ( ) $ */
char input[256]; int ip=0; char stack[256]; int top=0;
void push(char c){ stack[top++]=c; stack[top]='\0'; }
char popc(void){ char c=stack[--top]; stack[top]='\0'; return c; }
int main(void){
    char raw[256]; if(scanf("%255s",raw)!=1) return 1;
    /* convert id -> i */
    int j=0; for(int i=0;raw[i];i++){ if(raw[i]=='i'&&raw[i+1]=='d'){ input[j++]='i'; i++; } else input[j++]=raw[i]; } input[j]='\0'; strcat(input,"$");
    push('$'); push('E');
    printf("Predictive Parsing:\n");
    printf("Stack: %s   Input: %s\n", stack, input+ip);
    int steps=0;
    while(top>0 && steps++<200){
        char X=stack[top-1]; char a=input[ip];
        if(X==a){ popc(); ip++; printf("Match %c             Stack: %s   Input: %s\n", a, stack, input+ip); if(a=='$') break; continue; }
        char prod[16]=""; int ok=1;
        if(X=='E') strcpy(prod,"TR");
        else if(X=='R'){ if(a=='+') strcpy(prod,"+TR"); else if(a==')'||a=='$') strcpy(prod,""); else ok=0; }
        else if(X=='T') strcpy(prod,"FY");
        else if(X=='Y'){ if(a=='*') strcpy(prod,"*FY"); else if(a=='+'||a==')'||a=='$') strcpy(prod,""); else ok=0; }
        else if(X=='F'){ if(a=='i') strcpy(prod,"i"); else if(a=='(') strcpy(prod,"(E)"); else ok=0; }
        else ok=0;
        if(!ok){ printf("String Rejected\n"); return 0; }
        printf("Expand %c -> %s      Stack: ", X, prod[0]?prod:"e"); popc();
        for(int k=(int)strlen(prod)-1;k>=0;k--) push(prod[k]);
        printf("%s   Input: %s\n", stack, input+ip);
    }
    if(input[ip]=='$' || (ip>0 && input[ip-1]=='$')) printf("String Accepted\n");
    else if(top==0) printf("String Accepted\n"); else printf("String Rejected\n");
    return 0;
}
