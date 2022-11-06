CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

A banking application using the switch case and for-loop constructs.
The first input to the program is a positive integer number N, which represents the
number of operations a person wants to perform.
A person can perform one of the following operations on the application:
● WithdrawAmount
● AddAmount
● GetBalance
Based on the entered operation, the program will print the respective operation name, and
perform the operation.


REQUIREMENTS
------------

This program requires the following software:

 * gcc 

   - It is assumed that the system is Unix-like. 
     > However it should work on any system with gcc and on most C compilers.
   - The code was tested on gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11).

COMPILATION
-----------
 
 * Run the following command on the terminal: gcc -o Bank-ES19BTECH11017 Bank-ES19BTECH11017.c

USAGE
-----
 
 * Run the following command on the terminal: ./Bank-ES19BTECH11017

   - It is assumed that the binary file is executable. If not, explicity set it to executable using chmod.

 * Input the data:

   - Enter N (the number of operations you want to perform) when prompted and hit <Enter>.
   - Successively enter the type of operation and the amount (if required) when prompted and hit <Enter>.
   - In case of invalid input:
     > Follow the displayed instructions.

 * The data will be displayed in the following format (after each operation):
   - Type of opertation
   - Result of the operation (on a newline)

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in
