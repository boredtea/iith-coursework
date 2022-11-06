CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

This program parallelises the brute force approach to solve the travelling salesman problem. Given a starting point, the number of threads and a list of destinations points, this program finds the closes point by finding the distances to all the endpoints and then chooses the minimum distance. However, the program makes use of threads to do so by splitting up all the destination points over multiple threads to speed up the process.


REQUIREMENTS
------------

This program requires the following softwares/files:

 * gcc 
   - It is assumed that the system is Unix-like. 
     > However it should work on any system with gcc and on most C compilers.
   - The code was tested on gcc (10.3.0).
 * input file
   The program reads from an input file named 'input.txt' and requires it to contain the following data, each on a separate line:
   - Number of threads
   - The source coordinates in this format: (x, y)
   - The number of destination coordinates
   - The list of destination coordinates in the following format: (x1, y1) (x2, y) (x3, y3) ...
   
   Please note that the coordinates are expected to be integers. Moreover, a sample input file titled 'input.txt' has been included in the submission zip file.

COMPILATION
-----------
 
 * Run the following command on the terminal: gcc -o sourceCode Assgn1Src-ES19BTECH11017.c -lm -pthread

USAGE
-----
 
 * Run the following command on the terminal: ./sourceCode

   - It is assumed that the binary file is executable. If not, explicity set it to executable using chmod.

 * The output will be displayed in the following format:
   - Elapsed time in microseconds
   - The coordinates of the point closest to the source coordinates.

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in