/**
 *  @file IconManager.hpp
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
#ifndef NGM__ICONMANAGER__HPP
#define NGM__ICONMANAGER__HPP
#include <QObject>
#include <QString>
#include <QIcon>
#include <QMap>

namespace NGM
{
	namespace Manager
	{
		class ProjectManager;

		/**************************************************//*!
		*	@brief	Preloads and manages generic icons. All
		*			default (action and generic) icons are
		*			loaded as png files.
		******************************************************/
		class IconManager : public QObject
		{
			Q_OBJECT

		public:

			IconManager(ProjectManager *projectManager);

			/**************************************************//*!
			*	@brief	Contains icons used by actions.
			******************************************************/
			enum ActionIcon
			{
				NewProject		=	0,
				OpenProject		=	1,
				Save			=	2,
				SaveAs			=	3,
				SaveAll			=	4,
				SaveProject		=	37,
				SaveProjectAs	=	38,
				SaveProjectAll	=	39,
				Close			=	5,
				CloseAll		=	6,
				PageSetup		=	7,
				Print			=	8,
				Exit			=	9,
				Import			=	10,
				Export			=	11,
				Undo			=	12,
				Redo			=	13,
				Cut				=	14,
				Copy			=	15,
				Paste			=	16,
				SelectAll		=	17,
				ZoomIn			=	18,
				ZoomOut			=	19,
				Zoom			=	20,
				FindReplace		=	21,
				Build			=	22,
				BuildAll		=	23,
				Rebuild			=	24,
				RebuildAll		=	25,
				Clean			=	26,
				CleanAll		=	27,
				Run				=	28,
				Debug			=	29,
				Stop			=	30,
				StepOver		=	31,
				StepInto		=	32,
				Layout			=	33,
				Preferences		=	34,
				About			=	35,
				Plugins			=	36,
				ActionSize		=	40
			};

			/**************************************************//*!
			*	@brief	Contains a list of default generic icons.
			******************************************************/
			enum GenericIcon
			{
				NewFile			=	0,
				OpenFile		=	1,
				GroupOpen		=	2,
				GroupClosed		=	3,
				Okay			=	4,
				Cancel			=	5,
				Modify			=	6,
				Add				=	7,
				Delete			=	8,
				Move			=	9,
				Pencil			=	10,
				PaintBrush		=	11,
				PaintCan		=	12,
				Palette			=	13,
				ArrowUp			=	14,
				ArrowDown		=	15,
				ArrowLeft		=	16,
				ArrowRight		=	17,
				Home			=	18,
				Globe			=	19,
				Computer		=	20,
				Pin				=	21,
				Unpin			=	22,
				Attach			=	23,
				Music			=	24,
				Timer			=	25,
				VolumeUp		=	26,
				VolumeDown		=	27,
				Mute			=	28,
				Microphone		=	29,
				Update			=	30,
				Reload			=	31,
				Lock			=	32,
				Unlock			=	33,
				Background		=	34,
				Image			=	35,
				Path			=	36,
				Font			=	37,
				Message			=	38,
				Log				=	39,
				Help			=	40,
				Pause			=	41,
				Rewind			=	42,
				FastFoward		=	43,
				Skip			=	44,
				SkipBack		=	45,
				IconView		=	46,
				ListView		=	47,
				Grid			=	48,
				GenericSize		=	49,
				User,
				Shader,
				Script,
				Warning,
				Critical,
				Error,
				Accept,
				Reject
			};

			/**************************************************//*!
			*	@brief	Contains icons used by actions. It is
			*			recommended that you don't change these.
			*			They will be changed whenever the theme
			*			is changed.
			******************************************************/
			QIcon actionIcons[64];

			/**************************************************//*!
			*	@brief	Contains generic icons. It is recommended
			*			that you don't change these. They will be
			*			changed whenever the theme is changed.
			******************************************************/
			QIcon genericIcons[64];

			/**************************************************//*!
			*	@brief	Sets a new theme. Forces a reload.
			******************************************************/
			void setTheme(const QString &theme);

			/**************************************************//*!
			*	@brief	Returns the current theme name.
			******************************************************/
			inline QString theme() const
			{
				return _theme;
			}

			/**************************************************//*!
			*	@brief	Gets an icon by filename. If the icon
			*			does not exist, it is loaded.
			*	@see	loadByFilename();
			******************************************************/
			QIcon *iconByFilename(const QString &name);

			/**************************************************//*!
			*	@brief	Returns an icon relative to the icon
			*			theme. If it does not exist, it is
			*			loaded.
			*	@see	loadByTheme();
			******************************************************/
			QIcon *iconByTheme(const QString &name);

			/**************************************************//*!
			*	@brief	Loads and caches an icon by filename.
			******************************************************/
			QIcon *iconLoadByFilename(const QString &name);

			/**************************************************//*!
			*	@brief	Loads and caches an icon by filename
			*			relative to the theme directory. It is
			*			recommend that you place this inside
			*			a directory, if you require unique
			*			icons.
			******************************************************/
			QIcon *iconLoadByTheme(const QString &name);

			/**************************************************//*!
			*	@brief	Returns the application icon. This is
			*			loaded from the application working
			*			directory.
			******************************************************/
			inline const QIcon *applicationIcon()
			{
				return &_appIcon;
			}

			inline const QIcon &projectIcon() const
			{
				return _emptyProjectIcon;
			}

		signals:

			/**************************************************//*!
			*	@brief	Called when icons are reloaded.
			******************************************************/
			void iconsChanged();

		private:

			/**************************************************//*!
			*	@brief	Loads all icons.
			******************************************************/
			void load();

			/**************************************************//*!
			*	@brief	Stores the project manager for loading
			*			project icons.
			******************************************************/
			ProjectManager *_projectManager;

			/**************************************************//*!
			*	@brief	Holds the current theme name.
			******************************************************/
			QString _theme;

			/**************************************************//*!
			*	@brief	Contains icons loaded by a filename.
			******************************************************/
			QMap<QString, QIcon*> _iconFile;

			/**************************************************//*!
			*	@brief	Contains icons loaded by a filename
			*			relative to the icon theme directory.
			******************************************************/
			QMap<QString, QIcon*> _iconTheme;

			/**************************************************//*!
			*	@brief	Contains the application icon.
			******************************************************/
			QIcon _appIcon;

			QIcon _emptyProjectIcon;

		};
	}
}

#endif // NGM__ICONMANAGER__HPP
