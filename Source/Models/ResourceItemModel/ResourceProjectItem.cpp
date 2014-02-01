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
#include "ResourceItemModel.hpp"
#include <QStringBuilder>

NGM::Model::ResourceProjectItem::ResourceProjectItem(
		NGM::Resource::Content *resource, const NGM::Resource::Project *project,
		const QString &filepath, ResourceItemFlags flags)  :
	ResourceGroupItem(flags), resource(resource), _project(project)
{
	_projectItem = this;
	setFilepath(filepath);
}

NGM::Model::ResourceProjectItem *NGM::Model::ResourceProjectItem::toProjectItem()
{
	return this;
}

void NGM::Model::ResourceProjectItem::setFilepath(const QString filepath)
{
	int split = filepath.lastIndexOf('/') + 1;
	_filename = filepath.right(filepath.size() - split);
	_directory = filepath.left(split);
	updateText();
}

void NGM::Model::ResourceProjectItem::setModified(bool modified)
{
	_flags |= modified ? Modified : ~Modified;
	updateText();
}

void NGM::Model::ResourceProjectItem::updateText()
{
	setText((_flags & Modified) ? _filename % QChar('*') : _filename);
}
