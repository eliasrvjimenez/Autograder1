#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define L 5


void infinite_loop() {
    while (1) {
        // Infinite loop
    }
}

void slow_process() {
    sleep(5 * L);  // Sleep for 10 seconds, simulating a slow process
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
  
    int mode = 3;

    printf("mode is: %d\n", mode); 
    switch (mode) {
        case 1:
            return 0;  // Exit with status 0 (correct answer)
        case 2:
            return 1;  // Exit with status 1 (incorrect answer)
        case 3:
            raise(SIGSEGV);  // Trigger a segmentation fault
            break;
        case 4:
            infinite_loop();
            break;
        case 5:
            getchar(); // Simulate being stuck/blocked
            break;
        case 6:
            slow_process();
            break;
        default:
            break;
    }

    return 0;
}
