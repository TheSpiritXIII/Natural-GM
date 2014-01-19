/**
 *  @file SortGroupProxyModel.hpp
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
#ifndef NGM__SORTGROUPPROXYMODEL__H
#define NGM__SORTGROUPPROXYMODEL__H
#include <QSortFilterProxyModel>
#include <QTreeView>

namespace NGM
{
	namespace Model
	{
		/**************************************************//*!
		*	@brief	A model that has the ability to sort the
		*			contents of a model. If any children are
		*			accepted, then their groups will be too,
		*			and if any groups are accept, their
		*			children will be accepted as well.
		******************************************************/
		class SortGroupProxyModel : public QSortFilterProxyModel
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Creates a proxy with a parent.
			******************************************************/
			SortGroupProxyModel(QObject *parent = 0);

		protected:

			/**************************************************//*!
			*	@brief	Filters rows to include searched items
			*			and children of searched groups.
			******************************************************/
			virtual bool filterAcceptsRow(int row, const QModelIndex &parent) const;
		};
	}
}

#endif // NGM__SORTGROUPPROXYMODEL__H
