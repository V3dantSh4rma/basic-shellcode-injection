# Basic Shellcode Injection
Just something related to Malware dev i've been learning lately. What this code does is that it starts up a process. The Process is just the simple GUI I have coded using Windows header file. And then use the [shellcode.c](./shellcode.c) file to crash the program with the shellcode.


# Installation[Windows]
Make sure that you have any c compiler installed. Let it be GCC, Clang or any other compiler you have on your windows machine. In my case, I have gcc installed.
```terminal
git clone https://github.com/V3dantSh4rma/basic-shellcode-injection.git
gcc gui.c -o gui
gcc main.c -o main.exe
gcc shellcode.c -o shellcode
```

# Usage:
This Project requires 2 working terminals. The first terminal is to open up the process, and the second terminal is for using the [shellcode CLI](./shellcode.c) file which we coded.

## Open your first terminal, and type:
```
./main
```
This executable simply opens the [gui.c](./gui.c) file and Prints the Relevant information. After running this ``./main`` command, You will see a Process ID. Copy it for the usage of second terminal

## Open your second terminal, and type:
```
./shellcode <PROCESS_ID>
```
Copy the ``<PROCESS_ID>`` with the Process ID which you copied. Later, You will somewhat notice that the gui which appeared is not there anymore and our shellcode has crashed the program.