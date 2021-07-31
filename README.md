# Käyttöjärjestelmät & Systeemiohjelmointi harkkatyöprojekti

Description:
  This was done as a project for university course in LUT. 
  Project is based on https://github.com/remzi-arpacidusseau/ostep-projects.
  I picked three smaller projects from ostep-projects: reverse,
  utilites and xv6. 
  
Installation:
  Get the clone-link of the repository, open terminal,
  change the current working directory to the location 
  where you want the cloned directory and then type
  $ git clone https://github.com/hosuli/Systeemiohjelmointi.git.
  If you want to run the tests used for testing this, you
  also need to get tester-file from
  https://github.com/remzi-arpacidusseau/ostep-projects.
  
Reverse usage:
  Reverse is program that reverses given file (or standard input) and prints it to another file (or standard output).
  Program can be used in following ways:
  
    prompt> ./reverse
    prompt> ./reverse input.txt
    prompt> ./reverse input.txt output.txt

Utilities usage:
  In utilities project I created some basic UNIX tools. Wcat is for reading out the content of file(s) and printing it out.
  Usage is as follows:
    prompt> ./wcat [file]
  
  Wgrep reads lines from a file and searches them for a given search word.
    prompt> ./wgrep searchterm [file]
    
  Wzip and wunzip are used for file compression.
    prompt> ./wzip file.txt
    prompt> ./wunzip file.z
    
Xv6 Usage
  In this kernel hacking project I created my own system call to xv6. To install and run this, you also need
  to clone the following xv6 repository: git clone git://github.com/mit-pdos/xv6-public.git
  Added system call is called getreadcount() and it counts how many times the read() system call has been called.
  When you get the build running, just type in "getreadcount" and a numbers is returned back to you.
  
  
