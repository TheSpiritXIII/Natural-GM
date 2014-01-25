/**
 *  @file PriorityStatusBar.hpp
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
#include "StatusBar.hpp"
#include <QProgressBar>
#include <QLabel>

void NGM::Widget::StatusBar::setProgressLabel(int min, int max)
{
	_progress->setMinimum(min);
	_progress->setMaximum(max);
	_progress->setVisible(true);
	_label->setVisible(true);
	/*connect(&_messenger, &StatusBarMessenger::setText,
			_label, &QLabel::setText, Qt::QueuedConnection);
	connect(&_messenger, &StatusBarMessenger::setProgress,
			_label, &QLabel::setText, Qt::QueuedConnection);*/
}

NGM::Widget::StatusBarMessenger *NGM::Widget::StatusBar::messenger()
{

	return &_messenger;
}

