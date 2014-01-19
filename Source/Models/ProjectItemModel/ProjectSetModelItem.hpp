/**
 *  @file ProjectSetModelItem.hpp
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
#ifndef NGM__PROJECTSETMODELITEM__HPP
#define NGM__PROJECTSETMODELITEM__HPP
#include <QString>
#include <QVector>

namespace NGM
{
	namespace Resource
	{
		class Project;
	}
	namespace Model
	{
		/**************************************************//*!
		*	@brief	Values that decide how projects are
		*			displayed. By default, everything is
		*			displayed, but you can limit to projects
		*			with groups of files and/or projects with
		*			single files.
		******************************************************/
		enum class Display : char
		{
			Both		=	0x3,
			Groups		=	0x1,
			Files		=	0x2
		};

		/**************************************************//*!
		*	@brief	An item that contains sets of projects.
		*			More specifically, the set should contain
		*			projects of the same category.
		******************************************************/
		class ProjectSetModelItem
		{
		public:

			/**************************************************//*!
			*	@brief	Initializes the item by setting the
			*			projects set. All projects in the set
			*			should be the same category.
			*	@param	text The display text. Should either be
			*			the category or subcategory.
			*	@param	projects The project set to store.
			******************************************************/
			ProjectSetModelItem(const QString &text = QString(),
								const QVector<Resource::Project*> &projects =
									QVector<Resource::Project*>());

			/**************************************************//*!
			*	@brief	Deletes all children.
			******************************************************/
			~ProjectSetModelItem();

			/**************************************************//*!
			*	@brief	Appends a child into this item.
			******************************************************/
			inline void addChild(ProjectSetModelItem *item)
			{
				_children.append(item);
				item->_parent = this;
			}

			/**************************************************//*!
			*	@brief	Returns the number of children this item
			*			contains.
			******************************************************/
			int childCount() const
			{
				return _children.size();
			}

			/**************************************************//*!
			*	@brief	Returns the child at the indicated row.
			*	@see	childCount();
			******************************************************/
			inline ProjectSetModelItem *child(int row) const
			{
				return _children.at(row);
			}

			/**************************************************//*!
			*	@brief	Returns the parent, or nullptr if it has
			*			none.
			******************************************************/
			inline ProjectSetModelItem *parent() const
			{
				return _parent;
			}

			/**************************************************//*!
			*	@brief	Returns the row number that this item
			*			is inside its parent. -1 is returned if
			*			this object is not found.
			******************************************************/
			int childNumber() const;

			/**************************************************//*!
			*	@brief	Returns the display text.
			******************************************************/
			inline QString text() const
			{
				return _text;
			}

			/**************************************************//*!
			*	@brief	Returns the search string.
			******************************************************/
			inline QString searchText() const
			{
				return _search;
			}

			/**************************************************//*!
			*	@brief	Validates current projects by the
			*			indicated search requirement. Both the
			*			names and descriptions of each set is
			*			checked against the search string.
			*	@see	searchItems()
			******************************************************/
			void setSearch(const QString &search);

			/**************************************************//*!
			*	@brief	Returns true whether there are currently
			*			any valid items. Items are invalid when
			*			they do not meet the search criteria.
			*			This function also checks children.
			*	@see	setSearch()
			******************************************************/
			bool hasSearch() const;

			/**************************************************//*!
			*	@brief	Sets the indicated vector of project
			*			based on the current search requirements.
			*	@see	setSearch()
			******************************************************/
			void searchItems(QVector<Resource::Project*> *list) const;

			/**************************************************//*!
			*	@brief	Returns the new of valid items.
			*	@see	hasSearch()
			******************************************************/
			inline int searchCount() const
			{
				return _size;
			}

			/**************************************************//*!
			*	@brief	Sets the display requirements. This is
			*			used when searching.
			******************************************************/
			void setDisplay(Display display);

		private:

			/**************************************************//*!
			*	@brief	Validates items.
			******************************************************/
			void search_();

			/**************************************************//*!
			*	@brief	Contains all children.
			******************************************************/
			QVector<ProjectSetModelItem*> _children;

			/**************************************************//*!
			*	@brief	Stores this object's parent.
			******************************************************/
			ProjectSetModelItem *_parent;

			/**************************************************//*!
			*	@brief	Stores the display text.
			******************************************************/
			QString _text;

			/**************************************************//*!
			*	@brief	Stores projects for this item.
			******************************************************/
			QVector<Resource::Project*> _projects;

			/**************************************************//*!
			*	@brief	Stores the amount of items that meet the
			*			search criteria.
			*	@see	setSearch();
			******************************************************/
			int _size;

			/**************************************************//*!
			*	@brief	Stores the display type for searching.
			******************************************************/
			Display _display;

			/**************************************************//*!
			*	@brief	The previously used search string.
			******************************************************/
			QString _search;
		};
	}
}

#endif // NGM__PROJECTSETMODELITEM__HPP
