/**
 *  @file ResourceModelEvent.hpp
 *	@section License
 *
 *      Copyright (C) 2013-2014 Daniel Hrabovcak
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
#ifndef NGM__RESOURCEMODELINSERT__HPP
#define NGM__RESOURCEMODELINSERT__HPP
#include "ResourceGroupItem.hpp"
#include <QEvent>

namespace NGM
{
	namespace Event
	{
		/**************************************************//*!
		*	@brief	An an event that tells the application to
		*			remove an item from the resource model.
		******************************************************/
		class ResourceModelRemoveEvent : public QEvent
		{
		public:

			/**************************************************//*!
			*	@brief	The unique identifier for this event
			*			type.
			******************************************************/
			static const QEvent::Type id = static_cast<QEvent::Type>(
						QEvent::User + 2001);

			/**************************************************//*!
			*	@brief	Sets the parent and the count of items to
			*			remove in parent starting at the row.
			******************************************************/
			ResourceModelRemoveEvent(Model::ResourceGroupItem *parent, int row,
									 int count);

			/**************************************************//*!
			*	@brief	Returns the parent item where items are
			*			removed from.
			******************************************************/
			inline Model::ResourceGroupItem *parent() const
			{
				return _parent;
			}

			/**************************************************//*!
			*	@brief	Returns the item index to remove.
			******************************************************/
			inline int row() const
			{
				return _row;
			}

			/**************************************************//*!
			*	@brief	Returns the number of items to remove.
			******************************************************/
			inline int count() const
			{
				return _count;
			}

		private:

			/**************************************************//*!
			*	@brief	The parent where items are removed from.
			******************************************************/
			Model::ResourceGroupItem *_parent;

			/**************************************************//*!
			*	@brief	The item index to remove.
			******************************************************/
			int _row;

			/**************************************************//*!
			*	@brief	The number of items to remove.
			******************************************************/
			int _count;
		};

		/**************************************************//*!
		*	@brief	An an event that tells the application to
		*			insert an item to the resource model.
		******************************************************/
		class ResourceModelInsertEvent : public QEvent
		{
		public:

			/**************************************************//*!
			*	@brief	The unique identifier for this event
			*			type.
			******************************************************/
			static const QEvent::Type id = static_cast<QEvent::Type>(
						QEvent::User + 2002);

			/**************************************************//*!
			*	@brief	Sets the parent and the count of items to
			*			insert into the parent starting at row.
			*	@param	insert This may be more than one item.
			*			If count is more than one, the pointer
			*			arithmetic is done to find the next item.
			******************************************************/
			ResourceModelInsertEvent(Model::ResourceBaseItem *insert,
				Model::ResourceGroupItem *parent, int row, int count = 0);

			/**************************************************//*!
			*	@brief	Returns the item that is inserted.
			******************************************************/
			inline Model::ResourceBaseItem *insert() const
			{
				return _insert;
			}

			/**************************************************//*!
			*	@brief	Returns the parent item where items are
			*			inserted into.
			******************************************************/
			inline Model::ResourceGroupItem *parent() const
			{
				return _parent;
			}

			/**************************************************//*!
			*	@brief	Returns the item index to insert to.
			******************************************************/
			inline int row() const
			{
				return _row;
			}

			/**************************************************//*!
			*	@brief	Returns the number of items to insert.
			******************************************************/
			inline int count() const
			{
				return _count;
			}

		private:

			/**************************************************//*!
			*	@brief	The item to insert.
			******************************************************/
			Model::ResourceBaseItem *_insert;

			/**************************************************//*!
			*	@brief	The parent where items are inserted to.
			******************************************************/
			Model::ResourceGroupItem *_parent;

			/**************************************************//*!
			*	@brief	The item index to insert.
			******************************************************/
			int _row;

			/**************************************************//*!
			*	@brief	The number of items to insert.
			******************************************************/
			int _count;
		};
	}
}

#endif // NGM__RESOURCEMODELINSERT__HPP
