
/* parser for a=b+c*d style: single-char operands, + - * / , precedence * / > + - */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
char expr[128]; int pos=0; int tcount=0;
typedef struct { char op; char a1[32]; char a2[32]; char res[32]; } Quad;
Quad quads[64]; int nq=0;
void newTemp(char *out){ sprintf(out,"t%d",++tcount); }
void parseExpr(char *out);
void parseFactor(char *out){
    if(expr[pos]=='('){ pos++; parseExpr(out); pos++; /* ')' */ }
    else { char buf[2]={expr[pos],'\0'}; strcpy(out,buf); pos++; }
}
void parseTerm(char *out){
    parseFactor(out);
    while(expr[pos]=='*'||expr[pos]=='/'){ char op=expr[pos++]; char r[32], t[32]; parseFactor(r); newTemp(t);
        quads[nq].op=op; strcpy(quads[nq].a1,out); strcpy(quads[nq].a2,r); strcpy(quads[nq].res,t); nq++; strcpy(out,t); }
}
void parseExpr(char *out){
    parseTerm(out);
    while(expr[pos]=='+'||expr[pos]=='-'){ char op=expr[pos++]; char r[32], t[32]; parseTerm(r); newTemp(t);
        quads[nq].op=op; strcpy(quads[nq].a1,out); strcpy(quads[nq].a2,r); strcpy(quads[nq].res,t); nq++; strcpy(out,t); }
}
int build(void){ /* returns 1 on success; fills quads incl final assignment */
    char line[128]; if(!fgets(line,sizeof line,stdin)) return 0;
    line[strcspn(line,"\n")]='\0';
    char *eq=strchr(line,'='); if(!eq) return 0;
    char lhs[32]; int ll=(int)(eq-line); strncpy(lhs,line,ll); lhs[ll]='\0';
    strcpy(expr,eq+1); pos=0; char result[32]; parseExpr(result);
    quads[nq].op='='; strcpy(quads[nq].a1,result); strcpy(quads[nq].a2,"-"); strcpy(quads[nq].res,lhs); nq++;
    return 1;
}

int main(void){
    if(!build()){ printf("Invalid expression\n"); return 1; }
    printf("Triple:\n");
    printf("Index  Op  Arg1  Arg2\n");
    for(int i=0;i<nq;i++){
        char a1[32],a2[32]; strcpy(a1,quads[i].a1); strcpy(a2,quads[i].a2);
        for(int j=0;j<i;j++){ if(strcmp(a1,quads[j].res)==0){ sprintf(a1,"(%d)",j); } if(strcmp(a2,quads[j].res)==0){ sprintf(a2,"(%d)",j); } }
        if(quads[i].op=='=') printf("%d      =   %s     -\n", i, a1);
        else printf("%d      %c   %s     %s\n", i, quads[i].op, a1, a2);
    }
    return 0;
}
