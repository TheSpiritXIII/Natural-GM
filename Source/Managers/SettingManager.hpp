/**
 *  @file SettingManager.hpp
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
#ifndef NGM__SETTINGSMANAGER__HPP
#define NGM__SETTINGSMANAGER__HPP
#include <QStringList>

class QWidget;

namespace NGM
{
	namespace Manager
	{
		class IconManager;

		typedef uint8_t ProjectPreferences;

		/**************************************************//*!
		*	@brief	Holds global application settings.
		******************************************************/
		struct SettingManager final
		{

			//! DEPRECATED
			enum PreferencesDeprecated
			{
				ShowWelcome         =   0x0001,//0b0000000000000001,
				NoResourceTabs      =   0x0002,//0b0000000000000010,
				HideResourceTabs    =   0x0004,//0b0000000000000100,
				ExternalResources   =   0x0008,//0b0000000000001000,
				CodeUseTabs         =   0x0010,//0b0000000000010000,
				CodeWarpNone        =   0x0000,//0b0000000000000000,
				CodeWarpChar        =   0x0020,//0b0000000000100000,
				CodeWarpWord        =   0x0060,//0b0000000001100000,
				CodeEdgeNone        =   0x0000,//0b0000000000000000,
				CodeEdgeLine        =   0x0080,//0b0000000010000000,
				CodeEdgeBack        =   0x0180,//0b0000000110000000,
				UseDirectory		=	0x0200,//0b0000001000000000,
				PreloadData			=	0x0800,//0b0000100000000000,
				UniqueIcons			=	0x1000//b0001000000000000
			};
			//! DEPRECATED
			enum CodeColor
			{
				FontColor					=	0,
				PaperBackground				=	1,
				EdgeBackground				=	2,
				CaretBackground				=	3,
				CaretForeground				=	4,
				SelectionBackground			=	5,
				SelectionForeground			=	6,
				MarginBackground			=	7,
				MarginForeground			=	8,
				FoldMarginBackground		=	9,
				FoldMarginForeground		=	10,
				MatchedBraceBackground		=	11,
				MatchedBraceForeground		=	12,
				UnmatchedBraceBackground	=	13,
				UnmatchedBraceForeground	=	14,
				MarkerBackground			=	15,
				MarkerForeground			=	16,
				WhitespaceBackground		=	17,
				WhitespaceForeground		=	18,
				IndentationBackground		=	19,
				IndentationForeground		=	20,
				CalltipsBackground			=	21,
				CalltipsForeground			=	22,
				CalltipsHighlight			=	23,
				Reserved1					=	24,
				Reserved2					=	25,
				Reserved3					=	26,
				Reserved4					=	27,
				Reserved5					=	28,
				Reserved6					=	29,
				Reserved7					=	30,
				Reserved8					=	31,
				NormalText					=	32,
				Keywords					=	33,
				Number						=	34,
				Strings						=	35,
				Comments					=	36,
				Constants					=	37,
				BuiltInVariables			=	38,
				Functions					=	39,
				ScriptNames					=	40,
				ResourceNames				=	41,
				Reserved9					=	42,
				Reserved10					=	43,
				Reserved11					=	44,
				Reserved12					=	45,
				Reserved13					=	46,
				Reserved14					=	47,
				Reserved15					=	48
			};

			//! DEPRECATED
			uint32_t settings;

			//! DEPRECATED
			QString oldDirectory;




			/**************************************************//*!
			*	@brief	Contains basic application settings.
			******************************************************/
			enum ProjectPreference
			{
				AddDirectory		=	0x04,	/*!< Whether or not new projects
													should add directories. */
				Descending			=	0x01,	/*!< Whether or not projects are
													sorted descending. */
				IconMode			=	0x02,	/*!< Whether or not projects are
													shown in icon mode. */
				ShowGroups			=	0x08,	/*!< Whether or not group based
													project types are
													displayed. */
				ShowFiles			=	0x10,	/*!< Whether or not file based
													project types are
													displayed.*/
				SetDefault			=	0x80	/*!< Hints the the selected
													directory as default.
													Unused in settings. */
			};

			/**************************************************//*!
			*	@brief	Header IDs for the settings format.
			******************************************************/
			enum FileHeader : char
			{
				RecentFiles			=	0,
				RecentFilesMax		=	1,
				DefaultDirectory	=	2,
				LastDirectory		=	3
			};

			/// DEPRECATED.
			SettingManager();

			/**************************************************//*!
			*	@brief	Stores an icon manager, for loading its
			*			icons later.
			******************************************************/
			SettingManager(IconManager *iconManager);

			/**************************************************//*!
			*	@brief	Saves all settings.
			******************************************************/
			~SettingManager();

			/**************************************************//*!
			*	@brief	Loads the application settings. If the
			*			settings file is not found, defaults are
			*			set. All directories are set as the
			*			"Documents" user folder by default.
			*	@param	projectManager The icon manager, for
			*			loading the default icon theme.
			******************************************************/
			void load();

			/**************************************************//*!
			*	@brief
			******************************************************/
			void restoreWidget(QWidget *widget);

			/**************************************************//*!
			*	@brief	Contains the preferences for the project
			*			dialog.
			******************************************************/
			ProjectPreferences projectPreferences;

			/**************************************************//*!
			*	@brief	Sets the max recent file size.
			******************************************************/
			inline void setRecentFilesMax(unsigned char max)
			{
				_recentFilesMax = max;
			}

			/**************************************************//*!
			*	@brief	Returns the max number of recent files.
			******************************************************/
			inline unsigned char recentFilesMax() const
			{
				return _recentFilesMax;
			}

			/**************************************************//*!
			*	@brief	Returns a list of recent files.
			******************************************************/
			inline const QStringList recentFiles() const
			{
				return _recentFiles;
			}

			/**************************************************//*!
			*	@brief	Adds a new item to the front of the list.
			*			When max items are reached, the last one
			*			is removed.
			******************************************************/
			void addRecentFile(const QString &file);

			/**************************************************//*!
			*	@brief	Returns the default directory. This is
			*			the directory that is displayed when
			*			creating new project.
			******************************************************/
			inline QString defaultDirectory() const
			{
				return _defaultDirectory;
			}

			/**************************************************//*!
			*	@brief	Sets the default directory. To be used
			*			when a project is created.
			******************************************************/
			inline void setDefaultDirectory(const QString &directory)
			{
				_defaultDirectory = directory;
			}

			/**************************************************//*!
			*	@brief	Returns the last directory that was used
			*			to open a project.
			******************************************************/
			inline QString lastDirectory() const
			{
				return _lastDirectory;
			}

			/**************************************************//*!
			*	@brief	Sets the last directory. To be used when
			*			a file is opened.
			******************************************************/
			inline void setLastDirectory(const QString &directory)
			{
				_lastDirectory = directory;
			}

		private:

			/**************************************************//*!
			*	@brief	Stores the icon manager, for loading the
			*			icon manager's theme.
			******************************************************/
			IconManager *_iconManager;

			/**************************************************//*!
			*	@brief	Contains the recently used projects that
			*			the user opened.
			******************************************************/
			QStringList _recentFiles;

			/**************************************************//*!
			*	@brief	Stores the max number of recent files.
			******************************************************/
			unsigned char _recentFilesMax;

			/**************************************************//*!
			*	@brief	Stores the last directory that the user
			*			has agreed to set as the default.
			******************************************************/
			QString _defaultDirectory;

			/**************************************************//*!
			*	@brief	Stores the last directory used to open a
			*			project in.
			******************************************************/
			QString _lastDirectory;

			/**************************************************//*!
			*	@brief	Stores the style name. This is how
			*			windows are styled.
			******************************************************/
			QString _styleName;
		};
	}
}

#endif // NGM__SETTINGSMANAGER__HPP
