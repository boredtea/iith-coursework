CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

Program that uses one-dimensional integer arrays to read
in two sets of numbers, each having 10 integer numbers. Input array must not have  any 
duplicate elements.
Then following functions are developed:
1) Union of sets
2) Intersection of sets
3) Computation: First and second largest element in both union and intersection set.


REQUIREMENTS
------------

This program requires the following software:

 * gcc 

   - It is assumed that the system is Unix-like. 
     > However it should work on any system with gcc and on most C compilers.
   - The code was tested on gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11).

COMPILATION
-----------
 
 * Run the following command on the terminal: gcc -o Array-ES19BTECH11017 Array-ES19BTECH11017.c

USAGE
-----
 
 * Run the following command on the terminal: ./Array-ES19BTECH11017

   - It is assumed that the binary file is executable. If not, explicity set it to executable using chmod.

 * Input the data:

   - Enter the first array and hit <Enter>.
   - Enter the second array and hit <Enter>.
     > in case of duplicate elements, follow instructions displayed

 * The data will be displayed in the following format:
   - Union of the sets
   - The first and the second largest elements of the union set 
   - Intersection of the sets
   - The first and the second largest elements of the intersection set

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in
