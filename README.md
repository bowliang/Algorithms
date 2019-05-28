________
OVERVIEW

 This is C++ implementations of algorithms in the textbook Algorithm, 4th Edition. 
 The original implementation is done in Java, and here I redo them in C++ for later use.

_____________
CONFIGURATION

 The compilation of algorithms requires the CMake build system and GNU make.
 Typing
     $ make config 
 
 would configure the library with default options. The CMake build system will
 try to find the libraries rely on.
 The following options can be given to configure the library:
 
   - cc=[compiler]     The C compiler used in cmake tests, default: gcc
   - cxx=[compiler]    The C++ compiler to use, default: g++
   - prefix=[path]     Installation path, default: /usr/local
   - verbose=[bool]    Verbose output, default: false

 This is the most standard config info
     $ make config cxx=g++ prefix=~/libs

___________
COMPILATION

 To compile the library once the configuration has taken place, type
     $ make 

____________
INSTALLATION
 
 Install the library by typing 
     $ make install 

_____
OTHER
 
 To remove the files, type 
     $ make uninstall 
 
 To remove all object files while retaining the configuration, type    
     $ make clean 

_____
AUTHOR

 Bowen Liang
 bowen.raymone@gmail.com
