/**
 *  @file BasicItem.cpp
 *  @brief Defines a basic item class, capable of holding a single text.
 *
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
#include "BasicItem.hpp"
#include "BasicModel.hpp"
#include "ResourceItem.hpp"

namespace NGM
{
	namespace Model
	{
		BasicItem::BasicItem(const QString &data) :  _parent(NULL), _data(data) {}

		BasicItem::~BasicItem()
		{
			while(!_children.empty())
			{
				delete _children.back();
				_children.pop_back();
			}
		}

		const QModelIndex BasicItem::index()
		{
			if (_parent != NULL)
			{
				return _model->index(row(), 0, _parent->index());
			}
			return QModelIndex();
		}

		BasicItem *BasicItem::child(int row)
		{
			return _children[row];
		}

		int BasicItem::count() const
		{
			return _children.size();
		}

		QVariant BasicItem::data() const
		{
			return _data;
		}

		BasicItem *BasicItem::parent()
		{
			return _parent;
		}

		int BasicItem::row() const
		{
			if (_parent)
			{
				for(size_t i = 0; i < _parent->_children.size(); ++i)
				{
					if (_parent->_children[i] == const_cast<BasicItem*>(this))
					{
						return i;
					}
				}
			}
			return 0;
		}

		void BasicItem::append(BasicItem *item)
		{
			_model->beginInsert(index(), _children.size(), _children.size());
			item->_parent = this;
			item->_model = _model;
			_children.push_back(item);
			_model->endInsert();
		}

		void BasicItem::append(std::vector<BasicItem *> items)
		{
			_model->beginInsert(index(), _children.size(), _children.size()+items.size());
			for(auto i = items.begin(); i != items.end(); ++i)
			{
				(*i)->_parent = this;
				(*i)->_model = _model;
			}
			_children.insert(_children.end(), items.begin(), items.end());
			_model->endInsert();
		}

		void BasicItem::pop(int count)
		{
			_model->beginRemove(index(), _children.size()-1, _children.size()-1);
			for(int i = 0; i < count; ++i)
			{
				delete _children.back();
				_children.pop_back();
			}
			_model->endRemove();
		}

		void BasicItem::remove(int row, int count)
		{
			_model->beginRemove(index(), row, row+count);
			for(int i = row; i < row+count; ++i)
			{
				delete _children.at(row);
				_children.erase(_children.begin()+row);
			}
			_model->endRemove();
		}

		std::vector<BasicItem*> BasicItem::take(int row, int count)
		{
			_model->beginRemove(index(), row, row+count);
			std::vector<BasicItem*> taken;
			for(int i = row; i < row+count; ++i)
			{
				_children[i]->_model = NULL;
				_children[i]->_parent = NULL;
				taken.push_back(_children[i]);
			}
			_children.erase(_children.begin()+row, _children.begin()+row+count);
			_model->endRemove();
			return taken;
		}

		void BasicItem::insert(BasicItem *item, int row)
		{
			_model->beginInsert(index(), row, row);
			_children.insert(_children.begin()+row, item);
			_model->endInsert();
		}

		void BasicItem::insert(std::vector<BasicItem*> items, int row)
		{
			_model->beginInsert(index(), row, row+items.size()-1);
			_children.insert(_children.begin()+row, items.begin(), items.end());
			_model->endInsert();
		}

		ResourceItem *BasicItem::toResourceItem()
		{
			return 0;
		}
	}
}
