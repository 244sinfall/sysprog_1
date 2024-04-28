#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <libgen.h>

int main(int argc, char **argv) {

    if(argc < 2){
        printf("Передайте даты в формате ДД.ММ.ГГГГ (1 и более)\n");
        return 1;
    }

    char pathParent[1024];
    ssize_t len = readlink("/proc/self/exe", pathParent, sizeof(pathParent) - 1);
    if (len != -1) {
        pathParent[len] = '\0';
    } else {
        perror("readlink");
        return EXIT_FAILURE;
    }
    char * pathChild = dirname(pathParent);
    strcat(pathChild, "/child");

    pid_t pids[argc-1];
    for(int i = 0; i < argc-1; i++){
        int pipefd[2];
        if(pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        pid_t pid = fork();
        if(pid == -1){
            perror("fork");
            exit(EXIT_FAILURE);
        } else if(pid == 0){
            close(pipefd[0]); // Close unused read end of the pipe
            dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the pipe
            close(pipefd[1]); // Close the write end of the pipe
            execl(pathChild, pathChild, argv[i+1], NULL);
            perror("execl"); // In case execl fails
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            close(pipefd[1]);
            pids[i] = pid;
            char buffer[1024];
            ssize_t nbytes;
            while ((nbytes = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
                write(STDOUT_FILENO, buffer, nbytes);
            }
            close(pipefd[0]);
        }
    }

    // Wait for all child processes to finish
    for(int i = 0; i < argc-1; i++) {
        int status;
        waitpid(pids[i], &status, 0);
    }

    return EXIT_SUCCESS;
}
