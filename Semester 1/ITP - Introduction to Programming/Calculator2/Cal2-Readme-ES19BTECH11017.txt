CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

A calculator application that is capable ofperforming the following operations:
- Add
- Subtract
- Multiply
- Divide (output the floor of the result)
- Modulus (remainder on division)
- Square
- Square root (output the floor of the result)
- Log (base 2) (output the ceil of the result)
The program makes use of ONLY + and - (add and subtract operations) to implement all of the above
operations. ‘*’ (multiply), ‘/’ (divide), ‘%’ (modulo) and any function from “math.h” has not 
been used. Only loops, '+', and '-' have been used to implement all the above functions.

Separate functions have been created for each of the above operations.


REQUIREMENTS
------------

This program requires the following software:

 * gcc 

   - It is assumed that the system is Unix-like. 
     > However it should work on any system with gcc and on most C compilers.
   - The code was tested on gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11).

COMPILATION
-----------
 
 * Run the following command on the terminal: gcc -o Cal2-ES19BTECH11017 Cal2-ES19BTECH11017.c

USAGE
-----
 
 * Run the following command on the terminal: ./Cal2-ES19BTECH11017

   - It is assumed that the binary file is executable. If not, explicity set it to executable using chmod.

 * Input the data:

   - Enter a number from the displayed menu corresponding to the operation that is to be performed and hit <Enter>.
   - Enter the required number of inputs when prompted and hit <Enter>.
   - Repeat above steps when the menu is displayed again.
   - In case of invalid input:
     > Follow the displayed instructions.

 * The data will be displayed in the following format:
   - Menu of operations
   - Result of the operation
   - Repeats as long as the exit option isn't selected
     > Error message in case of invalid inputs

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in
