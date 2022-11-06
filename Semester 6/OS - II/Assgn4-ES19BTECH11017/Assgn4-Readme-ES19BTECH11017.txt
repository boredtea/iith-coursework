CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

This assignment implements CAS, TAS, and bounded CAS mutual exclusion algorithms.

REQUIREMENTS
------------

The programs require the following softwares/files:

 * g++ 
   - It is assumed that the system is Unix-like. 
     > However it should work on any system with g++ and on most C++ compilers.
 * input file
   The program reads from an input file named 'inp-params.txt'.
   
   A sample input file titled 'inp-params.txt' has been included in the submission zip file.

COMPILATION
-----------
 
 * Run the following commands on the terminal for: 
   - CAS: g++ SrcAssgn4-cas-ES19BTECH11017.cpp -o CAS
   - TAS: g++ SrcAssgn4-tas-ES19BTECH11017.cpp -o TAS
   - Bounded CAS: g++ SrcAssgn4-cas-bounded-ES19BTECH11017.cpp -o CAS_bounded

USAGE
-----
 
 * Run the following commands on the terminal for:
   - CAS: ./CAS
   - TAS: ./TAS
   - Bounded CAS: ./CAS_bounded

   - It is assumed that the binary file is executable. If not, explicity set it to executable using chmod.

 * The output for each algorithm will be displayed in the following files:
   - CAS: CAS-log.txt
   - TAS: TAS-log.txt
   - Bounded CAS: CAS-bounded-log.txt
   Additionally, the average waiing time and the worst waiting time for each algorithm is printed to console.

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in