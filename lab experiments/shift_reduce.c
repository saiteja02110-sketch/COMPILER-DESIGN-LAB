#include <stdio.h>
#include <string.h>
char stack[256]; int top=0; char input[256]; int ip=0;
void push(char c){ stack[top++]=c; stack[top]='\0'; }
int tryReduce(void){
    if(top>=1 && stack[top-1]=='d'){ /* placeholder never */ }
    /* id is handled at shift time: we shift 'i','d' then reduce to E */
    if(top>=2 && stack[top-2]=='i' && stack[top-1]=='d'){ top-=2; push('E'); printf("Reduce id -> E      Stack: %s   Input: %s\n", stack, input+ip); return 1; }
    if(top>=3 && stack[top-3]=='E' && (stack[top-2]=='+'||stack[top-2]=='*') && stack[top-1]=='E'){ char op=stack[top-2]; if(op=='+' && input[ip]=='*') return 0; /* * binds tighter: shift first */ top-=3; push('E'); printf("Reduce E %c E -> E   Stack: %s   Input: %s\n", op, stack, input+ip); return 1; }
    if(top>=3 && stack[top-3]=='(' && stack[top-2]=='E' && stack[top-1]==')'){ top-=3; push('E'); printf("Reduce ( E ) -> E   Stack: %s   Input: %s\n", stack, input+ip); return 1; }
    return 0;
}
int main(void){
    if(scanf("%255s",input)!=1) return 1;
    strcat(input,"$");
    printf("Shift Reduce Parsing:\n");
    while(1){
        while(tryReduce());
        char c=input[ip];
        if(c=='$'){ break; }
        if(c=='i' && input[ip+1]=='d'){ push('i'); push('d'); ip+=2; printf("Shift id            Stack: %s   Input: %s\n", stack, input+ip); continue; }
        if(c=='+'||c=='*'||c=='('||c==')'){ push(c); ip++; printf("Shift %c             Stack: %s   Input: %s\n", c, stack, input+ip); continue; }
        printf("String Rejected\n"); return 0;
    }
    while(tryReduce());
    if(top==1 && stack[0]=='E') printf("String Accepted\n"); else printf("String Rejected\n");
    return 0;
}
