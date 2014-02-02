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
		*	@see	ResourceBaseItem::Flags
		******************************************************/
		typedef uint8_t ResourceItemFlags;

		/**************************************************//*!
		*	@brief	An item that stores only its parent. This
		*			class can only be used with
		*			ResourceItemModel.
		******************************************************/
		class ResourceBaseItem
		{
		public:

			/**************************************************//*!
			*	@brief	Item flags used by multiple items.
			******************************************************/
			enum Flags
			{
				NotMovable		=	0x01,	/*!< For groups and content items:
												Whether or not the user is able
												to move this item around. */
				NotRenamable	=	0x02,	/*!< For groups and content items:
												Whether or not the item can be
												renamed by the user. */
				NoAdd			=	0x04,	/*!< For groups: Whether or not the
												users can create new content
												items. */
				NoSort			=	0x08,	/*!< For groups: If true, then this
												group will not be sorted, even
												if sorting is enabled. */
				IsSorted		=	0x10,	/*!< For groups: Whether or not the
												all children are sorted
												already. */
				CreateGroups	=	0x20,	/*!< For groups: Whether or not the
												user can create sub groups. If
												true, then the user cannot
												insert any other groups that are
												not containers of this group.*/
				Temporary		=	0x40,	/*!< For project items: Denotes that
												the project is saved in a
												temporary location. */
				Modified		=	0x80,	/*!< For project items: Whether or
												not the items were rearranged
												and should later ask the user to
												save changes. */
				IsStatic		=	NotMovable | NotRenamable
			};

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
			*	@brief	Returns the item flags.
			*	@see	Flags
			******************************************************/
			inline ResourceItemFlags flags() const
			{
				return _flags;
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
			*	@brief	Returns the container item. If there is
			*			a container item, then this item must
			*			have that item as a parent somewhere.
			******************************************************/
			inline ResourceGroupItem *container() const
			{
				return _container;
			}

			/**************************************************//*!
			*	@brief	Returns the root project item.
			******************************************************/
			inline ResourceProjectItem *projectItem() const
			{
				return _projectItem;
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
			*			less than the right item. This is done
			*			case insensitive.
			******************************************************/
			static bool lessThan(const ResourceBaseItem *lhs,
								 const ResourceBaseItem *rhs);

			/**************************************************//*!
			*	@brief	Returns whether or not the left item is
			*			less than the right string. This is done
			*			case insensitive.
			******************************************************/
			static bool lessThanText(const ResourceBaseItem *lhs,
									 const QString &rhs);

		protected:

			friend class ResourceItemModel;
			friend class ResourceGroupItem;

			/**************************************************//*!
			*	@brief	Creates an item with flags.
			******************************************************/
			ResourceBaseItem(ResourceItemFlags flags = IsSorted,
							 ResourceGroupItem *container = nullptr);

			/**************************************************//*!
			*	@brief	Creates an item with a name and flags.
			******************************************************/
			ResourceBaseItem(const QString &text,
							 ResourceItemFlags flags = IsSorted,
							 ResourceGroupItem *container = nullptr);

			/**************************************************//*!
			*	@brief	Other item types are responsible for
			*			deleting their data. This does nothing.
			******************************************************/
			virtual ~ResourceBaseItem();

			/**************************************************//*!
			*	@brief	Stores the parent. This is defined by
			*			the parent item during insertions.
			******************************************************/
			ResourceGroupItem *_parent;

			/**************************************************//*!
			*	@brief	Holds the topmost root item.
			******************************************************/
			ResourceProjectItem *_projectItem;

			/**************************************************//*!
			*	@brief	Stores the container item (usually the
			*			same as the parent).
			******************************************************/
			ResourceGroupItem *_container;

			/**************************************************//*!
			*	@brief	Stores the containing model.
			******************************************************/
			ResourceItemModel *_model;

			/**************************************************//*!
			*	@brief	Stores the item flags.
			******************************************************/
			ResourceItemFlags _flags;

		private:

			/**************************************************//*!
			*	@brief	Stores the display name of this item.
			******************************************************/
			QString _text;
		};
	}
}

#endif // NGM__RESOURCEBASEITEM__HPP
