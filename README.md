# CSCI 4061 AUTOGRADER FEB 2024 #

## Created by Elias Vera-Jimenez ## 
## With Assistance From: Sarthak Bansal, Sohan Addagudi ##


An uncompleted but fairly close to final version of an Autograder project I worked on with minor help from some teammates. it was originally on my school's enterprise github, but I wanted to display it here since I poured at least 20 hours into the project.

As of March 1st, 2024, We are working on an Enhanced version of this project, so hopefully I will learn how to correct the issues with this version and have it fully working as intended.

The concept was not too complex: Make an autograder program that receives a list of executable "Student Submissions" and runs them to see if the give the correct output. The program is supposed to handle 6 cases:

* The submission returns a 0, meaning that it ran properly and was ***Correct***
* The submission returns a 1, meaning that it ran properly but was ***Incorrect***
* The submission returns a 0 but takes longer than S time (declared in the include/utility,h file), meaning that it was ***Slow***
* The submission segfaults, giving the result ***segfault***

These 4 reasons work properly in the program, the 2 that are handled properly but are not distinguished by the program are:


* The submission runs infinitely, or greater than L time (declared in include/utility.h) and is killed and gives the result ***Infloop***
* The submission gets stuck waiting for user input, and is killed and gives the result ***Stuck***

The program only checks for these two if there is no return from the child process after L time. I tried reading the status file of these processes, but was unable to propery compare the statuses *Running* vs *Stopped*.

another thing the program does not do that it is supposed to is return with the correctly passed parameter.

For example, if I ran the program and gave it three integers `1 2 3`, if it is slow for 1, is correct for 2, and segfaults for 3, it should spit out:

```zsh
sol_x : 1 (slow) 2 (correct) 3 (segfault)
```

Since I was not able to get the program to properly line up the parameter with it's result, it would most likely spit out in the order that it complete, such as:

```zsh
sol_x : 1 (correct) 2 (segfault) 3 (slow)
```

since the correct result would likely appear before the other two, and slow would return last. 


### TO COMPILE ###

Ideally, Use `make` to compile the code, this can be done using:

```zsh
> make all
```

which should compile not only the autograder, but all of it's test files too.

### TO RUN ###

Run the program using:

```zsh
> ./autograder B p1 p2 ... pn
```

Where B is the batch size, or how many processes you want running at once (check core count for this one) and p1 ... pn being each parameter, which should be an integer.

For example:
```zsh
> ./autograder 4 1 2 3 4 5 6
```

Should take 4 as it's batch size, only running 4 at a time, and the rest of the integers as parameters to be passed to the submitted executable.




