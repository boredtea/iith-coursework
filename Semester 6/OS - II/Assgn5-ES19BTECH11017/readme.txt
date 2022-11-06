CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

This assignment implements the Readers-Writers with preference given to readers and the fair Readers-Writers algorithms.

REQUIREMENTS
------------

The programs require the following softwares/files:

 * g++ 
   - It is assumed that the system is Unix-like. 
     > However it should work on any system with g++ and on most C++ compilers.
 * input file
   The program reads from an input file named 'inp-params.txt'.
   
COMPILATION
-----------
 
 * Run the following commands on the terminal for: 
   - RW: g++ Assn5-rw-ES19BTECH11017.cpp -o rw -pthread
   - FRW: g++ Assn5-frw-ES19BTECH11017.cpp -o frw -pthread

USAGE
-----
 
 * Run the following commands on the terminal for:
   - RW: ./rw
   - FRW: ./frw

 * The output for each algorithm will be displayed in the following files:
   - RW: RW-log.txt
   - FRW: FairRW-log.txt
   - Average_time.txt: this file appends the average times of each algorithm every time they are run
   Additionally, the average waiing times and the worst waiting times for the reader and writer threads in each algorithm are printed to console.

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in