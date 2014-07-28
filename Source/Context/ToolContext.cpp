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
#include "ToolContext.hpp"
#include <QStatusBar>
#include <QToolBar>
#include <QMenu>

NGM::API::ToolContext::ToolContext() : _statusBar(nullptr) {}

NGM::API::ToolContext::~ToolContext()
{
	for (auto &i : _menus)
	{
		delete i;
	}
	for (auto &i : _tools)
	{
		delete i;
	}
	delete _statusBar;
}

QMenu *NGM::API::ToolContext::menus()
{
	return _menus[0];
}

uint8_t NGM::API::ToolContext::menuCount() const
{
	return _menus.count();
}

QToolBar *NGM::API::ToolContext::toolBars()
{
	return _tools[0];
}

uint8_t NGM::API::ToolContext::toolBarCount() const
{
	return _tools.count();
}

QStatusBar *NGM::API::ToolContext::statusBar() const
{
	return _statusBar;
}

