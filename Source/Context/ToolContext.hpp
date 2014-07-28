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
#include <cstdint>
#include <QVector>

class QMenu;
class QToolBar;
class QStatusBar;

namespace NGM
{
	namespace API
	{
		/**************************************************//*!
		*  @brief  Stores tool objects that are used by
		*          editors.
		******************************************************/
		struct ToolContext
		{
			/**************************************************//*!
			*  @brief  Deallocates all stored tool objects.
			******************************************************/
			~ToolContext();

			/**************************************************//*!
			*  @brief  Returns an array of menus, or nullptr if
			*          there are no menus.
			*  @see    menuCount();
			******************************************************/
			QMenu *menus();

			/**************************************************//*!
			*  @brief  Returns the number of menus, or 0 if there
			*          are no menus.
			******************************************************/
			uint8_t menuCount() const;

			/**************************************************//*!
			*  @brief  Returns an array of tool-bars, or nullptr
			*          if there are no tool-bars.
			*  @see    toolbarCount();
			******************************************************/
			QToolBar *toolBars();

			/**************************************************//*!
			*  @brief  Returns the number of tool-bars, or 0 if
			*          there are no menus.
			******************************************************/
			uint8_t toolBarCount() const;

			/**************************************************//*!
			*  @brief  Returns a status bar, or nullptr if there
			*          is no status bar.
			******************************************************/
			QStatusBar *statusBar() const;

		protected:

			/**************************************************//*!
			* Subclasses should create their own their own
			* constructor, where they create widgets. All widgets
			* must be valid throughout the entire lifetime, and
			* should be created only here. All memory is deleted
			* automatically by the default destructor.
			******************************************************/
			ToolContext();

			/**************************************************//*!
			*  @brief  Contains menus, or is empty if menus are
			*          not supported by the editor.
			******************************************************/
			QVector<QMenu*> _menus;

			/**************************************************//*!
			*  @brief  Contains tool-bars, or is empty if
			*          tool-bars are not supported by the editor.
			******************************************************/
			QVector<QToolBar*> _tools;

			/**************************************************//*!
			*  @brief  Contains the status-bar, or nullptr if a
			*          status-bar is not supported by the editor.
			******************************************************/
			QStatusBar *_statusBar;
		};
	}
}
