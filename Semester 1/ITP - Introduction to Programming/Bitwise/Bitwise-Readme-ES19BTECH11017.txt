CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

Hamming distance for a pair of numbers is defined as the number of corresponding bit positions
where the two numbers are different in their equivalent binary representation.
The program accepts two numbers and calculates the hamming distance between them.


REQUIREMENTS
------------

This program requires the following software:

 * gcc 

   - It is assumed that the system is Unix-like. 
     > However it should work on any system with gcc and on most C compilers.
   - The code was tested on gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11).

COMPILATION
-----------
 
 * Run the following command on the terminal: gcc -o Bitwise-ES19BTECH11017 Bitwise-ES19BTECH11017.c

USAGE
-----
 
 * Run the following command on the terminal: ./Bitwise-ES19BTECH11017

   - It is assumed that the binary file is executable. If not, explicity set it to executable using chmod.

 * Input the data:

   - Enter two numbers separated by a space when prompted and hit <Enter>.
   - Enter either 1 or 2 depending on whether you would like to continue and hit <Enter>.
   - Repeat above steps until you chose to exit
   - In case of invalid input:
     > Follow the displayed instructions.

 * The data will be displayed in the following format:
   - The Hamming distance between the two entered numbers
   - A menu asking whether you'd like to enter numbers again
   - Repeats as long as the exit option isn't selected
     > Error message in case of invalid inputs

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in
