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
#pragma once
#include <QDialog>

class QLabel;
class QPushButton;
class QPlainTextEdit;

namespace NGM
{
	namespace Core
	{
		struct Library;
	}
	namespace Widget
	{
		/**************************************************//*!
		*  @brief  Provides a graphical interface to viewing
		*          plugin information.
		******************************************************/
		class PluginDialog : public QDialog
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*  @brief  Creates a dialog with the given parent.
			******************************************************/
			PluginDialog(QSet<Core::Library*> *plugins, QWidget *parent = 0);

		private slots:
			void tabChanged(int index);
		private:
			QLabel *_titleLabel;
			QLabel *_versionLabel;
			QLabel *_authorsLabel;
			QLabel *_iconLabel;
			QPlainTextEdit *_descriptionEdit;
			QPushButton *_uninstallButton;
			QPushButton *_updateButton;
			QSet<Core::Library*> *_plugins;
		};
	}
}
