/**
 *  @file ResourceBaseItem.hpp
 *  @section License
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
#ifndef NGM__RESOURCEBASEITEM__HPP
#define NGM__RESOURCEBASEITEM__HPP
#include <QString>
#include <QModelIndex>

namespace NGM
{
	namespace Model
	{
		class ResourceItemModel;
		class ResourceGroupItem;
		class ResourceProjectItem;
		class ResourceContentItem;

		/**************************************************//*!
		*	@brief	An item that stores only its parent. This
		*			class can only be used with
		*			ResourceItemModel.
		******************************************************/
		class ResourceBaseItem
		{
		public:

			/**************************************************//*!
			*	@brief	Other item types are responsible for
			*			deleting their data. This does nothing.
			******************************************************/
			virtual ~ResourceBaseItem();

			/**************************************************//*!
			*	@brief	Returns the text of this item.
			******************************************************/
			inline QString text() const
			{
				return _text;
			}

			/**************************************************//*!
			*	@brief	Sets a new text name for this item.
			******************************************************/
			inline void setText(const QString &name)
			{
				_text = name;
			}

			/**************************************************//*!
			*	@brief	The model index of the item.
			******************************************************/
			const QModelIndex index() const;

			/**************************************************//*!
			*	@brief	Returns the row number inside its parent.
			*			If the item cannot be found, then -1 is
			*			returned.
			******************************************************/
			int childNumber() const;

			/**************************************************//*!
			*	@brief	Returns the item that stores this item as
			*			a child, or nullptr if this item is not
			*			currently stored in anything.
			******************************************************/
			inline ResourceGroupItem *parent() const
			{
				return _parent;
			}

			/**************************************************//*!
			*	@brief	Returns the root project item.
			******************************************************/
			inline ResourceProjectItem *root() const
			{
				return _project;
			}

			/**************************************************//*!
			*	@brief	Returns a safe cast to a content item.
			******************************************************/
			virtual ResourceContentItem *toContentItem();

			/**************************************************//*!
			*	@brief	Returns a safe cast to a project item.
			******************************************************/
			virtual ResourceProjectItem *toProjectItem();

			/**************************************************//*!
			*	@brief	Returns a safe cast to a group item.
			******************************************************/
			virtual ResourceGroupItem *toGroupItem();

			/**************************************************//*!
			*	@brief	Returns whether or not the left item is
			*			less than the right one.
			******************************************************/
			static bool lessThan(const ResourceBaseItem *lhs,
								 const ResourceBaseItem *rhs);

		protected:

			friend class ResourceItemModel;
			friend class ResourceGroupItem;

			/**************************************************//*!
			*	@brief	Creates an item with a root and a name.
			*			The root should be the topmost root of
			*			this item.
			******************************************************/
			ResourceBaseItem(const QString &text = QString());

			/**************************************************//*!
			*	@brief	Stores the parent. This is defined by
			*			the parent item during insertions.
			******************************************************/
			ResourceGroupItem *_parent;

			/**************************************************//*!
			*	@brief	Holds the topmost root item.
			******************************************************/
			ResourceProjectItem *_project;

			/**************************************************//*!
			*	@brief	Stores the containing model.
			******************************************************/
			ResourceItemModel *_model;

		private:

			/**************************************************//*!
			*	@brief	Stores the display name of this item.
			******************************************************/
			QString _text;
		};
	}
}

#endif // NGM__RESOURCEBASEITEM__HPP
