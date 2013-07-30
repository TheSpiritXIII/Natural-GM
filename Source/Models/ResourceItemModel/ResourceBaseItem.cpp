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
#include <QDebug>

namespace NGM
{
	namespace Model
	{
		ResourceBaseItem::ResourceBaseItem(const QString &name) : _root(nullptr), _parent(nullptr), _model(nullptr), _data(name)
		{
			// Empty.
		}

		QVariant ResourceBaseItem::data() const
		{
			return _data;
		}

		const QModelIndex ResourceBaseItem::index()
		{
			if (_parent != NULL)
			{
				return _model->index(row(), 0, _parent->index());
			}
			return QModelIndex();
		}

		int ResourceBaseItem::row() const
		{
			// To do.
			if (_parent)
			{
				ResourceGroupItem *p = _parent->toResourceGroupItem();
				for(size_t i = 0; i < p->_children.size(); ++i)
				{
					if (p->_children[i] == const_cast<ResourceBaseItem*>(this))
					{
						return i;
					}
				}
			}
			return 0;
		}

		ResourceBaseItem *ResourceBaseItem::parent()
		{
			return _parent;
		}

		ResourceContentItem *ResourceBaseItem::toResourceContentItem()
		{
			return nullptr;
		}

		ResourceProjectItem *ResourceBaseItem::toResourceProjectItem()
		{
			return nullptr;
		}

		ResourceGroupItem *ResourceBaseItem::toResourceGroupItem()
		{
			return nullptr;
		}

		ResourceProjectItem *ResourceBaseItem::root()
		{
			return _root;
		}
	}
}
