#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(void){
    char line[256]; if(!fgets(line,sizeof line,stdin)) return 1;
    char type[32]; if(sscanf(line,"%31s",type)!=1) return 1;
    printf("Symbol Table (type inherited by L-attribute):\n");
    printf("Name  Type\n");
    char *p=strchr(line,' '); if(!p) return 0; p++;
    char name[32]; int j=0;
    for(int i=0;;i++){ char ch=p[i];
        if(isalnum((unsigned char)ch)||ch=='_'){ name[j++]=ch; }
        else { if(j>0){ name[j]='\0'; printf("%s     %s\n", name, type); j=0; } if(ch==';'||ch=='\0'||ch=='\n') break; } }
    printf("Note: type '%s' is inherited from left to right across the identifier list.\n", type);
    return 0;
}
