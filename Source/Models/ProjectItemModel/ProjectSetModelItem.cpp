/**
 *  @file ProjectSetModelItem.cpp
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
#include "ProjectSetModelItem.hpp"
#include "Project.hpp"

NGM::Model::ProjectSetModelItem::ProjectSetModelItem(const QString &text,
	const QVector<Resource::Project *> &projects) :	_parent(nullptr),
	_text(text), _projects(projects), _size(projects.size()) {}

namespace NGM
{
	Model::ProjectSetModelItem::~ProjectSetModelItem()
	{
		for (QVector<ProjectSetModelItem*>::iterator i = _children.begin();
			 i != _children.end(); ++i)
		{
			delete (*i);
		}
	}

	int Model::ProjectSetModelItem::childNumber() const
	{
		for (int i = 0; i != _parent->childCount(); ++i)
		{
			if (_parent->_children[i] == this)
			{
				return i;
			}
		}
		return -1;
	}

	void Model::ProjectSetModelItem::setSearch(const QString &search)
	{
		_search = search;
		for (int i = 0; i != _children.size(); ++i)
		{
			_children[i]->setSearch(search);
		}
		search_();
	}

	bool Model::ProjectSetModelItem::hasSearch() const
	{
		if (_size == 0)
		{
			for (int i = 0; i != _children.size(); ++i)
			{
				if (_children[i]->hasSearch())
				{
					return true;
				}
			}
		}
		else
		{
			return true;
		}
		return false;
	}

	void Model::ProjectSetModelItem::searchItems(QVector<Resource::Project *>
												 *list) const
	{
		for (int i = 0; i != _size; ++i)
		{
			list->append(_projects[i]);
		}
		for (int i = 0; i != _children.size(); ++i)
		{
			_children.at(i)->searchItems(list);
		}
	}

	void Model::ProjectSetModelItem::search_()
	{
		_size = 0;
		bool last = true;
		Resource::Project *swap;

		for (int i = 0; i != _projects.size(); ++i)
		{
			if ((static_cast<char>(_projects[i]->projectType) &
				  static_cast<char>(_display)) != 0 &&
			   (_projects[i]->name.contains(_search, Qt::CaseInsensitive) ||
			   _projects[i]->description.contains(_search, Qt::CaseInsensitive)))
			{
				if (!last)
				{
					_projects[_size] = _projects[i];
					_projects[i] = swap;
					swap = _projects[++_size];
				}
				else
				{
					++_size;
				}
			}
			else
			{
				last = false;
			}
		}
	}

	void Model::ProjectSetModelItem::setDisplay(Display display)
	{
		_display = display;
		for (int i = 0; i != _children.size(); ++i)
		{
			_children[i]->setDisplay(display);
		}
		search_();
	}
}
