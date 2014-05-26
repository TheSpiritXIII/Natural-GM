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
#include "EditorTools.hpp"
#include <QStatusBar>

NGM::API::EditorTools::EditorTools(QMenu **menus, uint8_t menuCount,
  QToolBar **toolBars, uint8_t toolBarCount, QStatusBar *statusBar) :
  _menus(menus), _menuCount(menuCount), _toolBars(toolBars),
  _toolBarCount(toolBarCount), _statusBar(statusBar) {}

NGM::API::EditorTools::~EditorTools()
{
	delete [] _menus;
	delete [] _toolBars;
	delete _statusBar;
}

QMenu **NGM::API::EditorTools::menus() const
{
	return _menus;
}

uint8_t NGM::API::EditorTools::menuCount() const
{
	return _menuCount;
}

QToolBar **NGM::API::EditorTools::toolBars() const
{
	return _toolBars;
}

uint8_t NGM::API::EditorTools::toolBarCount() const
{
	return _toolBarCount;
}

QStatusBar *NGM::API::EditorTools::statusBar() const
{
	return _statusBar;
}

