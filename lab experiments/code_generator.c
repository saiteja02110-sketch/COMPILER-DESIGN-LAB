#include <stdio.h>
#include <string.h>
int main(void){
    char line[128];
    printf("Target Code:\n");
    while(fgets(line,sizeof line,stdin)){
        line[strcspn(line,"\n")]='\0'; if(line[0]=='\0') continue;
        char lhs[32], a1[32], a2[32], op; int matched;
        matched = sscanf(line, "%31s = %31s %c %31s", lhs, a1, &op, a2);
        if(matched==4){
            const char *mn = (op=='+')?"ADD":(op=='-')?"SUB":(op=='*')?"MUL":"DIV";
            printf("MOV %s, R0\n", a1);
            printf("%s %s, R0\n", mn, a2);
            printf("MOV R0, %s\n", lhs);
        } else if(sscanf(line, "%31s = %31s", lhs, a1)==2){
            printf("MOV %s, R0\n", a1);
            printf("MOV R0, %s\n", lhs);
        }
    }
    return 0;
}
