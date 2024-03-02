// AUTOGRADER FOR CSCI 4061
// Created by Elias Vera-Jimenez, Sarthak Bansal, Sohan Addagudi
// veraj002, bansa074, addag009

#include "include/utility.h"
#define MAX_STRING_SIZE 55
void evaluate_solution(const char *solution_name, char *parameter[], char retList[][MAX_STRING_SIZE], int retSize) {
    int b = atoi(parameter[1]); // batch size
    int j = 1; // used to go through the parameters in argv[]
    pid_t curr_processes[retSize - 1]; // records processes.
    char *used_parameters[retSize - 1]; // records currently used parameters
    int k = 0; // used to accurately list the parameter used in association with the most recent child process exit.
    int pnum = 0; //keeps track of processes 
    int placeInRetList = 1;//tracks returns
    while(j < retSize){ 
        pid_t pid = fork();
        if (pid == 0) { // Child process
            // Execute solution
            execl(solution_name, solution_name, parameter[j+1], (char*)NULL);
            // If execl fails, print error
            perror("Error executing solution");
            exit(1);            
        } else if (pid >= 0){ // Parent Process
            curr_processes[pnum] = pid;
            used_parameters[k] = parameter[j+1];
            if(j % b == 0 || j+1 == retSize){ // will only be true if either there are b processes
                                            // running or j is about to reach the retSize. 
                int status;
                struct timeval start;
                start_timer(&start);
                char solString[MAX_STRING_SIZE]; // holds the solution string that will be passed to retString
                pid_t exit_pid = pid; // used for debugging, will record the most recent exit.
                // Wait for child process to finish
                 
            while((exit_pid = waitpid(pid<-1, &status, WNOHANG)) >= 0){ //Will continue to wait for ALL current child processes
                if(exit_pid > 0){
                    int c = 0;
                    int old_pnum = pnum;
                    for(int i = 0; i<=old_pnum; i++){
                        if(curr_processes[i] == exit_pid){
                            pnum--;
                            k--;
                            continue;
                        }
                        curr_processes[c] = curr_processes[i];
                        c++;
                        printf("curr_processes[%d] = %ld | used_parameters[%d] = %d\n", c, (long)curr_processes[c],  c, atoi(used_parameters[c]));
                    }
                }

                if(stop_timer(&start) > L){ // Infloop or Stuck (NOT WORKING)
                    printf("HITTING TIMER\n");
                        char filepath[MAX_STRING_SIZE];
                        sprintf(filepath, "/proc/%ld/status", (long)curr_processes[pnum]);
                        FILE *fptr = fopen(filepath, "r");
                        char curr_status[MAX_STRING_SIZE];
                        fgets(curr_status, MAX_STRING_SIZE, fptr);
                        fgets(curr_status, MAX_STRING_SIZE, fptr);
                        fgets(curr_status, MAX_STRING_SIZE, fptr); // attempting to check status of process
                        printf("%s\n", curr_status);
                            if(strcmp(curr_status, "State:  R (Running)") == 0){ // is supposed to match up with running to
                                                                                 // signify an infinite loop
                                printf("%ld is looping, killing...\n", (long)curr_processes[pnum]);
                                sprintf(solString, "%s (infloop)", used_parameters[placeInRetList-1]);
                                kill(curr_processes[pnum], SIGKILL);
                            }else{ // stuck otherwise (often defaulted to, even if infinite).
                                printf("%ld is stuck, killing...\n", (long)curr_processes[pnum]);
                                sprintf(solString, "%s (stuck),", used_parameters[placeInRetList-1]);
                                kill(curr_processes[pnum], SIGKILL);
                            }
                            printf("killed process = %ld\n", (long)curr_processes[pnum]);
                            strcpy(retList[placeInRetList], solString);  
                            placeInRetList++;//increment to next spot in retList
                            fclose(fptr);
                            if(pnum == 0){
                                break;
                            }
                } else if(exit_pid > 0 && WIFSIGNALED(status) && WTERMSIG(status) == 11){ // Error (Segfault) WORKING
                    sprintf(solString, "%s (segfault) ", used_parameters[placeInRetList-1]);
                    strcpy(retList[placeInRetList], solString);
                    placeInRetList++;
                }
                else if(exit_pid > 0 && WIFEXITED(status)){ // Correct, incorrect, slow, segfault 
                    int exit_status = WEXITSTATUS(status); // Check exit status and print evaluation
                    printf("exit status of %ld: %d\n",(long)exit_pid, exit_status);
                            if (stop_timer(&start) > S){
                                sprintf(solString, "%s (slow) ", used_parameters[placeInRetList-1]);
                            } else if (exit_status == 0) {
                                sprintf(solString, "%s (correct) ", used_parameters[placeInRetList-1]);
                            } else {
                                sprintf(solString, "%s (incorrect) ", used_parameters[placeInRetList-1]);
                            }
                            strcpy(retList[placeInRetList],solString); //pushes solution to stringlist.
                            placeInRetList++;
                }
                sleep(1);
            } // end of waitpid() loop
        }
        }//end of parent
        j++;
        pnum++;
        k++;
    }//end of j
}

int main(int argc, char *argv[]) {
    if(argc < 3){ //Program needs at minimum 3 arguments
        printf("Incorrect amount of args, needs B=Cores, and a number of parameters after. need at least 2 arguments\n");
        return -1;
    }
    FILE *ptr = fopen("./submissions.txt", "r"); 
    
    if(ptr == NULL){
        printf("File not Found\n");
        return -1;
    } 

    fseek(ptr, 0, SEEK_END); //finds the end of the file's position
    long int end_point = ftell(ptr); //assigns that position to end_point
    fseek(ptr,0,SEEK_SET); // returns position to the beginnning of the file
    struct timeval superstart;

    start_timer(&superstart);

    while(ftell(ptr) < end_point){
        char subname[MAX_STRING_SIZE];    
        fgets(subname, MAX_STRING_SIZE, ptr); // Grabs next file
                if(subname[strlen(subname) - 1] == '\n')
            subname[strlen(subname)-1] = '\0';
        char retList[argc-1][MAX_STRING_SIZE]; // holds filename and all following parameter return results 
                                               // to be printed.
        char subStr[MAX_STRING_SIZE];
        sprintf(subStr, "%s", subname); // adds file name to retList
        strcpy(retList[0], subStr);

        evaluate_solution(subname, argv, retList, argc-1);

        for(int i = 0; i < argc-1; i++){ //prints all the elements in retList
            printf(" %s ", retList[i]);
        }
        printf("\n");
    }
    printf("Time Elapsed: %f\n", stop_timer(&superstart));
    fclose(ptr);
    return 0;
}
