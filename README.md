# cs530-a2
For SIC/XE Assembler Project

Files Manifest:
    Makefile
    main.cpp
    typedef.cpp
    typedef.hpp
    symtab.cpp
    symtab.hpp
    instruction.cpp
    instruction.hpp

Compile Instructions:
    Run 'asxe' from the project root directory.
    This will output two files within data/files.

Operating Instructions:
    Usage: asxe filename1.sic filename2.sic filename3.sic

Design Features:
    The program reads up to three .sic files and outputs one .l and one .st file.
    The program uses a two pass assembler, with the first pass making the .l and
    the second making the .sic. The role of deciphering the values within .sic will
    be divded up between the struct in instruction.hpp and typedef.hpp

Extra:
    I had to use a vector string and sprintf() to convert a placeholder printf()
    system into a file outputing system

Lessons Learned:
    * How to use struct as opposed to classes.
    * How to use a format specifier for printf()-like functions.
    * Strategies on how to split up lines into segments in a useful fasion.
    * A better understanding of how addressing modes works.