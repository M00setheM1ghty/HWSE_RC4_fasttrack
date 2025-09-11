
=== Submission
** *Compilation*
  *** Executable is built with: gcc -std=c99 -Wall -Wextra -pedantic -Wno-unused-parameter -o RC4 main.c
** *Execution*
  *** How to start: ./RC4 -h 
      This prints a manual to the command line.
  *** The user only needs to input the command at the beginning. There are no intermediate inputs necessary. "End of fole reached is printed if the program finished sucessfully and the user can issue another run if the program. If the input is incorrect the manual will be printed alongside the incorrect values provided. 
  Note: the text files provided for input and output must exist and be correctly filled. The program does not check if the input is empty or if the output is not.
  *** Built and tested only on Linux Mint.
** *Completed Tasks*
  *** Generation + Initialization of array then scrambling it with the swap elements function according to provided pseudocode. -> Keystream creation
  *** Read input from file
  *** Writing output to file
  *** encrypt and decrypt input values with the provided key -> based on the provided pseudocode in step 4 of the specification.
  *** implemented command line interface with getopt
  *** tested the program according to the steps listed in project description

