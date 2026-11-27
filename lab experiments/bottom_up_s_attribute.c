#include <stdio.h>
#include <string.h>
#include <ctype.h>
char str[128]; int pos=0;
double E(void);
double F(void){ double v=0; while(isdigit((unsigned char)str[pos])){ v=v*10+(str[pos]-'0'); pos++; } printf("Reduce number -> E, value = %.0f\n", v); return v; }
double T(void){ double v=F(); while(str[pos]=='*'){ pos++; double r=F(); printf("Reduce %.0f * %.0f -> T, value = %.0f\n", v, r, v*r); v=v*r; } return v; }
double E(void){ double v=T(); while(str[pos]=='+'){ pos++; double r=T(); printf("Reduce %.0f + %.0f -> E, value = %.0f\n", v, r, v+r); v=v+r; } return v; }
int main(void){
    if(scanf("%127s",str)!=1) return 1;
    printf("Bottom-Up Evaluation (S-Attributed):\n");
    double v=E();
    printf("Final Value = %.0f\n", v);
    return 0;
}
