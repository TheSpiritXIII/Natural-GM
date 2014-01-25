/**
 *  @file Serializer.cpp
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
#include "Serializer.hpp"
#include "ProgressEvent.hpp"
#include "ResourceProjectItem.hpp"
#include "ResourceModelEvent.hpp"
#include <QApplication>

void NGM::Resource::Serializer::setProgressText(const QString &text) const
{
	qApp->postEvent(qApp, new Event::ProgressTextEvent(text));
}

void NGM::Resource::Serializer::setProgressValue(int value) const
{
	qApp->postEvent(qApp, new Event::ProgressValueEvent(value));
}

void NGM::Resource::Serializer::setProgressMax(int value) const
{
	qApp->postEvent(qApp, new Event::ProgressMaxEvent(value));
}

void NGM::Resource::Serializer::removeItem(
	const Model::ResourceGroupItem *parent, int row, int count) const
{
	qApp->postEvent(qApp, new Event::ResourceModelRemoveEvent(
						const_cast<Model::ResourceGroupItem*>(parent),
						row, count));
}

void NGM::Resource::Serializer::insertItem(Model::ResourceBaseItem *item,
	const Model::ResourceGroupItem *parent, int row, int count) const
{
	qApp->postEvent(qApp, new Event::ResourceModelInsertEvent(
						item, const_cast<Model::ResourceGroupItem*>(parent),
						row, count));
}

void NGM::Resource::Serializer::layoutCreate(
		NGM::Model::ResourceProjectItem *) const {}

void NGM::Resource::Serializer::layoutLoad(
		NGM::Model::ResourceProjectItem *) const {}

void NGM::Resource::Serializer::layoutSave(
		NGM::Model::ResourceProjectItem *) const {}

void NGM::Resource::Serializer::layoutReload(
		const Model::ResourceProjectItem *) const {}
