/**
 *  @file SortRootProxyModel.hpp
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
#ifndef NGM__SORTROOTPROXYMODEL__H
#define NGM__SORTROOTPROXYMODEL__H
#include "SortGroupProxyModel.hpp"

namespace NGM
{
	namespace Model
	{
		/**************************************************//*!
		*	@brief	Role for icons when item is expanded. It
		*			takes the default value of 96.
		******************************************************/
		const int DecorationExpandRole = Qt::UserRole + 64; // 64 to avoid clashing.

		/**************************************************//*!
		*	@brief	A model that has the ability to change
		*			the display view when an item is expanded
		*			or collapsed. In addition, when sorted it
		*			always keeps the root. Roots can also be
		*			set as a priority, which makes them bold.
		*
		* The class requests different roles from the source
		* model. If an item is expanded, it requests a
		* Natural::DecorationExpandRole, otherwise, it
		* requests a Qt::DecorationRole.
		*
		* In addition, if the priority row is deleted, then
		* the priority is changed to the one after it, if
		* possible.
		******************************************************/
		class SortRootProxyModel : public SortGroupProxyModel
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Creates a proxy with a parent.
			******************************************************/
			SortRootProxyModel(QObject *parent = 0);

			/**************************************************//*!
			*	@brief	Sets the source model and installs a slot
			*			for watching deletions.
			******************************************************/
			virtual void setSourceModel(QAbstractItemModel *source);

			/**************************************************//*!
			*	@brief	Requests data from the source model.
			******************************************************/
			virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

			/**************************************************//*!
			*	@brief	Stores the tree view. The tree view must
			*			display this proxy model.
			******************************************************/
			virtual void setSourceView(QTreeView *sourceView);

			/**************************************************//*!
			*	@brief	Returns the current source view.
			******************************************************/
			QTreeView *sourceView() const;

			/**************************************************//*!
			*	@brief	Set the priority index (it is bolded).
			*			Setting this to any value outside the
			*			children range will not work.
			******************************************************/
			inline void setPriority(int index)
			{
				if (rowCount() < index)
				{
					_priority = index;
				}
			}

			/**************************************************//*!
			*	@brief	Returns the current index that has
			*			priority. This is 0 by default.
			******************************************************/
			inline int priority() const
			{
				return _priority;
			}

		protected:

			/**************************************************//*!
			*	@brief	Filters rows to include searched items
			*			and children of searched groups.
			******************************************************/
			bool filterAcceptsRow(int row, const QModelIndex &parent) const;

		private slots:

			/**************************************************//*!
			*	@brief	Checks if the priority row was deleted.
			*			Does not check arguments.
			******************************************************/
			void updatePriority(const QModelIndex &, int, int);

		private:

			/**************************************************//*!
			*	@brief	Stores the tree view of the source model.
			******************************************************/
			QTreeView *_sourceView;

			/**************************************************//*!
			*	@brief	Stores the priority root index.
			******************************************************/
			int _priority;
		};
	}
}

#endif // NGM__SORTROOTPROXYMODEL__H
