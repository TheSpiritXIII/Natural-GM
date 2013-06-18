Natural GM
==========

License
-------

Copyright (C) 2013 Daniel Hrabovcak and Robert B. Colton

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


Skins
-----

To add a skin, you must create a directory named "skins". Inside,
you must add another directory that is named after your skin.
Natural GM will use that name as the name of skin when the user is
looking through their installed skin. Then, your skin *must* have a
file named "settings.ngsk" (without the quotes). This file is a
binary file which decides whether the skin has a stylesheet and/or
icons.

### Settings

The skin settings file should only be 1 byte long. You may use a
binary to ascii converter to generate your settings file. It is
structured by the following bits:

### Stylesheets

Stylesheets are written using QSS (Qt's CSS-like Stylesheet
language). For stylesheet documentation, please visit:
http://qt-project.org/doc/qt-5.0/qtwidgets/stylesheet.html

### Icons

You may optionally place icons. If you do not supply any icons,your
users will only see text unless they choose to opt out. Icons may
be .png, .bmp or .svg. The only requirement is that they must have
the correct filename (eg. new.png is for the "New Project" button).


Plugins
-------

Plugins are essentially libraries compiled in C++. If you would like
it to interact with Qt, you must include the Qt library.

While plugins are not readily available yet, you can experiment with
creating classes. A plugin must have the following functions defined
or else it will not be loaded (even if they are empty):

```c++
enum class NGM_PLUGIN
{
	NAME = 0,
	AUTHOR = 1,
	DESCRIPTION = 2
};
bool load(NGMMainWindow *window);
bool startup(NGMMainWindow *window);
bool cleanup(NGMMainWindow *window);
const char* getPluginInfo(NGM_PLUGIN type);
```

The function startup() and cleanup() are requested on the program's
start and close respectively. The function load() occurs directly
after the startup() function is called. Any extensions should be
loaded in the load() function while others such as resources should
be loaded in the startup() function. If you want to add items to the
menus and such, you can simply include the headers found in Natural
GM's github (http://www.github.com/enigma-dev/NaturalGM).

If you use the plugin mechanism to create a new resource type, you
can create an icon named after the generic name of the resource and
Natural GM will load it from the plugin folder (if the user has not
already created an image for it in their skin or icon folders).


Compiling
---------

In order to compile, you must have Qt 5.0.1 and QScintilla 2.7.1
installed. This project is best edited under Qt Creator 2.7 and
compiled using GCC compiler, version 4.7 or higher. Your compiler
must have C++11.


Translations
------------

Translations will be available in the future via Qt Linguist.