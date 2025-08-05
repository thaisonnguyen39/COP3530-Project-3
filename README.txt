Instructions on how to run this project:
BEFORE YOU TRY TO RUN IT:
    the "archive.zip" file was uploaded using GitHub's LFS. To properly download and access the file's contents,
    you must first:

    -Open the repository (Link: https://github.com/thaisonnguyen39/COP3530-Project-3)
    -Click "archive.zip"
    -Download the raw file
    -Place the file in the project's main directory
    -Extract "archive.zip" to "COP3530-Project-3-main/archive"
    -Check to make sure a file named "US_Accidents_March23.csv" is stored inside

    If this fails or the data is outdated, you can also download the archive.zip file from the database source
    Link: https://www.kaggle.com/datasets/sobhanmoosavi/us-accidents/data
Compiling:
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
