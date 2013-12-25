/**
 *  @file AboutDialog.cpp
 *  @section License
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
#include "AboutDialog.hpp"
#include <QStringBuilder>
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
			QHBoxLayout *layout = new QHBoxLayout(this);

			if (QFile::exists("about.png"))
			{
				QLabel *label = new QLabel(this);
				label->setPixmap(QPixmap("about.png"));
				layout->addWidget(label);
			}

			QWidget *widget = new QWidget(this);
			QVBoxLayout *contents = new QVBoxLayout(widget);

			QWidget *textWidget = new QWidget(this);
			QVBoxLayout *textLayout = new QVBoxLayout(textWidget);
			contents->addWidget(textWidget);

			QLabel *label = new QLabel(QStringLiteral("Natural GM "), this);
			label->setTextFormat(Qt::PlainText);
			QPalette palette = label->palette();
			QFont font = label->font();

			palette.setColor(QPalette::WindowText, QColor(32, 176, 72));
			label->setPalette(palette);

			font.setPointSize(font.pointSize() * 3);
			font.setWeight(QFont::Bold);
			label->setFont(font);
			textLayout->addWidget(label);

			label = new QLabel(tr("Version 0.01"), this);
			label->setTextFormat(Qt::PlainText);
			font.setPointSize(label->font().pointSize() - 1);
			label->setFont(font);
			palette.setColor(QPalette::WindowText, QColor(128, 128, 128));
			label->setPalette(palette);
			textLayout->addWidget(label);

			textLayout->setMargin(0);
			textLayout->setSpacing(0);

			QString copyright = QStringLiteral("Copyright © 2013-2014 Daniel Hrabovcak. ");
			label = new QLabel(copyright % tr("All Rights Reserved."), this);
			label->setTextFormat(Qt::PlainText);
			label->setWordWrap(true);
			contents->addWidget(label);

			label = new QLabel(tr("Natural GM is an extendible, open source IDE for creating games."
								  " <a href='www.naturalgm.zymichost.com'>Learn more!</a>"), this);
			label->setTextFormat(Qt::RichText);
			label->setOpenExternalLinks(true);
			label->setWordWrap(true);
			contents->addWidget(label);

			label = new QLabel(tr("Want to get involved? "
				"<a href=\"www.naturalgm.zymichost.com\">Find out how!</a>"), this);
			label->setTextFormat(Qt::RichText);
			label->setOpenExternalLinks(true);
			contents->addWidget(label);

			layout->addWidget(widget);
			setFixedSize(sizeHint());
		}
	}
}
