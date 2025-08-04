Instructions on how to run this project:

The project includes files which use CMake to run and compile the program. If you downloaded
the repository's contents and are using CLion, you should be able to open the main directory
by opening CLion and navigating to

Menu(Three lines)->File->Open

then navigate to where you have the COP3530-Project-3 folder downloaded and click "OK".
You should be able to compile and run the program at this point.

If you plan on using a different IDE to run it, this method might not work. If this fails,
you can take the source files "main.cpp", "Graph.h", and "Graph.cpp" and use them to create a new project and run it
in your IDE of choice.

Alternatively, you can use a command terminal to compile the program, BUT, 
this will vary depending on your compiler
G++ Example: g++ -std=c++11 -o main.out main.cpp Graph.h Graph.cpp
