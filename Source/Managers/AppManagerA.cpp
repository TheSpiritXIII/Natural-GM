/**
 *  @file AppManagerA.cpp
 *	@brief Deals with actions and windows.
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
#include "ResourceItemModel.hpp"
#include "AppManager.hpp"
#include "ResourceWindow.hpp"
#include <QToolBar>
#include <QMenuBar>
#include <QKeyEvent>

#include "ProgressEvent.hpp"
#include "StatusBar.hpp"

namespace NGM
{
	namespace Manager
	{
		Widget::ResourceWindow *AppManager::createWindow()
		{
			Widget::ResourceWindow *window = new Widget::ResourceWindow(this);
			if (!_iconManager.applicationIcon()->isNull())
			{
				window->setWindowIcon(*_iconManager.applicationIcon());
			}

			QToolBar *fileBar = new QToolBar(tr("File"), window);
			fileBar->addAction(_actions[IconManager::NewProject]);
			fileBar->addAction(_actions[IconManager::OpenProject]);
			fileBar->addSeparator();
			fileBar->addAction(_actions[IconManager::Save]);
			fileBar->addAction(_actions[IconManager::SaveAll]);
			window->addToolBar(fileBar);

			QToolBar *clipboardBar = new QToolBar(tr("Clipboard"), window);
			clipboardBar->addAction(_actions[IconManager::Cut]);
			clipboardBar->addAction(_actions[IconManager::Copy]);
			clipboardBar->addAction(_actions[IconManager::Paste]);
			clipboardBar->addSeparator();
			clipboardBar->addAction(_actions[IconManager::Undo]);
			clipboardBar->addAction(_actions[IconManager::Redo]);
			clipboardBar->addSeparator();
			clipboardBar->addAction(_actions[IconManager::ZoomIn]);
			clipboardBar->addAction(_actions[IconManager::ZoomOut]);
			clipboardBar->addAction(_actions[IconManager::Zoom]);
			window->addToolBar(clipboardBar);

			QMenu *fileMenu = new QMenu(tr("&File"), window);
			fileMenu->addAction(_actions[IconManager::NewProject]);
			fileMenu->addAction(_actions[IconManager::OpenProject]);
			fileMenu->addAction(_actions[IconManager::SaveProject]);
			fileMenu->addAction(_actions[IconManager::SaveProjectAs]);
			fileMenu->addAction(_actions[IconManager::SaveProjectAll]);
			fileMenu->addSeparator();
			fileMenu->addAction(_actions[IconManager::Save]);
			fileMenu->addAction(_actions[IconManager::SaveAll]);
			fileMenu->addAction(_actions[IconManager::SaveAs]);
			fileMenu->addSeparator();
			fileMenu->addAction(_actions[IconManager::Close]);
			fileMenu->addAction(_actions[IconManager::CloseAll]);
			fileMenu->addSeparator();
			fileMenu->addAction(_actions[IconManager::Import]);
			fileMenu->addAction(_actions[IconManager::Export]);
			fileMenu->addSeparator();
			fileMenu->addAction(_actions[IconManager::PageSetup]);
			fileMenu->addAction(_actions[IconManager::Print]);
			fileMenu->addSeparator();
			fileMenu->addAction(_actions[IconManager::Exit]);

			QMenu *editMenu = new QMenu(tr("&Edit"), window);
			editMenu->addAction(_actions[IconManager::Undo]);
			editMenu->addAction(_actions[IconManager::Redo]);
			editMenu->addSeparator();
			editMenu->addAction(_actions[IconManager::Cut]);
			editMenu->addAction(_actions[IconManager::Copy]);
			editMenu->addAction(_actions[IconManager::Paste]);
			editMenu->addSeparator();
			editMenu->addAction(_actions[IconManager::SelectAll]);
			editMenu->addSeparator();
			editMenu->addAction(_actions[IconManager::ZoomIn]);
			editMenu->addAction(_actions[IconManager::ZoomOut]);
			editMenu->addAction(_actions[IconManager::Zoom]);
			editMenu->addSeparator();
			editMenu->addAction(_actions[IconManager::FindReplace]);

			QMenu *buildMenu = new QMenu(tr("&Build"), window);
			buildMenu->addAction(_actions[IconManager::Build]);
			buildMenu->addAction(_actions[IconManager::BuildAll]);
			buildMenu->addSeparator();
			buildMenu->addAction(_actions[IconManager::Rebuild]);
			buildMenu->addAction(_actions[IconManager::RebuildAll]);
			buildMenu->addSeparator();
			buildMenu->addAction(_actions[IconManager::Clean]);
			buildMenu->addAction(_actions[IconManager::CleanAll]);

			QMenu *debugMenu = new QMenu(tr("&Debug"), window);
			debugMenu->addAction(_actions[IconManager::Run]);
			debugMenu->addAction(_actions[IconManager::Debug]);
			debugMenu->addAction(_actions[IconManager::Stop]);
			debugMenu->addSeparator();
			debugMenu->addAction(_actions[IconManager::StepOver]);
			debugMenu->addAction(_actions[IconManager::StepInto]);

			QMenu *pluginsMenu = new QMenu(tr("&Plugins"), window);
			pluginsMenu->addAction(_actions[IconManager::Plugins]);
			pluginsMenu->addSeparator();

			QMenu *settingsMenu = new QMenu(tr("&Settings"), window);
			settingsMenu->addAction(_actions[IconManager::Layout]);
			settingsMenu->addAction(_actions[IconManager::Preferences]);

			QMenu *helpMenu = new QMenu(tr("&Help"), window);
			helpMenu->addAction(_actions[IconManager::About]);

			QMenuBar *menuBar = new QMenuBar(window);
			menuBar->addMenu(fileMenu);
			menuBar->addMenu(editMenu);
			menuBar->addMenu(buildMenu);
			menuBar->addMenu(debugMenu);
			menuBar->addMenu(pluginsMenu);
			menuBar->addMenu(settingsMenu);
			menuBar->addMenu(helpMenu);
			window->setMenuBar(menuBar);

			window->setIconSize(QSize(16, 16));
			window->show();
			_windows.append(window);
			emit windowCreated(window);
			return nullptr;
		}

		bool AppManager::addAction(const QString &name, QAction *action)
		{
			QMap<QString, QAction*>::iterator i = _pluginActions.find(name);
			if (i != _pluginActions.end())
			{
				return false;
			}
			_pluginActions.insert(name, action);
			return true;
		}

		void AppManager::reloadActionIcons()
		{
			QIcon *icons =  _iconManager.actionIcons;
			for (size_t i = 0; i != IconManager::ActionSize; ++i)
			{
				_actions[i]->setIcon(icons[i]);
			}
		}

		void AppManager::processKeyPress(QKeyEvent *event)
		{
			// Pure modifiers not allowed.
			if (event->isAutoRepeat() || event->key() == Qt::Key_Shift ||
				event->key() == Qt::Key_Control || event->key() == Qt::Key_Alt ||
				event->key() == Qt::Key_Meta)
			{
				return;
			}

			QKeySequence sequence(event->key() | event->modifiers());
			for (size_t i = 0; i != IconManager::ActionSize; ++i)
			{
				if (_actions[i]->shortcut().matches(sequence) == QKeySequence::ExactMatch)
				{
					event->accept();
					_actions[i]->trigger();
					return;
				}
			}
		}
	}
}

// REMOVE
#include <QDebug>

void NGM::Manager::AppManager::customEvent(QEvent *event)
{
	switch(static_cast<uint16_t>(event->type()))
	{
	case Event::ProgressMaxEvent::id:
	{
		Event::ProgressMaxEvent *progressEvent =
				static_cast<Event::ProgressMaxEvent*>(event);
		for (QList<Widget::ResourceWindow*>::iterator i = _windows.begin();
			 i != _windows.end(); ++i)
		{
			(*i)->statusBar()->setProgressShow(progressEvent->value());
		}
		break;
	}
	case Event::ProgressValueEvent::id:
	{
		Event::ProgressValueEvent *progressEvent =
				static_cast<Event::ProgressValueEvent*>(event);
		for (QList<Widget::ResourceWindow*>::iterator i = _windows.begin();
			 i != _windows.end(); ++i)
		{
			(*i)->statusBar()->setProgressValue(progressEvent->value());
		}
		break;
	}
	case Event::ProgressTextEvent::id:
	{
		Event::ProgressTextEvent *progressEvent =
				static_cast<Event::ProgressTextEvent*>(event);
		for (QList<Widget::ResourceWindow*>::iterator i = _windows.begin();
			 i != _windows.end(); ++i)
		{
			(*i)->statusBar()->setProgressText(progressEvent->text());
		}
		break;
	}
	default:
		qDebug() << "Unknown custom event.";
		break;
	}
}

void NGM::Manager::AppManager::enableProjectActions()
{
	_actions[IconManager::NewProject]->setEnabled(true);
	_actions[IconManager::OpenProject]->setEnabled(true);
	_actions[IconManager::Save]->setEnabled(true);
	_actions[IconManager::SaveAs]->setEnabled(true);
	_actions[IconManager::SaveAll]->setEnabled(true);
	_actions[IconManager::SaveProject]->setEnabled(true);
	_actions[IconManager::SaveProjectAs]->setEnabled(true);
	_actions[IconManager::SaveProjectAll]->setEnabled(true);

	_model->insert(_serializerThread.item());
	removePostedEvents(this, Event::ProgressMaxEvent::id);
	removePostedEvents(this, Event::ProgressTextEvent::id);
	removePostedEvents(this, Event::ProgressValueEvent::id);
	//removePostedEvents(this, Event::ProgressMaxEvent);
	//removePostedEvents(this, Event::ProgressMaxEvent);
	for (QList<Widget::ResourceWindow*>::iterator i = _windows.begin();
		 i != _windows.end(); ++i)
	{
		(*i)->statusBar()->setReady();
	}
	emit serializerDone();
}

void NGM::Manager::AppManager::disableProjectActions()
{
	_actions[IconManager::NewProject]->setEnabled(false);
	_actions[IconManager::OpenProject]->setEnabled(false);
	_actions[IconManager::Save]->setEnabled(false);
	_actions[IconManager::SaveAs]->setEnabled(false);
	_actions[IconManager::SaveAll]->setEnabled(false);
	_actions[IconManager::SaveProject]->setEnabled(false);
	_actions[IconManager::SaveProjectAs]->setEnabled(false);
	_actions[IconManager::SaveProjectAll]->setEnabled(false);
	emit serializerStart();
}
