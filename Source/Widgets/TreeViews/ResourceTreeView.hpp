/**
 *  @file ResourceTreeView.hpp
 *	@section License
 *
 *      Copyright (C) 2013-2014 Daniel Hrabovcak
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
#ifndef NGM__RESOURCETREEVIEW__HPP
#define NGM__RESOURCETREEVIEW__HPP
#include <QTreeView>

namespace NGM
{
	namespace Model
	{
		class ResourceBaseItem;
		class ResourceItemModel;
	}
	namespace Widget
	{
		/**************************************************//*!
		*	@brief	A tree view that is best for displaying
		*			and editing the main resource item.
		******************************************************/
		class ResourceTreeView : public QTreeView
		{
			Q_OBJECT

		public:
			
			/**************************************************//*!
			*	@brief	Creates a view with the indicated parent
			*			and item model.
			******************************************************/
			ResourceTreeView(Model::ResourceItemModel *model,
				QWidget *parent = 0);

		protected:
			
			/**************************************************//*!
			*	@brief	Displays a context menu relative to the
			*			current selected resource item.
			******************************************************/
			void contextMenuEvent(QContextMenuEvent *);

			/**************************************************//*!
			*	@brief	When no items are clicked, selections are
			*			cleaered.
			******************************************************/
			void mousePressEvent(QMouseEvent *);

		private slots:

			/**************************************************//*!
			*	@brief	Sorts the selected groups.
			******************************************************/
			void sortSelected() const;

			/**************************************************//*!
			*	@brief	Expands the selected groups.
			******************************************************/
			void expandSelected();

			/**************************************************//*!
			*	@brief	Collapses the selected groups.
			******************************************************/
			void collapseSelected();

			/**************************************************//*!
			*	@brief	Adds a new group to the selected group.
			*			The new group is queued for renaming
			*			right away.
			******************************************************/
			void addGroupToSelected();

			/**************************************************//*!
			*	@brief	Opens an editor for the selected items.
			******************************************************/
			void renameSelected();

			/**************************************************//*!
			*	@brief	Closes the selected project. A
			*			confirmation is asked by the user if
			*			changes were made.
			******************************************************/
			void closeSelectedProject();

			/**************************************************//*!
			*	@brief	Sets the current active project to the
			*			selected project.
			******************************************************/
			void setActiveSelectedProject();

		private:

			/**************************************************//*!
			*	@brief	Stores the model, for changing
			*			properties.
			******************************************************/
			Model::ResourceItemModel *_model;

			/**************************************************//*!
			*	@brief	Contains the last selected item.
			******************************************************/
			Model::ResourceBaseItem *_selected;
		};
	}
}

#endif // NGM__RESOURCETREEVIEW__HPP
