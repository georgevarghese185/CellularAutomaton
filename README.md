# Cellular Automaton
This is an OpenGL application written in C++. Its main aim is to provide the 
user with a 'Conway's Game Of Life' cellular automaton for the user to set up 
and watch it evolve over time. Optionally the user can set their own rules for 
the cellular automaton and see how it causes the cells to evolve.

This app was created for my 'Computer Graphics Lab' project in the 6th semester 
of my computer engineering course.

# Project Structure
I did not use any VCS while actually making the project. This git respository 
was created much later so that I could upload the code online. While I was 
actually making the app, I manually made a new copy of the project each time I 
made an updated/improved version. I simply translated each version into a commit
onto the main branch for this repo.

That being said, here's a quick explanation of each folder in the project:

### freeglut
I used glut for all OpenGL functions. This folder contains the freeglut library 
for compiling the program. Instrutions how to use them are given below.

### sources
This folder contains all .cpp and .h files that I created

### textures (version 2.1+)
This folder contains the .raw files I created for all text used for 
titles/captions throughout the app. (I was unable to implement a font 
alternative like freetype). It also contains the photoshop files I used to 
create the text with its font and effects.
The .raw files are quite big since they are raw images, so I compressed all 
of them into a zip file. Instructions on how to use them in the app are 
explained below

# Setting up
## Requirements
1. A C++11 compiler or IDE. I used Visual Studio 2015
2. Windows. The app should compile and run on linux/mac thanks to glut, but a 
line or two would have to be changed in the program where I've used a windows 
time function for a timer.

## Download the sources
You can do one of the following

1. Download the latest version source code from the main page as a zip.
2. If you want to compile and run an older version, you'll need to clone the 
repository and checkout one of the older commits according to the version you 
want

## Compiling and Running
These steps are for Visual Studio but you can follow similar steps for another 
IDE

### Create a new project
In visual studio, simply create a new Win32 Console Application project (under 
Visual C++) and name it whatever you want

### Setting up freeglut
Set up your IDE to point to 'freeglut/include' for the freeglut header files and
'freeglut/lib' for the freeglut library file.
If you're using Visual Studio you can follow these steps:

1. Right click the project name in the solution explorer and go to properties
2. Go to VC++ Directories
3. You might want to set this up for "All configurations" in the top left drop 
down box
4. In the 'Include' paths, add the path to 'freeglut/include'
5. In the Library paths, add the path to 'freeglut/lib'
6. Apply changes

### Adding _CRT_SECURE_NO_WARNINGS
Versions 2.1+ use the fopen function which is deprecated in visual studio. To be
able to build the app, you need to add the _CRT_SECURE_NO_WARNINGS definition. 
To do this:

1. Go to the project properties
2. Go to C/C++ > Preprocessor section
3. in 'Processor Definitions' place a semicolon separator (if not there already)
and put in '_CRT_SECURE_NO_WARNINGS'
4. Apply changes

### Compiling
Add all the .cpp and .h files in the 'sources' folder into your project and 
build it.

### Running
Before running the app do the following

1. copy 'freeglut.dll' from 'freeglut/bin' to the folder where the compiled 
output binary (.exe) is present
2. (only for v2.1+) You need to copy all the texture files into the output 
folder as well
	i) go to the 'textures' folder and extract the files in 'textures.zip'
	ii) You will get a number of "TEX_..." files with no extension. These are 
	the texture files
	iii) Copy these texture files, go the folder where the compiled exe is, 
	create a new folder 'textures' and paste these files in there. Make sure you
	do this step right or the program won't run

By the end, the folder where the compiled executable is MUST have the following

1. The executable itself (eg: cellular_automaton.exe)
2. The 'freeglut.dll' file
3. A 'textures' folder inside which is all the "TEX_" files

You should now be able to run the app by running the exe.

# Credits
-The first person to thank would be youtuber "Lemmino" and his video "Simulated 
Reality"(https://www.youtube.com/watch?v=K4rCzA8fS84) where at 5:52 he explains 
what a Cellular Automaton is and how it works. It was this clip that introduced 
me to the concept of a cellular automaton and Conway's game of life and inspired
me to try making a cellular automaton by myself and submit it as my computer 
graphics lab project at that time.

-Suraj Sivakumar (http://certigate.org) for writing and providing me the Win32 
code for the text used to display the title and version on the start screen. 
(Code found in TextManip.h and TextManip.cpp)

-wikibooks.org for the texture loading code. (OpenGL texture loading tutorial: 
https://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures)