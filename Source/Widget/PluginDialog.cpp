/*-
 *  Copyright (c) 2014 Daniel Hrabovcak
 *
 *  This program is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or (at your
 *  option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 *  for more details.
**/
#include "PluginDialog.hpp"
#include <QFormLayout>
#include <QLabel>

NGM::Widget::PluginDialog::PluginDialog(QWidget *parent) :
  QDialog(parent, Qt::Window)
{
	QFormLayout *layout = new QFormLayout(this);
	layout->addWidget(nameLabel = new QLabel(tr("Name:")));
	layout->addWidget(versionLabel = new QLabel(tr("Version:")));
	layout->addWidget(authorsLabel = new QLabel(tr("Authors:")));
	layout->addWidget(descriptionLabel = new QLabel(tr("Description:")));
}
