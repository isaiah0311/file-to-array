# File To Array

Takes in a file and converts the data into a byte array.

## Building

Pressing ctrl + shift + b while in VSCode will pull up the build tasks. From
here there are two options, build and clean. Build will compile the code and
place the executable in the bin folder. Clean will remove the bin and obj
directories. In order to build, you must have MSVC installed if you are on
Windows and GCC installed if you are on Linux.

## Running

If you are trying to run from VSCode using the debugger, press F5. This requires
you to have Visual Studio if you are debugging from Windows or GDB if you are
debugging from Linux.

If you are running the program outside of VSCode, or not using a debugger, you
can run it from the command line.

Example: file_to_array.exe -i input_file [-n bytes_per_line] [-s] [-v]

## Authors

Isaiah Lateer
