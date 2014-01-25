/**
 *  @file ResourceModelEvent.cpp
 *	@section License
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
#include "ResourceModelEvent.hpp"

NGM::Event::ResourceModelRemoveEvent::ResourceModelRemoveEvent(
	Model::ResourceGroupItem *parent, int row, int count) :
	QEvent(id), _parent(parent), _row(row), _count(count) {}

NGM::Event::ResourceModelInsertEvent::ResourceModelInsertEvent(
	Model::ResourceBaseItem *insert, Model::ResourceGroupItem *parent, int row,
	int count) : QEvent(id), _insert(insert), _parent(parent), _row(row),
	_count(count) {}
