/**
 *  @file SizableItemDelegate.hpp
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
#ifndef NGM__SIZABLEITEMDELEGATE__HPP
#define NGM__SIZABLEITEMDELEGATE__HPP
#include <QStyledItemDelegate>

namespace NGM
{
	namespace Delegate
	{
		/**************************************************//*!
		*	@brief	A styled item delegate for drawing fixed
		*			sized items.
		******************************************************/
		class SizableItemDelegate : public QStyledItemDelegate
		{
		public:

			/**************************************************//*!
			*	@brief	Creates a delegate with the indicated
			*			item width, item height and parent.
			******************************************************/
			SizableItemDelegate(const QSize &size, QObject *parent = 0);

			/**************************************************//*!
			*	@brief	Return the fixed item size.
			*	@see	setSize()
			******************************************************/
			inline QSize sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const
			{
				return _size;
			}

			/**************************************************//*!
			*	@brief	Sets the current fixed item size.
			******************************************************/
			inline void setSize(const QSize &size)
			{
				_size = size;
			}

			/**************************************************//*!
			*	@brief	Paints a styled item, with the hint that
			*			the selection is decorated (for showing
			*			the whole selection rectanlge).
			******************************************************/
			void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

		private:

			/**************************************************//*!
			*	@brief	Stores the fixed size.
			******************************************************/
			QSize _size;
		};
	}
}

#endif // NGM__SIZABLEITEMDELEGATE__HPP
