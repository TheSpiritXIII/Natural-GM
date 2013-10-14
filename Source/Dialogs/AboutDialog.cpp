/**
 *  @file AboutDialog.cpp
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
#include "AboutDialog.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QPushButton>
#include <QLabel>
#include <QFile>

namespace NGM
{
	namespace Dialog
	{
		AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent, Qt::WindowCloseButtonHint)
		{
			setWindowTitle(tr("About Natural GM"));
			QVBoxLayout *layout = new QVBoxLayout(this);

			QWidget *widget = new QWidget(this);
			QHBoxLayout *contents = new QHBoxLayout(widget);

			if (QFile::exists("naturalgm.png"))
			{
				QLabel *label = new QLabel(this);
				label->setPixmap(QPixmap("naturalgm.png"));
				contents->addWidget(label);
			}

			contents->addWidget(new QLabel(tr("<h1>Natural GM</h1>Copyright (c) 2013 Daniel Hrabovcak"), this));
			contents->setMargin(0);

			layout->addWidget(widget);
			QPushButton *button = new QPushButton(tr("Close"), this);
			button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
			layout->addWidget(button);
			layout->setAlignment(button, Qt::AlignRight);

			connect(button, &QPushButton::pressed, [this]()
			{
				close();
			});
		}
	}
}
