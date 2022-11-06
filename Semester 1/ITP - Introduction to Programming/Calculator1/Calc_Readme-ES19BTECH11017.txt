CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

A simple calculator application that takes three inputs: first input as operation
name (i.e., +, -, *, /), second and third input as two numbers (i.e., number_1 and
number_2). Then application calculates and displays the operation and result based on
the selected operation.


REQUIREMENTS
------------

This program requires the following software:

 * gcc 

   - It is assumed that the system is Unix-like. 
     > However it should work on any system with gcc and on most C compilers.
   - The code was tested on gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11).

COMPILATION
-----------
 
 * Run the following command on the terminal: gcc -o Calc-ES19BTECH11017 Calc-ES19BTECH11017.c

USAGE
-----
 
 * Run the following command on the terminal: ./Calc-ES19BTECH11017

   - It is assumed that the binary file is executable. If not, explicity set it to executable using chmod.

 * Input the data:

   - Enter operator (i.e., +, -, *, /) (stored as char datatype) when prompted and hit <Enter>.
   - Enter the first number (of int datatype) and hit <Enter>.
   - Enter the second number (of int datatype) and hit <Enter>.
   - In case of invalid input:
     > Follow the displayed instructions.

 * The data will be displayed in the following format:
   - Type of opertation
   - Result of the operation (of either int or double datatype) (on a newline)

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in
