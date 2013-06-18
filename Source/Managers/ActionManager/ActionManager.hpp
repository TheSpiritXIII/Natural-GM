/**
 *  @file ActionManager.hpp
 *  @brief Declares a class that stores icons and actions.
 *
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
		class ActionManager
		{

		public:

			/*! Contains all default actions types. */
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

			/*! Contains all default Drag & Drop icon types. */
			enum DragNDrop
			{
				DragIf,
				DragElse,
				DragStartBlock,
				DragEndBlock
			};

			/*! Contains a list of default generic resource types. */
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

			/*! Contains a group of actions. */
			QAction *actions[64];

			/*! Contains the drag & drop icons. */
			QIcon *dragdrop[192];

			/*! Contains generic resource icons. */
			QIcon *resources[16];

			/*! Loads (if not loaded) and returns an icon from the current theme. */
			QIcon *getIconFromTheme(QString location);

			/*! Loads (if not loaded) and returns an icon with the indicated filename. */
			QIcon *getIconFromFile(QString location);

			/*! Force a reload of all icons. */
			void reload();

			/*! Sets a new icon theme. This will reload all icons. */
			void setTheme(QString theme);

			/*! Gets the theme name. */
			QString getTheme();

		private:

			/*! Contains icons with their filenames. */
			std::map<QString, QIcon*> iconByFile;

			/*! Contains icons. Format for naming is "extension/name". */
			std::map<QString, QIcon*> iconByTheme;

			/*! Contains the current theme name. */
			QString _theme;
		};
	}
}

#endif // _NGM_ACTIONMANAGER__HPP
