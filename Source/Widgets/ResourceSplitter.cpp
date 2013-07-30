/**
 *  @file ResourceSplitter.cpp
 *
 *  @section License
 *
 *      Copyright (C) 2013 Daniel Hrabovcak
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
#include "ResourceSplitter.hpp"

namespace NGM
{
	namespace Widget
	{
		ResourceSplitter::ResourceSplitter(QWidget *parent) : QSplitter(parent) {}

		void ResourceSplitter::resourceOpen(Model::ResourceBaseItem *resource, bool active)
		{
			if (count() == 0 || active == false)
			{
				ResourceTab *tab = new ResourceTab(this);
				tab->resourceOpen(resource);
				addWidget(tab);
				current	= tab;
			}
			else
			{
				current->resourceOpen(resource);
			}
		}
	}
}