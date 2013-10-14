/**
 *  @file HighlightWidget.hpp
 *	@section License
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
#include "HighlightWidget.hpp"

namespace NGM
{
	namespace Widget
	{
		HighlightWidget::HighlightWidget(QWidget *parent) : QWidget(parent), highlightColor(palette().highlight().color())
		{
			highlightColor.setAlpha(128);
			//setPalette(Qt::transparent);
			setAttribute(Qt::WA_TransparentForMouseEvents);
		}

		void HighlightWidget::paintEvent(QPaintEvent *event)
		{
			QPainter painter(this);
			painter.fillRect(0, 0, width(), height(), highlightColor);
		}
	}
}
