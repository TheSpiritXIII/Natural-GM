/**
 *  @file ProgressManager.hpp
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
#ifndef _NGM_PROGRESSMANAGER__HPP
#define _NGM_PROGRESSMANAGER__HPP
#include "WindowManager.hpp"

namespace NGM
{
	namespace Manager
	{
		/**************************************************//*!
		*	@brief	A useful class for modifying application
		*			wide progress labels and bars.
		******************************************************/
		class ProgressManager
		{
		public:

			/**************************************************//*!
			*	@brief	Sets the window manager.
			******************************************************/
			ProgressManager(WindowManager *manager);

			/**************************************************//*!
			*	@brief	Updates all progress bar maximums.
			******************************************************/
			void setMaximum(const int &maximum);

			/**************************************************//*!
			*	@brief	Increments the progress bar by 1.
			******************************************************/
			void incrementValue();

			/**************************************************//*!
			*	@brief	Sets the progress bar's value.
			******************************************************/
			void setValue(const int &value);

			/**************************************************//*!
			*	@brief	Sets the label text.
			******************************************************/
			void setText(const QString &text);

		private:

			/**************************************************//*!
			*	@brief	The window manager knows all labels.
			******************************************************/
			WindowManager *manager;

		};
	}
}

#endif // _NGM_PROGRESSMANAGER__HPP
