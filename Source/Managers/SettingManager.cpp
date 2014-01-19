/**
 *  @file SettingManager.cpp
 *  @section License
 *
 *      Copyright (C) 2013-2014 Daniel Hrabovcak
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
#include "SettingManager.hpp"
#include "IconManager.hpp"
#include "Global.hpp"
#include <QStandardPaths>
#include <QStringBuilder>
#include <QTextStream>
#include <QFile>
#ifndef NGM_PORTABLE
#include <QDir>
#endif


#include <QDebug>
#include <sstream>
using std::ostringstream;

static const char t_Header[]			=	"Natural GM Settings:";
static const char t_RecentFilesMax[]	=	"recentFilesMax\t\t\t";
static const char t_RecentFiles[]		=	"recentFiles\t\t\t\t";
static const char t_DefaultDirectory[]	=	"defaultDirectory\t\t";
static const char t_LastDirectory[]		=	"lastDirectory\t\t\t";
static const char t_ThemeName[]			=	"themeName\t\t\t\t";
static const char t_StyleName[]			=	"styleName\t\t\t\t";

NGM::Manager::SettingManager::SettingManager() : _iconManager(nullptr) {}

NGM::Manager::SettingManager::SettingManager(IconManager *iconManager) :
	_iconManager(iconManager), projectPreferences(0) {}

NGM::Manager::SettingManager::~SettingManager()
{
	if (_iconManager == nullptr)
	{
		return;
	}
#ifdef NGM_PORTABLE
	QFile file(QStringLiteral("config"));
#else
	QDir dir;
	dir.mkdir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
	QFile file(QStandardPaths::writableLocation(
		QStandardPaths::DataLocation) % QStringLiteral("/config"));
#endif
	if (file.open(QFile::WriteOnly))
	{
		ostringstream ss;
		ss << +_recentFilesMax;

		file.write("Natural GM Settings:\n");
		file.write(t_RecentFilesMax);
		file.write(ss.str().c_str());
		file.putChar('\n');
		file.write(t_RecentFiles);
		for (QStringList::iterator i = _recentFiles.begin();
			 i != _recentFiles.end(); ++i)
		{
			file.write(i->toUtf8().data());
			file.putChar(';');
		}
		file.putChar('\n');
		file.write(t_DefaultDirectory);
		file.write(_defaultDirectory.toUtf8());
		file.putChar('\n');
		file.write(t_LastDirectory);
		file.write(_lastDirectory.toUtf8());
		file.putChar('\n');
		file.write(t_ThemeName);
		file.write(_iconManager->theme().toUtf8());
		file.putChar('\n');
		file.write(t_StyleName);
		file.write(_styleName.toUtf8());
		file.putChar('\n');
	}
}

void NGM::Manager::SettingManager::load()
{
#ifdef NGM_PORTABLE
	QFile file(QStringLiteral("config"));
#else
	QFile file(QStandardPaths::writableLocation(
		QStandardPaths::DataLocation) % QStringLiteral("/config"));
#endif
	if (file.open(QFile::ReadOnly))
	{
		QByteArray bytes;
		bytes = file.readLine();
		if (strncmp(bytes.data(), t_Header, sizeof(t_Header) - 1) != 0)
		{
			return;
		}
		QString iconTheme;
		while (!file.atEnd())
		{
			bytes = file.readLine();
			if (strncmp(bytes.data(), t_RecentFilesMax,
						sizeof(t_RecentFilesMax) - 1) == 0)
			{
				_recentFilesMax = atoi(
							&bytes.data()[sizeof(t_RecentFilesMax) - 1]);
				qDebug() << _recentFilesMax;
			}
			else if (strncmp(bytes.data(), t_RecentFiles,
							 sizeof(t_RecentFiles) - 1) == 0)
			{
				int last = sizeof(t_RecentFiles);
				int pos = bytes.indexOf(';');
				while (pos != -1)
				{
					addRecentFile(QString::fromUtf8(&bytes.data()[last], pos));
					last = pos + 1;
					pos = bytes.indexOf(';', last);
				}
			}
			else if (strncmp(bytes.data(), t_DefaultDirectory,
							 sizeof(t_DefaultDirectory) - 1) == 0)
			{
				_defaultDirectory = QString::fromUtf8(
					&bytes.data()[sizeof(t_DefaultDirectory) - 1],
					bytes.size() - sizeof(t_DefaultDirectory));
				qDebug() << _defaultDirectory;
			}
			else if (strncmp(bytes.data(), t_LastDirectory,
							 sizeof(t_LastDirectory) - 1) == 0)
			{
				_lastDirectory = QString::fromUtf8(
					&bytes.data()[sizeof(t_LastDirectory) - 1],
					bytes.size() - sizeof(t_LastDirectory));
				qDebug() << _lastDirectory;
			}
			else if (strncmp(bytes.data(), t_ThemeName,
							 sizeof(t_ThemeName) - 1) == 0)
			{
				iconTheme = QString::fromUtf8(
					&bytes.data()[sizeof(t_ThemeName) - 1],
					bytes.size() - sizeof(t_ThemeName));
			}
			else if (strncmp(bytes.data(), t_StyleName,
							 sizeof(t_StyleName) - 1) == 0)
			{
				_styleName = QString::fromUtf8(
					&bytes.data()[sizeof(t_StyleName) - 1],
					bytes.size() - sizeof(t_StyleName));
			}
		}
		_iconManager->setTheme(iconTheme);
		return;
	}
	_recentFilesMax = 10;
	_defaultDirectory = QStandardPaths::writableLocation(
		QStandardPaths::DocumentsLocation) % QStringLiteral("/Projects");
	_lastDirectory = QStandardPaths::writableLocation(
		QStandardPaths::DocumentsLocation);
	_iconManager->setTheme(NGM::NGM_DEFAULT_THEME);
}

void NGM::Manager::SettingManager::addRecentFile(const QString &file)
{
	while (_recentFiles.size() == _recentFilesMax)
	{
		_recentFiles.removeLast();
	}
	_recentFiles.push_front(file);
}
