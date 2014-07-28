Natural GM
==========
Natural GM (NGM) is a plugin-based multi-purpose integrated developer
environment (IDE). NGM was created mainly for the purpose of having a reliable
and extensible game editor and other miscellaneous, related tools.

License
-------
Copyright (C) 2013 Daniel Hrabovcak

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

Compiling
---------
Qt 5.x is required to compile NGM. To compile, run qmake on Natural-GM.pro.

After the compilation is completed, copy the content of the Resources directory
into the build directory. The Resources directory contains icon and skin sets.

Skins
-----
As a Qt application, NGM supports QSS (Qt StyleSheet) based skinning. You can
set a skin using the command line argument '-stylesheet'.

Currently, skins cannot be set internally, but such functionality is planned.

Plugins
-------
Plugins provide a way of adding extra content, including editing facilities and
extending existing functionality.

###Installing Plugins
As of now, plugins cannot be installed externally. They must be included and
loaded in the source code.

### Creating Plugins
Plugins __must__ be compiled with either GCC (MinGW on Windows) or Clang. To
begin, you may link against the NGM Library by either using an existing one, or
by building it yourself under Source/Natural-GM-Library.
plugin must return a valid API::Plugin implementation through the function name
NGM_PLUGIN_MAIN.

You can build the NGM Core library 

#### Creating Editors
Creating an editor relies mainly on the API::Factory class. First and foremost,
this class must be sub-classed to return a valid widget. Optionally, for global
tool widgets (a status bar, menu bars and tool bars), then the API::EditorTools
should be sub-classed as well.

The editor itself will _not_ be present inside the application unless it is
evoked by a serializer. If the editor is not an alternative replacement for an
existing editor, then a serializer must also be created and bound with the
editor type.

#### Creating Serializers
Serializers are responsible for translating file formats into visual editors.
In order to read files and/or projects, then API::Serializer must be
sub-classed to at least be able to create, save and load files.

Serializers function using various API::SerialData classes, which provide
representations of various data structures. These classes are provided as
extensible unions - default classes can be cast using built-in methods, while
another cast method is provided that uses an internal UUID to cast user-created
serial data.