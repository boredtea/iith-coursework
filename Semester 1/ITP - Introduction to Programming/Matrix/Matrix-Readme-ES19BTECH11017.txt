CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

This program calculates the product of two matrices
and the inverse of the product matrix.


REQUIREMENTS
------------

This program requires the following software:

 * gcc 

   - It is assumed that the system is Unix-like. 
     > However it should work on any system with gcc and on most C compilers.
   - The code was tested on gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11).

COMPILATION
-----------
 
 * Run the following command on the terminal: gcc -o Matrix-ES19BTECH11017 Matrix-ES19BTECH11017.c

USAGE
-----
 
 * Run the following command on the terminal: ./Matrix-ES19BTECH11017

   - It is assumed that the binary file is executable. If not, explicity set it to executable using chmod.

 * Input the data:

   - Enter order of the first array when prompted and hit <Enter>. 
   - Enter order of the second array when prompted and hit <Enter>. 
     > NOTE: enter number of rows first and then number of columns
     > in case of invalid input, enter again
   - Enter elements for the first array row-wise.
   - Enter elements for the second array row-wise.

 * The data will be displayed in the following format:
   - Multiplication matrix of the first matrix with the second
     > displayed in a matrix format
   - Inverse of the multiplication matrix
     > if inverse doesn't exist, a message saying so is displayed

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in
