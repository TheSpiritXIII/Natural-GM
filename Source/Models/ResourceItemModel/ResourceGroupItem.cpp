/**
 *  @file ResourceGroupItem.cpp
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
#include "ResourceGroupItem.hpp"
#include "ResourceItemModel.hpp"
#include "ResourceProjectItem.hpp"
#include "Serializer.hpp"
#include "Project.hpp"
#include <algorithm>
#include <cassert>
#include <stack>

NGM::Model::ResourceGroupItem::ResourceGroupItem(const QString &name,
	ResourceItemFlags flags) : ResourceBaseItem(name, flags) {}

NGM::Model::ResourceGroupItem::ResourceGroupItem(ResourceItemFlags flags) :
	ResourceBaseItem(flags) {}

NGM::Model::ResourceGroupItem::~ResourceGroupItem()
{
	for (auto &i : _children)
	{
		delete i;
	}
}

void NGM::Model::ResourceGroupItem::sort()
{
	if (_model)
	{
		QList<QPersistentModelIndex> list;
		list << QPersistentModelIndex(index());
		_model->layoutAboutToBeChanged(list,
			QAbstractItemModel::VerticalSortHint);
		sortChildren();
		_model->layoutChanged(list, QAbstractItemModel::VerticalSortHint);
	}
	else
	{
		sortChildren();
	}
}

int NGM::Model::ResourceGroupItem::childPosition(
		const ResourceBaseItem *find) const
{
	if (_flags & IsSorted)
	{
		QList<NGM::Model::ResourceBaseItem*>::const_iterator i =
			std::lower_bound(_children.begin(), _children.end(), find,
							 &ResourceBaseItem::lessThan);
		if (i != _children.end())
		{
			return i - _children.begin();
		}
	}
	else
	{
		for(int i = 0; i != _children.size(); ++i)
		{
			if (_children[i] == find)
			{
				return i;
			}
		}
	}
	return -1;
}

void NGM::Model::ResourceGroupItem::insertSorted(ResourceBaseItem *item)
{
	assert(_flags & IsSorted);
	assert(!(_flags & NoSort));
	ResourceItemIterator i = std::lower_bound(_children.begin(),
		_children.end(), item, &ResourceBaseItem::lessThan);
	int position = i - _children.begin();
	_model->beginInsert(index(), position, position);
	_children.insert(position, item);
	_model->endInsert();
}

void NGM::Model::ResourceGroupItem::insert(ResourceBaseItem *item)
{
	item->_parent = this;
	if (item->_model != _model)
	{
		setModel(item, _model);
	}
	if (item->_projectItem != _projectItem &&
			(_parent != nullptr || toProjectItem()))
	{
		setProjectItem(item, _projectItem);
	}
	if (_model)
	{
		if (_model->sort() && item->toGroupItem())
		{
			item->toGroupItem()->sortChildren();
		}
		if (_model->sort() && !(_flags & NoSort))
		{
			insertSorted(item);
		}
		else
		{
			int position = count();
			_model->beginInsert(index(), position, position);
			_children.append(item);
			_model->endInsert();
			_flags &= ~IsSorted;
		}
	}
	else
	{
		_children.append(item);
		_flags &= ~IsSorted;
	}
}

void NGM::Model::ResourceGroupItem::insert(ResourceBaseItem *item, int position)
{
	if (_model)
	{
		assert(!_model->sort());
		setModel(item, _model);
		_model->beginInsert(index(), position, position);
		item->_parent = this;
		item->_model = _model;
		_children.insert(_children.begin() + position, item);
		_model->endInsert();
	}
	else
	{
		item->_parent = this;
		item->_model = _model;
		_children.insert(_children.begin() + position, item);
	}
	_flags &= ~IsSorted;
	if (item->_model != _model)
	{
		setModel(item, _model);
	}
	if (item->_projectItem != _projectItem && _parent != nullptr)
	{
		setProjectItem(item, _projectItem);
	}
}

void NGM::Model::ResourceGroupItem::move(int from, ResourceGroupItem *group)
{
	ResourceBaseItem *item;
	ResourceItemIterator i;
	if (_model)
	{
		if (_model->sort() && !(_flags & NoSort))
		{
			assert(group != this);
			i = _children.begin() + from;
			item = *i;
			if (group->count() != 0)
			{
				ResourceItemIterator to = std::lower_bound(
					group->_children.begin(), group->_children.end(),
					item, &ResourceBaseItem::lessThan);
				_model->beginMove(index(), from, from, group->index(),
										 to - group->_children.begin());
				_children.erase(i);
				group->_children.insert(to, item);
			}
			else
			{
				_children.erase(i);
				_model->beginMove(index(), from, from, group->index(), 0);
				group->_children.append(item);
			}
		}
		else
		{
			_model->beginMove(index(), from, from,
							  group->index(), group->count());
			i = _children.begin() + from;
			item = _children[from];
			_children.erase(i);
			group->_children.append(item);
			_flags &= ~IsSorted;
		}
		item->_parent = group;
		_model->endMove();
	}
	else
	{
		i = _children.begin() + from;
		item = *i;
		group->_children.append(item);
		_children.erase(i);
		item->_parent = group;
		_flags &= ~IsSorted;
	}
	if ((item->_model != group->_model ||
		 item->_projectItem != group->_projectItem) &&
		parent() != nullptr)
	{
		setModel(item, group->_model);
	}
}

void NGM::Model::ResourceGroupItem::move(int from, ResourceGroupItem *group,
										 int to)
{
	ResourceBaseItem *item;
	if (_model)
	{
		assert(!_model->sort());
		_model->beginMove(index(), from, from, group->index(), to);
		item = _children[from];
		_children.erase(_children.begin() + from);
		if (group == this && from < to)
		{
			--to;
		}
		group->_children.insert(group->_children.begin() + to, item);
		item->_parent = group;
		_model->endMove();
	}
	else
	{
		item = _children[from];
		_children.erase(_children.begin() + from);
		group->_children.insert(group->_children.begin() + to, item);
		item->_parent = group;
	}
	_flags &= ~IsSorted;
	if ((item->_model != group->_model ||
		 item->_projectItem != group->_projectItem) &&
		parent() != nullptr)
	{
		setModel(item, group->_model);
	}
}

void NGM::Model::ResourceGroupItem::remove(int position, int count)
{
	for (int i = 0; i != count; ++i)
	{
		delete _children[position + i];
	}
	if (_model)
	{
		_model->beginRemove(index(), position, position + count - 1);
		_children.erase(_children.begin() + position,
						_children.begin() + position + count - 1);
		_model->endRemove();
	}
	else
	{
		_children.erase(_children.begin() + position,
						_children.begin() + position + count - 1);
	}
}

NGM::Model::ResourceGroupItem *NGM::Model::ResourceGroupItem::toGroupItem()
{
	return this;
}

bool NGM::Model::ResourceGroupItem::canContain(ResourceBaseItem *other)
{
	if (other->_container == nullptr || other->_container == this)
	{
		return true;
	}
	ResourceGroupItem *parent = _parent;
	while (parent != nullptr)
	{
		if (other->_container == parent)
		{
			return true;
		}
		parent = parent->_parent;
	}
	return false;
}

void NGM::Model::ResourceGroupItem::setModel(ResourceBaseItem *item,
	ResourceItemModel *model) const
{
	item->_model = model;
	if (!item->toGroupItem())
	{
		return;
	}
	std::stack<ResourceGroupItem*> stack;
	stack.push(item->toGroupItem());
	ResourceGroupItem *group;
	while (!stack.empty())
	{
		group = stack.top();
		stack.pop();

		for (ResourceItemIterator i = group->_children.begin();
			 i != group->_children.end(); ++i)
		{
			(*i)->_model = model;
			if ((*i)->toGroupItem())
			{
				stack.push((*i)->toGroupItem());
			}
		}
	}
}

void NGM::Model::ResourceGroupItem::setProjectItem(ResourceBaseItem *item,
	ResourceProjectItem *projectItem) const
{
	item->_projectItem = projectItem;
	if (!item->toGroupItem())
	{
		return;
	}
	std::stack<ResourceGroupItem*> stack;
	stack.push(item->toGroupItem());
	ResourceGroupItem *group;
	while (!stack.empty())
	{
		group = stack.top();
		stack.pop();

		for (ResourceItemIterator i = group->_children.begin();
			 i != group->_children.end(); ++i)
		{
			(*i)->_projectItem = projectItem;
			if ((*i)->toGroupItem())
			{
				stack.push((*i)->toGroupItem());
			}
		}
	}
}

void NGM::Model::ResourceGroupItem::sortChildren()
{
	std::stack<ResourceGroupItem*> stack;
	ResourceGroupItem *group;
	stack.push(this);
	while (!stack.empty())
	{
		group = stack.top();
		stack.pop();

		if (!(group->_flags & (NoSort | IsSorted)))
		{
			std::sort(group->_children.begin(), group->_children.end(),
					  &ResourceBaseItem::lessThan);
			group->_flags |= IsSorted;
		}

		for (ResourceItemIterator i = group->_children.begin();
			 i != group->_children.end(); ++i)
		{
			if ((*i)->toGroupItem())
			{
				stack.push((*i)->toGroupItem());
			}
		}
	}
}
