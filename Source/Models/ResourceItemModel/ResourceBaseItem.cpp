/**
 *  @file ResourceBaseItem.hpp
 *  @section License
 *
 *      Copyright (C) 2013 Daniel Hrabovcak
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
#include "ResourceBaseItem.hpp"
#include "ResourceGroupItem.hpp"
#include "ResourceItemModel.hpp"
#include "ResourceProjectItem.hpp"

NGM::Model::ResourceBaseItem::ResourceBaseItem(const QString &text) :
	_parent(nullptr), _project(nullptr), _model(nullptr), _text(text) {}

NGM::Model::ResourceBaseItem::~ResourceBaseItem() {}

const QModelIndex NGM::Model::ResourceBaseItem::index() const
{
	if (_parent != nullptr)
	{
		return _model->index(childNumber(), 0, _parent->index());
	}
	return QModelIndex();
}

int NGM::Model::ResourceBaseItem::childNumber() const
{
	if (_parent)
	{
		return _parent->childPosition(this);
	}
	return -1;
}

NGM::Model::ResourceContentItem *NGM::Model::ResourceBaseItem::toContentItem()
{
	return nullptr;
}

NGM::Model::ResourceProjectItem *NGM::Model::ResourceBaseItem::toProjectItem()
{
	return nullptr;
}

NGM::Model::ResourceGroupItem *NGM::Model::ResourceBaseItem::toGroupItem()
{
	return nullptr;
}

bool NGM::Model::ResourceBaseItem::lessThan(const ResourceBaseItem *lhs,
											const ResourceBaseItem *rhs)
{
	return lhs->text() < rhs->text();
}
