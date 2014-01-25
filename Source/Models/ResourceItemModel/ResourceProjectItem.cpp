/**
 *  @file ResourceProjectItem.cpp
 *  @section License
 *
 *      Copyright (C) 2014 Daniel Hrabovcak
 *
 *      This file is a part of the Natural GM IDE.
 *
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
#include "ResourceProjectItem.hpp"

NGM::Model::ResourceProjectItem::ResourceProjectItem(
		NGM::Resource::Resource *resource, NGM::Resource::Project *project,
		const QString &filepath, ProjectSettings settings)  :
	resource(resource), project(project), _settings(settings)
{
	setFilepath(filepath);
}

void NGM::Model::ResourceProjectItem::setFilepath(const QString filepath)
{
	int split = filepath.lastIndexOf('/') + 1;
	_filename = filepath.right(filepath.size() - split);
	_directory = filepath.left(split);
	setText(_filename);
}

NGM::Model::ResourceProjectItem *NGM::Model::ResourceProjectItem::toProjectItem()
{
	return this;
}
