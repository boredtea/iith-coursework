CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

A BMI calculator application that takes the user’s weight in kilograms and height in
meters as input, then calculates and displays the user’s body mass index, according to the
formula:

BMI = Weight/(Height × Height)

Weight and height are taken as inputs from the user and stored as doubles. 
It is assumed that the inputs are numbers greater than 0.

The BMI is also calculated as a double and printed out.

We also print wheter the user is underweight, normal, overweight or obese.

REQUIREMENTS
------------

This program requires the following software:

 * gcc 

   - It is assumed that the system is Unix-like. 
   - The code was tested on gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11).

COMPILATION
-----------
 
 * Run the following command on the terminal: gcc -o BMI-ES19BTECH11017 BMI-ES19BTECH11017.c 

USAGE
-----
 
 * Run the following command on the terminal: ./BMI-ES19BTECH11017

   - It is assumed that the binary file is executable.

 * Input the data:

   - Enter height in metres when prompted and hit <Enter>.
   - Enter weight in kilograms when prompted and hit <Enter>.

 * The data will be displayed in the following format:
   - BMI (double)
   - Category (on a newline)

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in
