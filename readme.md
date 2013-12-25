Natural GM
==========

License
-------

Copyright (C) 2013 Daniel Hrabovcak

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


Themes & Skins
--------------

__NOTE:__ THEMING IS NOT CURRENTLY FUNCTIONAL.

### Themes

Themes are code color preferences. To add a new theme, create a .ngth 
file inside the _themes_ directory.

### Skins

To add a new skin, simply place a .qss file inside the _skins_ folder.
A .qss file is a Qt Stylesheet file. For stylesheet documentation,
please visit the following website:
http://qt-project.org/doc/qt-5.0/qtwidgets/stylesheet.html

### Icons

Natural GM supports custom icons. To create an icon theme, create a
directory containing all of your icons and place them inside the
_icons_ directory. If you do not supply certain icons, your users will
only see text instead. Icons must be in .png format. Please see the
default icon packages for examples of correct naming.


Addons
-------

__NOTE:__ Addons ARE NOT CURRENTLY FUNCTIONAL.

Addons are essentially libraries compiled in C++. There are two
different types of addons that NGM is able to use: Tool Addons and
Widget Addons. Tool Addons are addons that simply request a menu
a tool button and can be compiled with any compiler. Widget Addons,
on the other hand, are able to do more such as creating an entirely
new editor, with the restriction that the addons must be compiled in
the same compiler that NGM was compiled in.

```c++
// To do.
```

If you create a new resource or project type, icons will automatically
be loaded based on the respective identifier names.


Translations
------------

Translations will be available in the future via Qt Linguist. A
basic translation file is provided as Untranslated.ts.