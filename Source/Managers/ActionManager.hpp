/**
 *  @file ActionManager.hpp
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
#pragma once
#ifndef _NGM_ACTIONMANAGER__HPP
#define _NGM_ACTIONMANAGER__HPP
#include <QAction>
#include <QIcon>
#include <map>

namespace NGM
{
	namespace Manager
	{
		class WindowManager;
		class ProjectManager;

		/**************************************************//*!
		*	@brief	Stores all actions and icons.
		******************************************************/
		class ActionManager
		{
		public:

			/**************************************************//*!
			*	@brief	Contains all default actions types.
			******************************************************/
			enum Actions
			{
				ActionNew,
				ActionOpen,
				ActionSave,
				ActionSaveAs,
				ActionSaveAll,
				ActionClose,
				ActionCloseAll,
				ActionPrint,
				ActionExit,
				ActionUndo,
				ActionRedo,
				ActionCut,
				ActionCopy,
				ActionPaste,
				ActionSelectAll,
				ActionFindReplace,
				ActionBuild,
				ActionBuildAll,
				ActionRebuild,
				ActionRebuildAll,
				ActionClean,
				ActionCleanAll,
				ActionRun,
				ActionDebug,
				ActionPause,
				ActionStop,
				ActionContinue,
				ActionStepOver,
				ActionStepInto,
				ActionLayout,
				ActionPreferences,
				ActionHelp,
				ActionManual,
				ActionAbout
			};

			/**************************************************//*!
			*	@brief	Contains all default Drag & Drop icon types.
			******************************************************/
			enum DragNDrop
			{
				DragIf,
				DragElse,
				DragStartBlock,
				DragEndBlock
			};

			/**************************************************//*!
			*	@brief	Contains a list of default generic
			*			resource types (for icons).
			******************************************************/
			enum GenericResources
			{
				ResourceAnimation,
				ResourceImage,
				ResourceText,
				ResourceBlob,
				ResourceSound,
				ResourceMusic,
				ResourcePath,
				ResourceFont,
				ResourceTimeline,
				ResourceObject,
				ResourceScene,
				ResourceInformation,
				ResourceSettings,
				ResourceExtensions,
				ResourceGMLScript,
				ResourceGLSLScript
			};

			/**************************************************//*!
			*	@brief	Stores other managers.
			******************************************************/
			ActionManager(WindowManager *manager, ProjectManager *project);

			/**************************************************//*!
			*	@brief	Removes all actions and icons.
			******************************************************/
			~ActionManager();

			/**************************************************//*!
			*	@brief	Contains all actions.
			******************************************************/
			QAction *actions[64];

			/**************************************************//*!
			*	@brief	Contains all drag & drop icons.
			******************************************************/
			QIcon *dragdrop[192];

			/**************************************************//*!
			*	@brief	Contains generic resource icons.
			******************************************************/
			QIcon *resources[16];

			/**************************************************//*!
			*	@brief	Gets an icon based on the current theme.
			******************************************************/
			QIcon *getIconFromTheme(QString location);

			/**************************************************//*!
			*	@brief	Gets an icon from the indicated filename.
			******************************************************/
			QIcon *getIconFromFile(QString location);

			/**************************************************//*!
			*	@brief	Forces a reload of resource icons.
			******************************************************/
			void reload();

			/**************************************************//*!
			*	@brief	Forces a reload of drag n drop icons.
			******************************************************/
			void reloadDragDrop();

			/**************************************************//*!
			*	@brief	Unloads all drag n drop icons.
			******************************************************/
			void unloadDragDrop();

			/**************************************************//*!
			*	@brief	Forces a reload of all icons.
			******************************************************/
			void reloadAll();

			/**************************************************//*!
			*	@brief	Sets a new theme. Forces a reload.
			******************************************************/
			void setTheme(QString theme);

			/**************************************************//*!
			*	@return	The current theme name.
			******************************************************/
			QString getTheme();

			/**************************************************//*!
			*	@return	The theme appended with the icon name.
			******************************************************/
			QString getFullThemeDirectory(QString name = "");

		private:

			/**************************************************//*!
			*	@brief	Contains icons mapped to their filenames.
			******************************************************/
			std::map<QString, QIcon*> iconByFile;

			/**************************************************//*!
			*	@brief	Contains themed icons mapped to their filenames
			******************************************************/
			std::map<QString, QIcon*> iconByTheme;

			/**************************************************//*!
			*	@brief	Holds the current theme name.
			******************************************************/
			QString theme;

			/**************************************************//*!
			*	@brief	The project manager, for managing its icons.
			******************************************************/
			ProjectManager *project;

			/**************************************************//*!
			*	@brief	Contains action related settings.
			******************************************************/
			WindowManager *manager;

			friend class NGM::Manager::WindowManager;
		};
	}
}

#endif // _NGM_ACTIONMANAGER__HPP
