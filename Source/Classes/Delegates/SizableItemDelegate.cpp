/**
 *  @file SizableItemDelegate.cpp
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
#include "SizableItemDelegate.hpp"

NGM::Delegate::SizableItemDelegate::SizableItemDelegate(const QSize &size,
	QObject *parent) : QStyledItemDelegate(parent), _size(size) {}

void NGM::Delegate::SizableItemDelegate::paint(QPainter *painter,
	const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyleOptionViewItem optionView = option;
	optionView.showDecorationSelected = true;
	QStyledItemDelegate::paint(painter, optionView, index);
}