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
#include <QMainWindow>

namespace NGM
{
	namespace Widget
	{
		/**************************************************//*!
		*  @brief  Displays an editor.
		*
		* This class is not used in the final release. It
		* exists as an easy way to set up an isolated testing
		* environment.
		******************************************************/
		class SDIEditorWindow : public QMainWindow
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*  @brief  Creates a window with the given parent.
			******************************************************/
			SDIEditorWindow(QObject *parent = 0);
		};
	}
}
