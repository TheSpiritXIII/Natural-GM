/**
 *  @file ResourceProxyModel.hpp
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
#pragma once
#ifndef _NGM_RESOURCEPROXYMODEL__HPP
#define _NGM_RESOURCEPROXYMODEL__HPP
#include <QAbstractProxyModel>

namespace NGM
{
	namespace Model
	{
		class ResourceProjectItem;

		/**************************************************//*!
		*	@brief	A proxy model capable of storing the
		*			current active project and bolds it.
		******************************************************/
		class ResourceProxyModel : public QAbstractProxyModel
		{
		public:

			/**************************************************//*!
			*	@brief	Required for subclassing.
			******************************************************/
			QModelIndex mapFromSource(const QModelIndex & sourceIndex) const;

			/**************************************************//*!
			*	@brief	Required for subclassing.
			******************************************************/
			QModelIndex mapToSource(const QModelIndex & proxyIndex) const;

			/**************************************************//*!
			*	@brief	Returns the data at the specified index.
			*			This is mostly the same, except the
			*			active project is bolded.
			******************************************************/
			QVariant data(const QModelIndex & proxyIndex, int role = Qt::DisplayRole) const;

			/**************************************************//*!
			*	@brief	Sets the current active project item.
			******************************************************/
			inline void setActiveProjectItem(const ResourceProjectItem * item)
			{
				_activeProjectItem = item;
			}

			/**************************************************//*!
			*	@brief	Returns the current active project item.
			******************************************************/
			inline const ResourceProjectItem *activeProjectItem()
			{
				return _activeProjectItem;
			}

		private:

			/**************************************************//*!
			*	@brief	The current active project index.
			******************************************************/
			const ResourceProjectItem *_activeProjectItem;
		};
	}
}

#endif // _NGM_RESOURCEPROXYMODEL__HPP
