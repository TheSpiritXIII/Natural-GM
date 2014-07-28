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
#include "Library.hpp"
#include "PluginDepr.hpp"
#include <QStringBuilder>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QFormLayout>
#include <QTabWidget>
#include <QSplitter>
#include <QLabel>

NGM::Widget::PluginDialog::PluginDialog(QSet<Core::Library *> *plugins,
	QWidget *parent) : QDialog(parent, Qt::Window), _plugins(plugins)
{
	_authorsLabel = new QLabel();
	_authorsLabel->setTextFormat(Qt::PlainText);
	_versionLabel = new QLabel();
	_versionLabel->setTextFormat(Qt::PlainText);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);

	QTabBar *tabBar = new QTabBar();
	tabBar->addTab(tr("Installed"));
	tabBar->addTab(tr("Available"));
	tabBar->setExpanding(false);
	tabBar->setDocumentMode(true);

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
	QLabel *label = new QLabel(tr("Version:"));
	font = _versionLabel->font();
	font.setBold(true);
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
	_updateButton = new QPushButton(tr("Check for Updates"));
	_updateButton->setEnabled(false);
	pluginButtonLayout->addWidget(_updateButton);
	pluginButtonLayout->addStretch(1);
	_uninstallButton = new QPushButton(tr("Uninstall"));
	pluginButtonLayout->addWidget(_uninstallButton);

	infoLayout->addLayout(detailsLayout);
	label = new QLabel(tr("Plugin Description:"));
	label->setTextFormat(Qt::PlainText);
	label->setFont(font);
	infoLayout->addWidget(label);
	_descriptionEdit = new QPlainTextEdit();
	_descriptionEdit->setReadOnly(true);
	infoLayout->addWidget(_descriptionEdit);
	infoLayout->addLayout(pluginButtonLayout);

	contentWidget->addTab(infoWidget, tr("Information"));

	QTableWidget *tableWidget = new QTableWidget(0, 2);
	tableWidget->setHorizontalHeaderLabels({tr("Enabled"), tr("Name")});
	tableWidget->horizontalHeader()->setStretchLastSection(true);

	contentSplitter->addWidget(tableWidget);
	contentSplitter->addWidget(contentWidget);
	contentSplitter->setCollapsible(0, false);
	contentSplitter->setContentsMargins(
		style()->pixelMetric(QStyle::PM_LayoutLeftMargin),
		style()->pixelMetric(QStyle::PM_LayoutTopMargin),
		style()->pixelMetric(QStyle::PM_LayoutRightMargin), 0);

	QHBoxLayout *buttonLayout = new QHBoxLayout();
	buttonLayout->setContentsMargins(
		style()->pixelMetric(QStyle::PM_LayoutLeftMargin),
		style()->pixelMetric(QStyle::PM_LayoutTopMargin),
		style()->pixelMetric(QStyle::PM_LayoutRightMargin),
		style()->pixelMetric(QStyle::PM_LayoutBottomMargin));
	buttonLayout->addWidget(new QPushButton(tr("Install Plugin")));
	buttonLayout->addWidget(new QPushButton(tr("Open Plugin Folder")));
	QProgressBar *downloadProgress = new QProgressBar();
	downloadProgress->setRange(0, 0);
	downloadProgress->setTextVisible(false);
	downloadProgress->setVisible(false);
	buttonLayout->addWidget(downloadProgress, 1);
	buttonLayout->addStretch();

	QPushButton *button = new QPushButton(tr("Close"));
	buttonLayout->addWidget(button);
	connect(button, &QPushButton::clicked, this, &PluginDialog::close);

	layout->addWidget(tabBar);
	layout->addWidget(contentSplitter);
	layout->addLayout(buttonLayout);

	if (_plugins->size() != 0)
	{
		const API::Plugin *plugin = (*_plugins->begin())->plugin;
		_titleLabel->setText(plugin->name);
		_authorsLabel->setText(plugin->authors);
		API::Version version = plugin->version;
		_versionLabel->setText(QString::number(version.major) % QChar('.') %
			QString::number(version.minor) % QChar('.') %
			QString::number(version.revision));
		_descriptionEdit->setPlainText(plugin->description);
		if ((*_plugins->begin())->library == nullptr)
		{
			_uninstallButton->setEnabled(false);
		}
	}
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

