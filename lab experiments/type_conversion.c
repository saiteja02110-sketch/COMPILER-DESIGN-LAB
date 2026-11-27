#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(void){
    char line[128]; if(!fgets(line,sizeof line,stdin)) return 1;
    /* find operator + - * / between two numeric literals */
    double v1=0,v2=0; int isF1=0,isF2=0; char op=0;
    char *p=line;
    /* parse first number */
    char buf[64]; int j=0; while(isdigit((unsigned char)*p)||*p=='.'){ if(*p=='.') isF1=1; buf[j++]=*p++; } buf[j]='\0'; sscanf(buf,"%lf",&v1);
    while(*p==' ') p++;
    op=*p++;
    while(*p==' ') p++;
    j=0; while(isdigit((unsigned char)*p)||*p=='.'){ if(*p=='.') isF2=1; buf[j++]=*p++; } buf[j]='\0'; sscanf(buf,"%lf",&v2);
    printf("Operand 1: %.2f (%s)\n", v1, isF1?"float":"int");
    printf("Operand 2: %.2f (%s)\n", v2, isF2?"float":"int");
    double res=0; if(op=='+') res=v1+v2; else if(op=='-') res=v1-v2; else if(op=='*') res=v1*v2; else if(op=='/') res=(v2!=0)?v1/v2:0;
    if(isF1||isF2){ printf("Type Conversion: int operand widened to float (implicit conversion)\n"); printf("Result Type: float\n"); printf("Result Value: %.2f\n", res); }
    else { printf("Type Conversion: none needed\n"); printf("Result Type: int\n"); printf("Result Value: %d\n", (int)res); }
    return 0;
}
