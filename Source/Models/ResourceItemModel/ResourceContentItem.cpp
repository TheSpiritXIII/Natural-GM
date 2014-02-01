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
	NGM::Resource::Content *content, ResourceItemFlags flags,
	ResourceGroupItem *container) : ResourceBaseItem(flags, container),
	content(content)
{
	updateText();
}

NGM::Model::ResourceContentItem::ResourceContentItem(
	NGM::Resource::Content *content, const QString &text,
	ResourceItemFlags flags, ResourceGroupItem *container) :
	ResourceBaseItem(text, flags, container), content(content) {}

void NGM::Model::ResourceContentItem::setFilepath(const QString &filepath)
{
	content->filepath = filepath;
	updateText();
}

NGM::Model::ResourceContentItem *NGM::Model::ResourceContentItem::toContentItem()
{
	return this;
}

void NGM::Model::ResourceContentItem::updateText()
{
	int position = content->filepath.lastIndexOf('/') + 1;
	if (content->settings & Resource::Content::NoExtension)
	{
		setText(content->filepath.mid(content->filepath.size() - position,
			content->filepath.indexOf(QChar('.'), position)));
	}
	else
	{
		setText(content->filepath.right(content->filepath.size() - position));
	}
}
