CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

This is a multithreaded program that calculates various statistical values for a list of numbers. 
A series of numbers is passed to the program and it then creates three separate threads. 
One thread will determine the average of the numbers, the second will determine the minimum 
value and the third will determine the maximum value.

For analytical purposes, the submission also includes another source code file to calculate the time
taken by the code while executing.

REQUIREMENTS
------------

This program requires the following software:

 * gcc 

   - It is assumed that the system is Unix-like. 
     > However it should work on any system with gcc and on most C compilers.
   - The code was tested on gcc (Ubuntu 5.4.0-6ubuntu1~16.04.12).

COMPILATION
-----------
 
 * Run the following command on the terminal: gcc -o Asgn2-ES19BTECH11017 Asgn2-ES19BTECH11017.c -lpthread

 * To run the analytical file, use the following command: gcc -o Asgn2-Analysis-ES19BTECH11017 Asgn2-Analysis-ES19BTECH11017.c -lpthread

USAGE
-----
 
 * Run the following command on the terminal: ./Asgn2-ES19BTECH11017

   - It is assumed that the binary file is executable. If not, explicity set it to executable using chmod.

 * The output will be stored in a text file labelled Asgn2-out-ES19BTECH11017.txt

 For the analytical file:

 * Run the following command on the terminal: ./Asgn2-Analysis-ES19BTECH11017

 * The output of this file will be displayed as follows:
   - Elapased time for case <case number>: <time taken in milli seconds>


AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in