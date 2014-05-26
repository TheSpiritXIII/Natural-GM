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
		struct EditorTools
		{
			/**************************************************//*!
			*  @brief  Sets all tool objects.
			*
			* All objects must be valid throughout the entire
			* lifetime. Otherwise, there is a risk of a buffer
			* overflow or other errors.
			******************************************************/
			EditorTools(QMenu **menus, uint8_t menuCount, QToolBar ** toolBars,
			  uint8_t toolBarCount, QStatusBar *statusBar);

			/**************************************************//*!
			*  @brief  Deallocates all stored tool objects.
			******************************************************/
			~EditorTools();

			/**************************************************//*!
			*  @brief  Returns an array of menus, or nullptr if
			*          there are no menus.
			*  @see    menuCount();
			******************************************************/
			QMenu **menus() const;

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
			QToolBar **toolBars() const;

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

		private:
			QMenu ** const _menus;
			const uint8_t _menuCount;
			QToolBar ** const _toolBars;
			const uint8_t _toolBarCount;
			QStatusBar *_statusBar;
		};
	}
}
