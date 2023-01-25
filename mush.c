#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    while(0==0) {

        char input[2048];
        char *words[128];
        char *word;

        printf("$ "); 
        fgets(input, 2048, stdin);
        int len = strlen(input);
        input[len-1] = '\0';

        word = strtok(input, " ");
        words[0] = word;
        int i = 1;
        while (word != NULL) {
            word = strtok(NULL, " ");
            words[i] = word;
            i++;
        }
        words[i] = NULL;

        if(strcmp(words[0], "exit") == 0) {
            exit(0);
        }else if(strcmp(words[0], "cd") == 0) {
            int cderr = chdir(words[1]);
            if (cderr == -1) {
                perror("Cd error ");
            }
        }else {
            int pid = fork();
            if (pid == 0) {
                execvp(words[0],words);
                perror("Error ");
            }
            wait(NULL);
        }

    }
}