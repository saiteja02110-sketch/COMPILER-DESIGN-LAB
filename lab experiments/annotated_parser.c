#include <stdio.h>
#include <string.h>
#include <ctype.h>
char str[128]; int pos=0;
double E(void);
double F(void){ double v=0; if(str[pos]=='('){ pos++; v=E(); pos++; printf("F -> ( E )  : F.val = %.0f\n", v); return v; }
    while(isdigit((unsigned char)str[pos])){ v=v*10+(str[pos]-'0'); pos++; } printf("F -> number : F.val = %.0f\n", v); return v; }
double T(void){ double v=F(); while(str[pos]=='*'){ pos++; double r=F(); printf("T -> T * F  : T.val = %.0f * %.0f = %.0f\n", v, r, v*r); v=v*r; } return v; }
double E(void){ double v=T(); while(str[pos]=='+'){ pos++; double r=T(); printf("E -> E + T  : E.val = %.0f + %.0f = %.0f\n", v, r, v+r); v=v+r; } return v; }
int main(void){
    if(scanf("%127s",str)!=1) return 1;
    double v=E();
    printf("Annotated Parse Tree (synthesized attribute):\n");
    printf("E.val = %.0f\n", v);
    printf("Final Value = %.0f\n", v);
    return 0;
}
