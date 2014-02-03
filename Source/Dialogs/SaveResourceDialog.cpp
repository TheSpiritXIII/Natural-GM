/**
 *  @file SaveResourceDialog.cpp
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
#include "SaveResourceDialog.hpp"
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>

NGM::Dialog::SaveResourceDialog::SaveResourceDialog(QWidget *parent) :
	QDialog(parent)
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);

	QLabel *label = new QLabel(tr("Check the items you wish to save. Unchecked "
		"resources will be discarded."), this);
	label->setTextFormat(Qt::PlainText);

	QWidget *buttonWidget = new QWidget(this);
	QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);
	buttonLayout->setMargin(0);

	QPushButton *saveButton = new QPushButton(tr("Save"), this);
	connect(saveButton, &QPushButton::pressed,
			this, &SaveResourceDialog::saveButtonPressed);
	QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);
	connect(cancelButton, &QPushButton::pressed, this, &QDialog::reject);

	buttonLayout->addStretch(1);
	buttonLayout->addWidget(saveButton);
	buttonLayout->addWidget(cancelButton);

	layout->addWidget(label);
	layout->addWidget(buttonWidget);
}

void NGM::Dialog::SaveResourceDialog::saveButtonPressed()
{
	// TODO Add content.
	accept();
}
