CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------
This program makes extensive use of structures and pointers to 
achieve its goal as described in the following paragraphs.

An automobile company has several characteristics for engine parts: 
- serial numbers starting from AA0 to FF9
- date of manufacture 
- material
- weight

A structure is created to store information about each engine part. Using
this information, functions are written to retrieve the following:
1) List of all the serial numbers of engine parts where weight is more than 5kg.
2) The year of manufacture of engine parts having serial numbers between 
   AA2 and BB7(both inclusive).
3) List of all the details of engine parts where the year of manufacture is within 
   3 years of 15th Nov 2019.

REQUIREMENTS
------------

This program requires the following software:

 * gcc 

   - It is assumed that the system is Unix-like. 
     > However it should work on any system with gcc and on most C compilers.
   - The code was tested on gcc (Ubuntu 5.4.0-6ubuntu1~16.04.11).

COMPILATION
-----------
 
 * Run the following command on the terminal: gcc -o Structures-ES19BTECH11017 Structures-ES19BTECH11017.c

USAGE
-----
 
 * Run the following command on the terminal: ./Structures-ES19BTECH11017

   - It is assumed that the binary file is executable. If not, explicity set it to executable using chmod.

 * Input the data:

   - Enter the number of engine parts when prompted and hit <Enter>.
   - Enter the following data about engine parts when prompted 
     and hit <Enter>.
     > Serial number (AA0, AA1, ..., FF9)
     > Date of manufacture (dd-mm-yyyy)
     > Material (1 for iron, 2 for steel)
     > Weight (an integer between 1 and 10, both inclusive, in kg)
   - In case of invalid input, follow the displayed instructions

 * The data will be displayed in the following format:
   - Serial numbers where weight is more than 5kg
   - Years of manufacture of engine parts having serial number between AA2 and BB7
   - Details of engine parts where year of manufacture is within 3 years of 15th Nov 2019
   - In case of invalid inputs, error messages are displayed

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in
