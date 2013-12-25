/**
 *  @file ErrorLogger.hpp
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
#ifndef NGM__ERRORLOGGER__HPP
#define NGM__ERRORLOGGER__HPP
#include <QString>

namespace NGM
{
	namespace Debug
	{
		/**************************************************//*!
		*	@brief	Handles a message handler function that
		*			logs to a text file for Qt's error stream.
		******************************************************/
		void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message);
	}
}

#endif // NGM__ERRORLOGGER__HPP
