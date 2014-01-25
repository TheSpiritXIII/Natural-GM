/**
 *  @file ResourceContentItem.hpp
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
#include "ResourceContentItem.hpp"

NGM::Model::ResourceContentItem::ResourceContentItem(
	NGM::Resource::Resource *resource, const QString &filepath,
	NGM::Model::ResourceSettings settings) : resource(resource),
	_settings(settings)
{
	setFilepath(filepath);
}

void NGM::Model::ResourceContentItem::setFilepath(const QString &filepath)
{
	_filepath = filepath;
	int position = filepath.lastIndexOf('/') + 1;
	if (_settings & NoExtension)
	{
		setText(filepath.mid(filepath.size() - position,
							 filepath.indexOf(QChar('.'), position)));
	}
	else
	{
		setText(filepath.right(filepath.size() - position));
	}
}

NGM::Model::ResourceContentItem *NGM::Model::ResourceContentItem::toContentItem()
{
	return this;
}
