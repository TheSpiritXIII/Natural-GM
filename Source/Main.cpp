/*-
 *  Copyright (c) 2014 Daniel Hrabovcak
 *
 *  This program is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or (at your
 *  option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 *  for more details.
**/
#include <QApplication>
#include "SDIEditorWindow.hpp"
#include "PluginDialog.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	NGM::Widget::SDIEditorWindow window;
	window.show();
	NGM::Widget::PluginDialog dialog;
	dialog.show();
	return app.exec();
}
