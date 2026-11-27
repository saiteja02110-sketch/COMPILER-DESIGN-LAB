#include <stdio.h>
#include <string.h>
char str[256]; int pos=0; int error=0;
int peekIsId(void){ return str[pos]=='i' && str[pos+1]=='d'; }
void E(void); void T(void); void F(void);
void Ed(void){ if(str[pos]=='+'){ pos++; T(); Ed(); } }
void Td(void){ if(str[pos]=='*'){ pos++; F(); Td(); } }
void F(void){ if(peekIsId()){ pos+=2; } else if(str[pos]=='('){ pos++; E(); if(str[pos]==')') pos++; else error=1; } else error=1; }
void T(void){ F(); Td(); }
void E(void){ T(); Ed(); }
int main(void){
    if(scanf("%255s",str)!=1) return 1;
    E();
    if(!error && str[pos]=='\0') printf("String Accepted\n");
    else printf("String Rejected\n");
    return 0;
}
