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
#include <QDebug>

namespace NGM
{
	namespace Model
	{
		ResourceGroupItem::~ResourceGroupItem()
		{
			for (auto &i : _children)
			{
				delete i;
			}
		}

		int ResourceGroupItem::count() const
		{
			return _children.size();
		}

		ResourceBaseItem *ResourceGroupItem::child(int row)
		{
			return _children[row];
		}

		void ResourceGroupItem::append(ResourceBaseItem *item)
		{
			_model->beginInsert(index(), _children.size(), _children.size());
			item->_parent = this;
			item->_model = _model;
			item->_root = _root;
			_children.push_back(item);
			_model->endInsert();
		}

		void ResourceGroupItem::append(std::vector<ResourceBaseItem*> items)
		{
			_model->beginInsert(index(), _children.size(), _children.size()+items.size());
			for(auto i = items.begin(); i != items.end(); ++i)
			{
				(*i)->_parent = this;
				(*i)->_model = _model;
				(*i)->_root = _root;
			}
			_children.insert(_children.end(), items.begin(), items.end());
			_model->endInsert();
		}

		void ResourceGroupItem::pop(int count)
		{
			_model->beginRemove(index(), _children.size()-1, _children.size()-1);
			for(int i = 0; i < count; ++i)
			{
				delete _children.back();
				_children.pop_back();
			}
			_model->endRemove();
		}

		void ResourceGroupItem::remove(int row, int count)
		{
			_model->beginRemove(index(), row, row+count);
			for(int i = row; i < row+count; ++i)
			{
				delete _children.at(row);
				_children.erase(_children.begin()+row);
			}
			_model->endRemove();
		}

		std::vector<ResourceBaseItem*> ResourceGroupItem::take(int row, int count)
		{
			_model->beginRemove(index(), row, row+count);
			std::vector<ResourceBaseItem*> taken;
			for(int i = row; i < row+count; ++i)
			{
				_children[i]->_model = nullptr;
				_children[i]->_parent = nullptr;
				_children[i]->_root = nullptr;
				taken.push_back(_children[i]);
			}
			_children.erase(_children.begin()+row, _children.begin()+row+count);
			_model->endRemove();
			return taken;
		}

		void ResourceGroupItem::insert(ResourceBaseItem *item, int row)
		{
			_model->beginInsert(index(), row, row);
			item->_parent = this;
			item->_model = _model;
			item->_root = _root;
			_children.insert(_children.begin()+row, item);
			_model->endInsert();
		}

		void ResourceGroupItem::insert(std::vector<ResourceBaseItem*> items, int row)
		{
			_model->beginInsert(index(), row, row+items.size()-1);
			for(auto i = items.begin(); i != items.end(); ++i)
			{
				(*i)->_parent = this;
				(*i)->_model = _model;
				(*i)->_root = _root;
			}
			_children.insert(_children.begin()+row, items.begin(), items.end());
			_model->endInsert();
		}

		ResourceGroupItem *ResourceGroupItem::toGroupItem()
		{
			return this;
		}
	}
}
