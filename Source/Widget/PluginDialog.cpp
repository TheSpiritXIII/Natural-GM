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
#include "TabDisplayWidget.hpp"
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QFormLayout>
#include <QTabWidget>
#include <QSplitter>
#include <QTabBar>
#include <QLabel>

NGM::Widget::PluginDialog::PluginDialog(QWidget *parent) :
  QDialog(parent, Qt::Window)
{
	_nameLabel = new QLabel();
	_nameLabel->setTextFormat(Qt::PlainText);
	_authorsLabel = new QLabel();
	_authorsLabel->setTextFormat(Qt::PlainText);
	_versionLabel = new QLabel();
	_versionLabel->setTextFormat(Qt::PlainText);

	QVBoxLayout *layout = new QVBoxLayout(this);

	//TabDisplayWidget *tabWidget = new TabDisplayWidget();
	QTabBar *tabBar = new QTabBar();//tabWidget->tabBar();
	tabBar->setExpanding(false);
	tabBar->addTab(tr("Installed"));
	tabBar->addTab(tr("Available"));

	QSplitter *contentSplitter = new QSplitter();
	QTabWidget *contentWidget = new QTabWidget();

	QWidget *infoWidget = new QWidget();
	QVBoxLayout *infoLayout = new QVBoxLayout(infoWidget);

	QHBoxLayout *detailsLayout = new QHBoxLayout();

	QFormLayout *infoForm = new QFormLayout();
	_titleLabel = new QLabel(tr("Super Awesome Plugin"));
	_titleLabel->setTextFormat(Qt::PlainText);
	QFont font = _titleLabel->font();
	font.setPointSizeF(font.pointSizeF() * 1.5f);
	font.setBold(true);
	_titleLabel->setFont(font);
	infoForm->addRow(_titleLabel);
	QLabel *label = new QLabel(tr("Name:"));
	label->setTextFormat(Qt::PlainText);
	font = _nameLabel->font();
	font.setBold(true);
	label->setFont(font);
	infoForm->addRow(label, _nameLabel);
	label = new QLabel(tr("Version:"));
	label->setTextFormat(Qt::PlainText);
	label->setFont(font);
	infoForm->addRow(label, _versionLabel);
	label = new QLabel(tr("Authors:"));
	label->setTextFormat(Qt::PlainText);
	label->setFont(font);
	infoForm->addRow(label, _authorsLabel);

	//_iconLabel = new QLabel();
	detailsLayout->addLayout(infoForm, 1);
	//detailsLayout->addWidget(_iconLabel);

	QHBoxLayout *pluginButtonLayout = new QHBoxLayout();
	pluginButtonLayout->addWidget(new QPushButton(tr("Settings")));
	pluginButtonLayout->addWidget(new QPushButton(tr("Check for Updates")));
	pluginButtonLayout->addStretch(1);
	QPushButton *button = new QPushButton(tr("Uninstall"));
	connect(button, &QPushButton::clicked, this, &PluginDialog::close);
	pluginButtonLayout->addWidget(button);

	infoLayout->addLayout(detailsLayout);
	label = new QLabel(tr("Plugin Description:"));
	label->setTextFormat(Qt::PlainText);
	label->setFont(font);
	infoLayout->addWidget(label);
	infoLayout->addWidget(new QPlainTextEdit());
	infoLayout->addLayout(pluginButtonLayout);

	contentWidget->addTab(infoWidget, tr("Information"));

	QTableWidget *tableWidget = new QTableWidget(0, 2);
	tableWidget->setHorizontalHeaderLabels({tr("Enabled"), tr("Name")});
	tableWidget->horizontalHeader()->setStretchLastSection(true);

	contentSplitter->addWidget(tableWidget);
	contentSplitter->addWidget(contentWidget);
	contentSplitter->setCollapsible(0, false);

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(new QPushButton(tr("Install Plugin")));
	buttonLayout->addWidget(new QPushButton(tr("Open Plugin Folder")));
	QProgressBar *downloadProgress = new QProgressBar();
	downloadProgress->setRange(0, 0);
	downloadProgress->setTextVisible(false);
	downloadProgress->setVisible(false);
	buttonLayout->addWidget(downloadProgress, 1);
	buttonLayout->addStretch();
	buttonLayout->addWidget(new QPushButton(tr("Close")));

	layout->addWidget(tabBar);
	layout->addWidget(contentSplitter);
	//layout->addWidget(tabWidget);
	//tabWidget->setWidget(contentSplitter);
	layout->addLayout(buttonLayout);
}

void NGM::Widget::PluginDialog::tabChanged(int index)
{
	if (index == 0)
	{

	}
	else
	{

	}
}

