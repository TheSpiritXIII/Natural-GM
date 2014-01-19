/**
 *  @file ProjectFilterProxyModel.hpp
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
#ifndef NGM__PROJECTFILTERPROXYMODEL__HPP
#define NGM__PROJECTFILTERPROXYMODEL__HPP
#include "SortGroupProxyModel.hpp"
#include "ProjectSetItemModel.hpp"

namespace NGM
{
	namespace Model
	{
		/**************************************************//*!
		*	@brief	A model that displays a source
		*			ProjectSetItemModel with special
		*			filtering to display only items with
		*			matching search criteria and different
		*			priorities.
		******************************************************/
		class ProjectFilterProxyModel : public SortGroupProxyModel
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Sets a parent object.
			******************************************************/
			ProjectFilterProxyModel(QObject *parent = 0);

		protected:

			/**************************************************//*!
			*	@brief	Filters rows to include searched items
			*			and children of searched groups. Also
			*			removes items that do not have any
			*			Projects attached.
			******************************************************/
			bool filterAcceptsRow(int row, const QModelIndex &parent) const;

			/**************************************************//*!
			*	@brief	Normal sorting, except with "All" and
			*			"Recent" always placed at the top.
			******************************************************/
			bool lessThan(const QModelIndex & left,
						  const QModelIndex & right) const;

		private:

			/**************************************************//*!
			*	@brief	Returns the project set model.
			******************************************************/
			inline const ProjectSetItemModel* getProjectSetModelSource() const
			{
				return static_cast<const ProjectSetItemModel*>(sourceModel());
			}
		};
	}
}

#endif // NGM__PROJECTFILTERPROXYMODEL__HPP
