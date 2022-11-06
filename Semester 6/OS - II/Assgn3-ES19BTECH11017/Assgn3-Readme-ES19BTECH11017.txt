CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Compiling
 * Usage
 * Author

INTRODUCTION
------------

These programs implement the rate-monotonic and earliest deadline first scheduling algorithms.

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
 
 * Run the following command on the terminal for RMS: g++ Assgn3-RMSES19BTECH11017.cpp -o RMS
 * Run the following command on the terminal for EDF: g++ Assgn3-EDFES19BTECH11017.cpp -o RMS

USAGE
-----
 
 * Run the following command on the terminal for RMS: ./RMS
 * Run the following command on the terminal for EDF: ./EDF

   - It is assumed that the binary file is executable. If not, explicity set it to executable using chmod.

 * The output will be displayed in the following two files:
   - RM-Log.txt and EDF-Log.txt. These contain the logs of each step that was executed while the processes were being scheduled.
   - RM-Stats.txt and EDF-Stats.txt. These files contain information like the total number of processes, number of complete and 
     incomplete processes, and the average waiting time of all the processes.

AUTHOR
------
 
Soumi Chakraborty
es19btech11017@iith.ac.in