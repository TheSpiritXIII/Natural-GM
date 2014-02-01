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

NGM::Widget::StatusBar::StatusBar(QWidget *parent) : QStatusBar(parent)
{
	_label = new QLabel(this);
	_progress = new QProgressBar(this);
	_progress->setTextVisible(false);
	addWidget(_progress);
	addWidget(_label, 1);
	setReady();
}

void NGM::Widget::StatusBar::setReady()
{
	_progress->setVisible(false);
	_label->setVisible(true);
	_label->setText(tr("Ready."));
}

void NGM::Widget::StatusBar::setProgressShow(int max)
{
	_progress->setValue(0);
	_progress->setMaximum(max);
	_progress->setVisible(true);
	_label->setVisible(true);
	_label->setText(QString());
}

void NGM::Widget::StatusBar::setProgressValue(int value)
{
	_progress->setValue(value);
}

void NGM::Widget::StatusBar::setProgressText(const QString &text)
{
	_label->setText(text);
}

void NGM::Widget::StatusBar::setWidgets()
{
	if (!_progress->isVisible())
	{
		_label->setVisible(false);
	}
}

