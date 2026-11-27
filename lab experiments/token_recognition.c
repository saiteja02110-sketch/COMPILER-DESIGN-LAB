#include <stdio.h>
#include <string.h>
#include <ctype.h>
int isKeyword(const char *s){ const char *kw[]={"int","float","char","if","else","while","for","return","void",0}; for(int i=0;kw[i];i++) if(strcmp(s,kw[i])==0) return 1; return 0; }
int main(void){
    char line[512]; if(!fgets(line,sizeof line,stdin)){ return 1; }
    int i=0;
    printf("Tokens:\n");
    while(line[i]){
        if(isspace((unsigned char)line[i])){ i++; continue; }
        if(isalpha((unsigned char)line[i])||line[i]=='_'){ char buf[64]; int j=0; while(isalnum((unsigned char)line[i])||line[i]=='_') buf[j++]=line[i++]; buf[j]='\0';
            printf("%s : %s\n", buf, isKeyword(buf)?"Keyword":"Identifier"); continue; }
        if(isdigit((unsigned char)line[i])){ char buf[64]; int j=0; while(isdigit((unsigned char)line[i])) buf[j++]=line[i++]; buf[j]='\0'; printf("%s : Number\n", buf); continue; }
        if(strchr("+-*/=",line[i])){ printf("%c : Operator\n", line[i]); i++; continue; }
        printf("%c : Symbol\n", line[i]); i++;
    }
    return 0;
}
