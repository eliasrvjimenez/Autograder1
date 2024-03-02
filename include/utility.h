#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h> // For PATH_MAX


#define L 20  // Define timeout for stuck or infinite
#define S 5   // Define timeout for slow


// Define an enum for the program execution outcomes
enum {
    CORRECT = 1,     // Corresponds to case 1: Exit with status 0 (correct answer)
    INCORRECT,       // Corresponds to case 2: Exit with status 1 (incorrect answer)
    SEGFAULT,        // Corresponds to case 3: Triggering a segmentation fault
    INFLOOP,         // Corresponds to case 4: Entering an infinite loop
    STUCK_BLOCK,     // Corresponds to case 5: Simulating being stuck/blocked
    SLOW             // Corresponds to case 6: Simulating a slow process
};


// Function to get status message
const char* get_status_message(int status) {
    switch (status) {
        case CORRECT: return "correct";
        case INCORRECT: return "incorrect";
        case SLOW: return "slow";
        case SEGFAULT: return "segfault";
        case STUCK_BLOCK: return "stuck or block";
        case INFLOOP: return "infloop";
        default: return "unknown";
    }
}


/**
 * Writes the full paths of all files within a specified directory to a given output file.
 * This function opens the specified directory, iterates over each entry excluding special
 * entries "." and "..", constructs the full path for each file, and writes these paths to
 * the specified output file.
 * @param directoryPath The path to the directory whose file paths are to be written.
 * @param outputFileName The path to the file where the full paths will be saved.
 * @Hint: This function can create submissions.txt if you wish to use it
 */

void write_filepath_to_submissions(const char *directoryPath, const char *outputFileName) {
    DIR *dir;
    struct dirent *entry;
    FILE *file;

    // Open the directory
    dir = opendir(directoryPath);
    if (!dir) {
        perror("Failed to open directory");
        exit(EXIT_FAILURE);
    }

    // Open or create the output file
    file = fopen(outputFileName, "w");
    if (!file) {
        perror("Failed to open output file");
        closedir(dir);
        exit(EXIT_FAILURE);
    }

    char fullPath[PATH_MAX];
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path
        snprintf(fullPath, sizeof(fullPath), "%s/%s", directoryPath, entry->d_name);

        // Write the full path to the file
        fprintf(file, "%s\n", fullPath);
    }

    fclose(file);
    closedir(dir);
}

/* The inline keyword is used to suggest that the compiler embeds the function's code directly 
at each point of call, potentially reducing function call overhead and improving execution speed. 
Note: timer returns second */

static inline void start_timer(struct timeval *start) {
    gettimeofday(start, NULL);
}

static inline double stop_timer(struct timeval *start) {
    struct timeval end;
    gettimeofday(&end, NULL);
    double seconds = (double)(end.tv_sec - start->tv_sec);
    double useconds = (double)(end.tv_usec - start->tv_usec) / 1000000.0;
    return seconds + useconds;
}

#endif // UTILITY_H
