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
#include <cassert>
#include <algorithm>
#include <stack>

// REMOVE
#include <QDebug>

NGM::Model::ResourceGroupItem::ResourceGroupItem(const QString &name) :
	ResourceBaseItem(name) {}

NGM::Model::ResourceGroupItem::~ResourceGroupItem()
{
	for (auto &i : _children)
	{
		delete i;
	}
}

void NGM::Model::ResourceGroupItem::sort()
{
	std::sort(_children.begin(), _children.end(),
			  &ResourceBaseItem::lessThan);
	for (ResourceItemIterator i = _children.begin();
		 i != _children.end(); ++i)
	{
		if ((*i)->toGroupItem())
		{
			(*i)->toGroupItem()->sort();
		}
	}
}

int NGM::Model::ResourceGroupItem::childPosition(
		const ResourceBaseItem *find) const
{
	if (_model && _model->sort())
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

void NGM::Model::ResourceGroupItem::insert(ResourceBaseItem *item)
{
	item->_parent = this;
	if (_model)
	{
		setData(item, _model, _project);
		if (_model->sort())
		{
			ResourceItemIterator i = std::lower_bound(_children.begin(),
				_children.end(), item, &ResourceBaseItem::lessThan);
			int position = i - _children.begin();
			_model->beginInsert(index(), position, position);
			_children.insert(i, item);
			if (item->toGroupItem())
			{
				item->toGroupItem()->sort();
			}
			_model->endInsert();
			return;
		}
	}
	int position = count();
	_model->beginInsert(index(), position, position);
	_children.append(item);
	_model->endInsert();
}

void NGM::Model::ResourceGroupItem::insert(ResourceBaseItem *item, int position)
{
	if (_model && !_model->sort() && item->root() == root())
	{
		setData(item, _model, _project);
		_model->beginInsert(index(), position, position);
		item->_parent = this;
		_children.insert(_children.begin() + position, item);
		_model->endInsert();
	}
}

void NGM::Model::ResourceGroupItem::move(int from, ResourceGroupItem *group)
{
	if (group->root() != root())
	{
		return;
	}
	ResourceBaseItem *item;
	ResourceItemIterator i;
	if (_model && _model->sort())
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
			group->_children.insert(to, item);
		}
		else
		{
			_model->beginMove(index(), from, from, group->index(), 1);
			group->_children.push_back(item);
		}
	}
	else
	{
		_model->beginMove(index(), from, from, group->index(), group->count());
		i = _children.begin() + from;
		item = *i;
		group->_children.append(item);
	}
	_children.erase(i);
	item->_parent = group;
	_model->endMove();
}

void NGM::Model::ResourceGroupItem::move(int from, ResourceGroupItem *group,
										 int to)
{
	if (_model && !_model->sort())
	{
		_model->beginMove(index(), from, from, group->index(), to);
		ResourceItemIterator i = _children.begin() + from;
		ResourceBaseItem *item = *i;
		// Insert first, in case group == this.
		group->_children.insert(group->_children.begin() + to, item);
		_children.erase(i);
		item->_parent = group;
		_model->endMove();
	}
}

void NGM::Model::ResourceGroupItem::remove(int position, int count)
{
	_model->beginRemove(index(), position, position + count - 1);
	_children.erase(_children.begin() + position,
					_children.begin() + position + count - 1);
	_model->endRemove();
}

NGM::Model::ResourceGroupItem *NGM::Model::ResourceGroupItem::toGroupItem()
{
	return this;
}

void NGM::Model::ResourceGroupItem::setData(ResourceBaseItem *item,
	ResourceItemModel *model, ResourceProjectItem *project) const
{
	if (!item->toGroupItem())
	{
		item->_model = model;
		item->_project = project;
		return;
	}
	std::stack<ResourceGroupItem*> stack;
	stack.push(item->toGroupItem());
	ResourceGroupItem *group;
	while (!stack.empty())
	{
		group = stack.top();
		group->_model = model;
		group->_project = project;
		for (ResourceItemIterator i = group->_children.begin();
			 i != group->_children.end(); ++i)
		{
			if ((*i)->toGroupItem())
			{
				stack.push((*i)->toGroupItem());
			}
			else
			{
				(*i)->_model = model;
				(*i)->_project = project;
			}
		}
		stack.pop();
	}
}
