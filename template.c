#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


#define S 10   // Define timeout for slow

void infinite_loop() {
    while(1){};    // Simulating a infinite loop
}

void slow_process() {
    sleep(S);  // Simulating a slow process
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <mode>\n", argv[0]);
        return 1;
    }

    unsigned int seed = 0;

    for (int i = 0; argv[0][i] != '\0'; i++) {
        seed += (unsigned char)argv[0][i]; 
    }
    
    unsigned int pi = atoi(argv[1]);    
    seed += pi;
    srandom(seed);
  
    int mode = random() % 6 + 1;
    pid_t pid = getpid(); // Get the current process ID

    sleep(1); 

    switch (mode) {
        case 1:
            printf("Program: %s, PID: %d, Mode: 1 - Exiting with status 0 (Correct answer)\n", argv[0], pid);
            return 0;  // Exit with status 0 (correct answer)
        case 2:
            printf("Program: %s, PID: %d, Mode: 2 - Exiting with status 1 (Incorrect answer)\n", argv[0], pid);
            return 1;  // Exit with status 1 (incorrect answer)
        case 3:
            printf("Program: %s, PID: %d, Mode: 3 - Triggering a segmentation fault\n", argv[0], pid);
            raise(SIGSEGV);  // Trigger a segmentation fault
            break;
        case 4:
            printf("Program: %s, PID: %d, Mode: 4 - Entering an infinite loop\n", argv[0], pid);
            infinite_loop();
            break;
        case 5:
            printf("Program: %s, PID: %d, Mode: 5 - Simulating being stuck/blocked\n", argv[0], pid);
            getchar(); // Simulate being stuck/blocked
            break;
        case 6:
            printf("Program: %s, PID: %d, Mode: 6 - Simulating a slow process\n", argv[0], pid);
            slow_process();
            break;
        default:
            break;
    }

    return 0;
}
