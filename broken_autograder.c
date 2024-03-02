// AUTOGRADER FOR CSCI 4061
// Created by Elias Vera-Jimenez, Sarthak Bansal, Sohan Addagudi
// veraj002, bansa074, addag009

#include "include/utility.h"
#define MAX_STRING_SIZE 50

void evaluate_solution(const char *solution_name, char *parameter[], char retList[][MAX_STRING_SIZE], int retSize) {
    
    int b = atoi(parameter[1]);
    for(int j = 2; j < retSize; j++){
        pid_t pid = fork();
        if (pid == 0) { // Child process
            // Execute solution
            execl(solution_name, solution_name, parameter[j], (char*)NULL);
            // If execl fails, print error
            perror("Error executing solution");
            exit(1);
        } else if (pid > 0) { // Parent process 
            int status;
            // Wait for child process to finish
            waitpid(pid, &status, 0);
            if(WIFEXITED(status)){
                int exit_status = WEXITSTATUS(status);
            // Check exit status and print evaluation
                char solString[MAX_STRING_SIZE];
                if (exit_status == 0) {
                     sprintf(solString, " %s (correct), ", parameter[j]);
                } else {
                    sprintf(solString, " %s (incorrect), ", parameter[j]);
                }
                strcpy(retList[j-1],solString); 
            }
            } else { // Fork failed
            perror("Fork failed");
            exit(1);
        }
        if(j-2 % b){
            usleep(300);
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc < 3){ //Program needs at minimum 3 arguments
        printf("Incorrect amount of args, needs B=Cores, and a number of parameters after. need at least 2 arguments\n");
        return -1;
    }
    FILE *ptr = fopen("./test_submissions.txt", "r"); //will always open this file, as denoted by project1 pdf
    
    if(ptr == NULL){
        printf("File not Found\n");
        return -1;
    } 

    fseek(ptr, 0, SEEK_END); //finds the end of the file's position
    long int end_point = ftell(ptr); //assigns that position to end_point
    fseek(ptr,0,SEEK_SET); // returns position to the beginnning of the file
               
    while(ftell(ptr) < end_point){
        char subname[MAX_STRING_SIZE];    
        fgets(subname, MAX_STRING_SIZE, ptr);
        if(subname[strlen(subname) - 1] == '\n')
            subname[strlen(subname)-1] = '\0';

        char retList[argc][MAX_STRING_SIZE];
        sprintf(retList[0], subname, ": ");
        evaluate_solution(subname, argv, retList, argc);

        for(int i = 0; i < argc; i++){
            printf(" %s ", retList[i]);
        }
        printf("\n");
    }
    fclose(ptr);
    return 0;
}
