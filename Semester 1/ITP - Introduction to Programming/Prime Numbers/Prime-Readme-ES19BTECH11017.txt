CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

A C program that prints the sum of prime digits of a positive number using recursion.
The number is taken as input from the user.
The number given as input must have exactly 10 digits. 
The program achieves its goal using two functions that use only recursion.


REQUIREMENTS
------------

This program requires the following software:

 * gcc 

   - It is assumed that the system is Unix-like. 
     > However it should work on any system with gcc and on most C compilers.
   - The code was tested on gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11).

COMPILATION
-----------
 
 * Run the following command on the terminal: gcc -o Prime-ES19BTECH11017 Prime-ES19BTECH11017.c

USAGE
-----
 
 * Run the following command on the terminal: ./Prime-ES19BTECH11017

   - It is assumed that the binary file is executable. If not, explicity set it to executable using chmod.

 * Input the data:

   - Enter a 10 - digit positive number when prompted and hit <Enter>.
   - In case of invalid input:
     > Follow the displayed instructions.

 * The data will be displayed in the following format:
   - Sum of all the primes in the number (on a newline)
   - Repeats as long as the input is invalid

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in
