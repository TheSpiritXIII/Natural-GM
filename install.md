Natural GM
==========

Getting Started
---------------

Before installing, you must have Qt 5.2 or higher installed. NGM has
only been tested with GCC (MinGW on Windows) 4.7.2. Visual Studio is
not supported.

Installing QScintilla
---------------------
Before you can run Qt, you must have QScintilla installed. You may
download it here:

http://www.riverbankcomputing.com/software/qscintilla/download

Please note that for some strange reason, QScintilla does not build
with a debug version by default, so if you will be debugging in NGM,
you must also create a debug version of the library yourself.

Compiling Natural GM
--------------------
Once all required prerequisites are meet, you can open a terminal and
type the following commands in order (__NOTE:__ Qt must be in the
system's path. On Windows, a console application is provided with Qt
that sets the system path accordingly):

```
cd Source
qmake Natural-GM.pro
make
```

Finishing Up
------------

To complete the installation process, you must copy over contents from
the Resource directory to the location of the executable or build
folder. This gives you the default icons and themes. If you do not,
you will be seeing NGM naked. Don't look! D: