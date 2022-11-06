CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

A multi-process C program involving IPC to find the time needed to execute an instruction 
from the command line. The program makes use of the fork(), execvp() and gettimeofday() 
functions to achieve its goals.

REQUIREMENTS
------------

This program requires the following software:

 * gcc 

   - It is assumed that the system is Unix-like. 
     > However it should work on any system with gcc and on most C compilers.
   - The code was tested on gcc (Ubuntu 5.4.0-6ubuntu1~16.04.12).

COMPILATION
-----------
 
 * Run the following command on the terminal: gcc -o Asgn1-ES19BTECH11017 Asgn1-ES19BTECH11017.c -lrt

USAGE
-----
 
 * Run the following command on the terminal: ./Asgn1-ES19BTECH11017 <command>
   
   - For example: ./Asgn1-ES19BTECH11017 ls

   - It is assumed that the binary file is executable. If not, explicity set it to executable using chmod.

 * The output will be displayed in the following format:
   - Output of the given command
   - Elapsed time

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in