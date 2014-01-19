/**
 *  @file IconManager.cpp
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
#include "IconManager.hpp"
#include "ProjectManager.hpp"
#include "Project.hpp"
#include <QStringBuilder>
#include <QFile>
#ifndef NGM_PORTABLE
#include <QStandardPaths>
#endif

#include <QDebug>

void NGM::Manager::IconManager::load()
{
#ifdef NGM_PORTABLE
	QString dir = QStringLiteral("icons/") % _theme % QStringLiteral("/main/");
#else
	QString dir = QStandardPaths::writableLocation(QStandardPaths::DataLocation)
			% QStringLiteral("/icons/") % _theme % QStringLiteral("/main/");
#endif
	QString file = dir % QStringLiteral("newproject.png");
	qDebug() << file;
	actionIcons[NewProject] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("openproject.png");
	actionIcons[OpenProject] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("save.png");
	actionIcons[Save] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("saveas.png");
	actionIcons[SaveAs] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("saveall.png");
	actionIcons[SaveAll] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("close.png");
	actionIcons[Close] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("closeall.png");
	actionIcons[CloseAll] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("pagesetup.png");
	actionIcons[PageSetup] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("print.png");
	actionIcons[Print] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("exit.png");
	actionIcons[Exit] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("import.png");
	actionIcons[Import] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("export.png");
	actionIcons[Export] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("undo.png");
	actionIcons[Undo] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("redo.png");
	actionIcons[Redo] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("cut.png");
	actionIcons[Cut] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("copy.png");
	actionIcons[Copy] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("paste.png");
	actionIcons[Paste] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("selectall.png");
	actionIcons[SelectAll] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("zoomin.png");
	actionIcons[ZoomIn] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("zoomout.png");
	actionIcons[ZoomOut] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("zoom.png");
	actionIcons[Zoom] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("findreplace.png");
	actionIcons[FindReplace] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("build.png");
	actionIcons[Build] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("buildall.png");
	actionIcons[BuildAll] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("rebuild.png");
	actionIcons[Rebuild] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("rebuildall.png");
	actionIcons[RebuildAll] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("clean.png");
	actionIcons[Clean] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("cleanall.png");
	actionIcons[CleanAll] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("run.png");
	actionIcons[Run] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("debug.png");
	actionIcons[Debug] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("stop.png");
	actionIcons[Stop] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("stepover.png");
	actionIcons[StepOver] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("stepinto.png");
	actionIcons[StepInto] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("layout.png");
	actionIcons[Layout] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("preferences.png");
	actionIcons[Preferences] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("about.png");
	actionIcons[About] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("plugins.png");
	actionIcons[Plugins] = QFile::exists(file) ? QIcon(file) : QIcon();

#ifdef NGM_PORTABLE
	dir = QStringLiteral("icons/") % _theme % QStringLiteral("/generic/");
#else
	dir = QStandardPaths::writableLocation(QStandardPaths::DataLocation)
			% QStringLiteral("/icons/") % _theme % QStringLiteral("/generic/");
#endif
	file = dir % QStringLiteral("newfile.png");
	genericIcons[NewFile] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("openfile.png");
	genericIcons[OpenFile] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("groupclosed.png");
	genericIcons[GroupClosed] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("groupopen.png");
	genericIcons[GroupOpen] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("okay.png");
	genericIcons[Okay] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("cancel.png");
	genericIcons[Cancel] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("modify.png");
	genericIcons[Modify] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("add.png");
	genericIcons[Add] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("delete.png");
	genericIcons[Delete] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("move.png");
	genericIcons[Move] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("pencil.png");
	genericIcons[Pencil] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("paintbrush.png");
	genericIcons[PaintBrush] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("paintcan.png");
	genericIcons[PaintCan] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("palette.png");
	genericIcons[Palette] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("arrowup.png");
	genericIcons[ArrowUp] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("arrowdown.png");
	genericIcons[ArrowDown] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("arrowleft.png");
	genericIcons[ArrowLeft] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("arrowright.png");
	genericIcons[ArrowRight] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("home.png");
	genericIcons[Home] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("globe.png");
	genericIcons[Globe] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("computer.png");
	genericIcons[Computer] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("pin.png");
	genericIcons[Pin] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("unpin.png");
	genericIcons[Unpin] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("attach.png");
	genericIcons[Attach] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("music.png");
	genericIcons[Music] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("timer.png");
	genericIcons[Timer] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("volumeup.png");
	genericIcons[VolumeUp] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("volumedown.png");
	genericIcons[VolumeDown] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("mute.png");
	genericIcons[Mute] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("microphone.png");
	genericIcons[Microphone] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("update.png");
	genericIcons[Update] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("reload.png");
	genericIcons[Reload] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("lock.png");
	genericIcons[Lock] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("unlock.png");
	genericIcons[Unlock] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("background.png");
	genericIcons[Background] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("image.png");
	genericIcons[Image] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("path.png");
	genericIcons[Path] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("font.png");
	genericIcons[Font] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("message.png");
	genericIcons[Message] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("log.png");
	genericIcons[Log] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("help.png");
	genericIcons[Help] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("pause.png");
	genericIcons[Pause] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("rewind.png");
	genericIcons[Rewind] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("fastforward.png");
	genericIcons[FastFoward] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("skip.png");
	genericIcons[Skip] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("skipback.png");
	genericIcons[SkipBack] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("iconview.png");
	genericIcons[IconView] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("listview.png");
	genericIcons[ListView] = QFile::exists(file) ? QIcon(file) : QIcon();
	file = dir % QStringLiteral("grid.png");
	genericIcons[Grid] = QFile::exists(file) ? QIcon(file) : QIcon();

#ifdef NGM_PORTABLE
	dir = QStringLiteral("icons/") % _theme % QStringLiteral("/project/");
	QString common = QStringLiteral("icons/common/project/");
#else
	dir = QStandardPaths::writableLocation(QStandardPaths::DataLocation)
			% QStringLiteral("/icons/") % _theme % QStringLiteral("/project/");
	QString common = QStandardPaths::writableLocation(
				QStandardPaths::DataLocation) %
			QStringLiteral("/icons/common/project/");
#endif
	Manager::ProjectIconIterator p =_projectManager->iconIterator();
	while (!_projectManager->iconIteratorEnd(p))
	{
		file = dir % p.getName() % QStringLiteral(".png");
		if (!QFile::exists(file))
		{
			file = common % p.getName() % QStringLiteral(".png");
			qDebug() << file << QFile::exists(file);
		}
		if (QFile::exists(file))
		{
			QPixmap pixmap(file);
			if (pixmap.size() != QSize(48, 48))
			{
				pixmap = pixmap.scaled(QSize(48, 48));
			}
			*p.getIcon() = QIcon(pixmap);
		}
		else
		{
			*p.getIcon() = _emptyProjectIcon;
		}
		++p;
	}

	QMap<QString, QIcon*>::iterator i = _iconFile.begin();
	while (i != _iconFile.end())
	{
		(*i.value()) = QIcon(i.key());
	}

#ifdef NGM_PORTABLE
	dir = QStringLiteral("icons/") % _theme % QStringLiteral("/");
	common = QStringLiteral("icons/common/");
#else
	dir = QStandardPaths::writableLocation(QStandardPaths::DataLocation)
			% QStringLiteral("/icons/") % _theme % QStringLiteral("/");
	common = QStandardPaths::writableLocation(QStandardPaths::DataLocation)
			% QStringLiteral("/icons/common/");
#endif
	i = _iconTheme.begin();
	while (i != _iconTheme.end())
	{
		file = QStringLiteral("icons/") % _theme % QStringLiteral("/") % i.key();
		if (!QFile::exists(file))
		{
			file = common % i.key();
		}
		(*i.value()) = QFile::exists(file) ? QIcon(file) : QIcon();
	}
}

namespace NGM
{
	namespace Manager
	{
		IconManager::IconManager(ProjectManager *projectManager) :
			_projectManager(projectManager),
#ifdef Q_OS_WIN
			_appIcon(QStringLiteral("icon.ico"))
#elif defined(Q_OS_MAC)
			_appIcon(QStringLiteral("icon.icns"))
#else
			_appIcon(QStringLiteral("icon.png"))
#endif
		{
			QPixmap pixmap(48, 48);
			pixmap.fill(Qt::transparent);
			_emptyProjectIcon = QIcon(pixmap);
		}

		void IconManager::setTheme(const QString &theme)
		{
			qDebug() << theme;
			_theme = theme;
			load();
			emit iconsChanged();
		}

		QIcon *IconManager::iconByFilename(const QString &name)
		{
			QMap<QString, QIcon*>::const_iterator i = _iconFile.find(name);
			return i != _iconFile.end() ? i.value() : iconLoadByFilename(name);
		}

		QIcon *IconManager::iconByTheme(const QString &name)
		{
			QMap<QString, QIcon*>::const_iterator i = _iconTheme.find(name);
			return i != _iconTheme.end() ? i.value() : iconLoadByTheme(name);
		}

		QIcon *IconManager::iconLoadByFilename(const QString &name)
		{
			QIcon *icon = new QIcon(name);
			_iconFile.insert(name, icon);
			return icon;
		}

		QIcon *IconManager::iconLoadByTheme(const QString &name)
		{
			QIcon *icon = new QIcon(QStringLiteral("icons/") % _theme % QStringLiteral("/") % name);
			_iconFile.insert(name, icon);
			return icon;
		}
	}
}
