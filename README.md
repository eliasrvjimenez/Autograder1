# CSCI 4061 INTERMEDIATE P1 SUBMISSION #

## Created by Elias Vera-Jimenez (veraj002) , Sarthak Bansal (bansa074) , Sohan Addagudi (addag009) ##

## FINAL WRITEUP BY ELIAS VERA-JIMENEZ ##

This zip should include the following:
* autograder.c
* ./autograder
* Makefile
* README.md (this file)
* template.c
* submissions.txt
* include/utility.h

If missing any, please contact veraj002@umn.edu, or any of the other members of the group.

## TO COMPILE ##

Should be able to compile using the normal makefile command 

```$ make all ```  
to run autograder, use:  
```$ ./autograder <B> <p1> <p2> ... <pn> ```   

All tests were done on KH1-250 and KH1-260 machines.

The autograder can Identify 5/6 types of cases, with the only one missing being infloop, because it cannot discerne between 
stuck and infloop. this also means that we did not get to 3.f, so there is no ctemplate.c file. 

## CONTRIBUTION ##

Sohan Addagudi: The intermediate submission's version of evaluate_solution(), little communication or work done until Friday,
February 16th, where they asked what needed to be finished up. still did not make any meaningful contributions past intermediate deadline.

Sarthak Bansal: A bit of skeleton code on how to format the infloop and stuck cases, as well as slow cases, did not provide working version of any of these case checks, no other work done besides this.

Elias Vera-Jimenez: Set up Github Repository, Created fopen, fgets for submission files in main(), After Intermediate submission: Reformatted evaluate_solution() to better return output values and implemented parallelism for B processes at a time (on average, 3). Fixed and got 5/6 test cases to work, but they do not output in order. at bare minimum, I haven't experience a segfault with them. 

I hate to have to call out my teammates, but there were several times where I contacted them about progress I had made on the project after waiting for them to come through with something to further progress the project, only to receive a thumbs up or a cheer instead of anything actually meaningful. I attempted to help them out and give them pointers where necessary, but never got any sort of result out of that either. At this point I'm calling it quits and turning in what we have, as I don't have the energy to keep working on the project and would rather move on and focus on studying for the midterm. - Elias Vera-Jimenez

## Questions ##
Q1) Explain how you observed the parallelism benefit, and why would performance not improve in the same way for the default solution executable template: Using Parallelism I found that the autograder was able to make it through cases such as slow, stuck, and infiniteloop significantly faster than if we ran through each case one by one, forcing cases that would clear faster to wait until after these cases were done. 






