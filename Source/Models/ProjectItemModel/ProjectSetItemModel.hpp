/**
 *  @file ProjectSetItemModel.hpp
 *	@section License
 *
 *      Copyright (C) 2014 Daniel Hrabovcak
 *
 *      This file is part of the Natural GM IDE.
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
#ifndef NGM__PROJECTSETITEMMODEL__HPP
#define NGM__PROJECTSETITEMMODEL__HPP
#include "ProjectSetModelItem.hpp"
#include <QAbstractItemModel>
#include <QVector>

namespace NGM
{
	namespace Resource
	{
		class Project;
	}
	namespace Model
	{
		class ProjectItemModel;

		/**************************************************//*!
		*	@brief	Displays project categories. Requires to
		*			be inside a ProjectFilterProxyModel in
		*			order to display correctly.
		*
		* This model is specific to drawing all project
		* categories. It even two special items, an "All"
		* item that stores all projects and a "Recent" item
		* that preferably stores the user's last used items.
		******************************************************/
		class ProjectSetItemModel : public QAbstractItemModel
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Creates an item model with an icon and
			*			a parent. The icon supplied is displayed
			*			on every tree item. It is indended for
			*			it to be an empty icon, so that tree
			*			items are expanding to be larger.
			*	@param	recent The recent items that the user
			*			last used. These are displayed in a
			*			special item in bold.
			******************************************************/
			ProjectSetItemModel(QObject *parent = 0, QVector<Resource::Project*>
				recent = QVector<Resource::Project*>());

			~ProjectSetItemModel();

			/**************************************************//*!
			*	@brief	Returns the item index at the indicated
			*			row and parent.
			******************************************************/
			QModelIndex index(int row, int column = 0,
							  const QModelIndex &parent = QModelIndex()) const;

			/**************************************************//*!
			*	@brief	Returns the parent of the indicated
			*			index.
			******************************************************/
			QModelIndex parent(const QModelIndex & index) const;

			/**************************************************//*!
			*	@brief	Returns the number of rows at the
			*			indicated index.
			******************************************************/
			int rowCount(const QModelIndex & parent = QModelIndex()) const;

			/**************************************************//*!
			*	@brief	Always returns 1.
			******************************************************/
			int columnCount(const QModelIndex & parent = QModelIndex()) const;

			/**************************************************//*!
			*	@brief	Returns the project category on data and
			*			querys the icon manager for an icon.
			******************************************************/
			QVariant data(const QModelIndex &index,
						  int role = Qt::DisplayRole) const;

			/**************************************************//*!
			*	@brief	Always returns a text "Categories".
			******************************************************/
			QVariant headerData(int, Qt::Orientation,
								int role = Qt::DisplayRole) const;

			/**************************************************//*!
			*	@brief	Returns the flags (items are enabled
			*			is the only flag set).
			******************************************************/
			Qt::ItemFlags flags(const QModelIndex &index) const;

			/**************************************************//*!
			*	@brief	Returns true if the indicated parent
			*			index contains children.
			******************************************************/
			bool hasChildren(const QModelIndex &parent = QModelIndex()) const;

			/**************************************************//*!
			*	@brief	Adds a new child. This can only be done
			*			at the model creation. After the model
			*			has been internally initialized, this
			*			function has no effect on the view.
			******************************************************/
			inline void addChild(ProjectSetModelItem *item)
			{
				_root->addChild(item);
			}

			/**************************************************//*!
			*	@brief	Returns the number of items.
			******************************************************/
			inline int childCount() const
			{
				return _root->childCount();
			}

			/**************************************************//*!
			*	@brief	Returns the child in the indicated row.
			******************************************************/
			inline ProjectSetModelItem *child(int row) const
			{
				return _root->child(row);
			}

			/**************************************************//*!
			*	@brief	Returns whether or not this object has
			*			any recent items.
			******************************************************/
			inline bool hasRecent() const
			{
				return _recent->childCount() != 0;
			}

			/**************************************************//*!
			*	@brief	Returns whether or the indicated model
			*			index is storing the "Recent" item.
			******************************************************/
			bool isRecentItem(const QModelIndex &index) const;

			/**************************************************//*!
			*	@brief	Returns whether or the indicated model
			*			index is the "All" item.
			******************************************************/
			bool isAllItem(const QModelIndex &index) const;

			/**************************************************//*!
			*	@brief	Sets the model to search for items using
			*			the indicated display.
			*	@see	setSearch()
			******************************************************/
			void setDisplay(Display display) const;

			/**************************************************//*!
			*	@brief	Sets search criteria for items. All items
			*			are processed and the item search list
			*			is changed, so any item search lists
			*			must be refreshed after calling this
			*			function.
			*	@see	hasSearch()
			******************************************************/
			void setSearch(const QString &search);

			/**************************************************//*!
			*	@brief	Returns if the root row has any items
			*			that matched the last indicated search
			*			criteria.
			*	@see	setSearch()
			******************************************************/
			bool hasSearch(int row) const;

			/**************************************************//*!
			*	@brief	Sets the indicated project item model's
			*			item projects equal to the indicated
			*			index's current search projects.
			******************************************************/
			void setItemModel(const QModelIndex &index,
							  ProjectItemModel *model) const;

			/**************************************************//*!
			*	@brief	Casts the index into an item.
			******************************************************/
			inline ProjectSetModelItem *getItem(const QModelIndex &index) const
			{
				return static_cast<ProjectSetModelItem*>
						(index.internalPointer());
			}

		private:

			/**************************************************//*!
			*	@brief	Returns true if the row matches the
			*			"Recent" row, if there is a recent item.
			******************************************************/
			inline bool isRecentItemRow(int row) const
			{
				return (row == _root->childCount() + 1 &&
						_recent->childCount() != 0);
			}

			/**************************************************//*!
			*	@brief	Returns whether the row matches the "All"
			*			item row.
			******************************************************/
			inline bool isAllItemRow(int row) const
			{
				return (row == _root->childCount());
			}

			/**************************************************//*!
			*	@brief	Contains the root children.
			******************************************************/
			ProjectSetModelItem *_root;

			/**************************************************//*!
			*	@brief	Stores the user's recent projects.
			******************************************************/
			ProjectSetModelItem *_recent;
		};
	}
}

#endif // NGM__PROJECTSETITEMMODEL__HPP
