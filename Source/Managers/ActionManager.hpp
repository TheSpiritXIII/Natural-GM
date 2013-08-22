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
				ActionNewProject	=	0,
				ActionOpenProject	=	1,
				ActionNewFile		=	2,
				ActionOpenFile		=	3,
				ActionSave			=	4,
				ActionSaveAs		=	5,
				ActionSaveAll		=	6,
				ActionClose			=	7,
				ActionCloseAll		=	8,
				ActionPageSetup		=	9,
				ActionPrint			=	10,
				ActionExit			=	11,
				ActionImport		=	12,
				ActionExport		=	13,
				ActionUndo			=	14,
				ActionRedo			=	15,
				ActionCut			=	16,
				ActionCopy			=	17,
				ActionPaste			=	18,
				ActionSelectAll		=	19,
				ActionZoomIn		=	20,
				ActionZoomOut		=	21,
				ActionZoom			=	22,
				ActionFindReplace	=	23,
				ActionBuild			=	24,
				ActionBuildAll		=	25,
				ActionRebuild		=	26,
				ActionRebuildAll	=	27,
				ActionClean			=	28,
				ActionCleanAll		=	29,
				ActionRun			=	30,
				ActionDebug			=	31,
				ActionPause			=	32,
				ActionStop			=	33,
				ActionContinue		=	34,
				ActionStepOver		=	35,
				ActionStepInto		=	36,
				ActionLayout		=	37,
				ActionPreferences	=	38,
				ActionHelp			=	39,
				ActionManual		=	40,
				ActionAbout			=	41,
				ActionUnused0		=	42,
				ActionUnused1		=	43,
				ActionUnused2		=	44,
				ActionUnused3		=	45,
				ActionUnused4		=	46,
				ActionUnused5		=	47
			};

			/**************************************************//*!
			*	@brief	Contains all default Drag & Drop icon types.
			******************************************************/
			enum DragNDrop
			{
				DNDIf,
				DNDElse,
				DNDStartBlock,
				DNDEndBlock,
				DNDSetMotion,
				DNDMovePoint,
				DNDSetHspeed,
				DNDSetVspeed,
				DNDSetGravity,
				DNDReverseXdir,
				DNDReverseYdir,
				DNDSetFriction,
				DNDMoveTo,
				DNDMoveStart,
				DNDMoveRandom,
				DNDSnap,
				DNDWrap,
				DNDMoveContact,
				DNDBounce,
				DNDPath,
				DNDPathEnd,
				DNDPathPosition,
				DNDPathSpeed,
				DNDLinearStep,
				DNDPotentialStep
			};

			/**************************************************//*!
			*	@brief	Contains a list of default generic icons.
			******************************************************/
			enum GenericIcon
			{
				IconOkay		=	0,
				IconCancel		=	1,
				IconZoomIn		=	2,
				IconZoomOut		=	3,
				IconZoom		=	4,
				IconModify		=	5,
				IconAdd			=	6,
				IconDelete		=	7,
				IconPencil		=	8,
				IconPaintBrush	=	9,
				IconPaintCan	=	10,
				IconPalette		=	11,
				IconUnused0		=	12,
				IconUnused1		=	13,
				IconUnused2		=	14,
				IconUnused3		=	15
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
			*	@brief	Contains all drag & drop icons.
			******************************************************/
			QIcon *dragdrop[192];

			/**************************************************//*!
			*	@brief	Contains generic resource icons.
			******************************************************/
			QIcon *icons[16];

			/**************************************************//*!
			*	@brief	Returns the indicated action.
			******************************************************/
			const QAction *getAction(size_t type) const;

			/**************************************************//*!
			*	@brief	Gets an icon based on the current theme.
			******************************************************/
			QIcon *getIconFromTheme(const QString &location) const;

			/**************************************************//*!
			*	@brief	Gets an icon from the indicated filename.
			******************************************************/
			QIcon *getIconFromFile(const QString &location) const;

			/**************************************************//*!
			*	@brief	Forces a reload of resource icons.
			******************************************************/
			void reload();

			/**************************************************//*!
			*	@brief	Unloads resource icons. Call before reload.
			******************************************************/
			void unload();

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
			void setTheme(const QString &_theme);

			/**************************************************//*!
			*	@return	The current theme name.
			******************************************************/
			const QString getTheme() const;

		private:

			/**************************************************//*!
			*	@brief	Contains icons mapped to their filenames.
			******************************************************/
			std::map<const QString, QIcon*> iconByFile;

			/**************************************************//*!
			*	@brief	Contains themed icons mapped to their filenames
			******************************************************/
			std::map<const QString, QIcon*> iconByTheme;

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

			/**************************************************//*!
			*	@brief	Contains all actions.
			******************************************************/
			QAction *actions[64];

			friend class NGM::Manager::WindowManager;
		};
	}
}

#endif // _NGM_ACTIONMANAGER__HPP
