Natural GM
==========

Getting Started
---------------

Before installing, you must have Qt 5.0 or higher installed. NGM has
only been tested with GCC (MinGW on Windows) 4.7.2 and higher so far,
so other compilers might not work.

Installing QScintilla
---------------------
Before you can run Qt, you must have QScintilla installed. You may
download it here:
http://www.riverbankcomputing.com/software/qscintilla/download

Compiling Natural GM
--------------------
Now that you have all required prerequisites, you can open a terminal
and type the following commands in order (__NOTE:__ Qt must be in the
system's path. On Windows, a console application is provided with Qt
that sets the system path accordingly):

```
cd Source
qmake Natural-GM.pro
make
```

Finishing Up
------------

To complete the installation process, you can copy over contents from
the Resource directory to the location of the executable. This gives
you the default icons and themes.