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
#include "Library.hpp"
#include "PluginDepr.hpp"

NGM::Core::Library::Library(API::Plugin *plugin, QLibrary *library) :
  plugin(plugin), library(library) {}

NGM::Core::Library::~Library()
{
	delete plugin;
	if (library != nullptr)
	{
		library->unload();
		delete library;
	}
}

bool NGM::Core::Library::operator<(const Library &other)
{
	return plugin < other.plugin;
}
