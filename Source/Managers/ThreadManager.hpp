/**
 *  @file ThreadManager.hpp
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
#ifndef _NGM_THREADMANAGER__HPP
#define _NGM_THREADMANAGER__HPP
#include <QSharedMemory>
#include <cstdint>
#include <thread>
#include <queue>

namespace NGM
{
	namespace Manager
	{
		class ThreadManager
		{
		public:

			/**************************************************//*!
			*	@brief	Defines all possible process types.
			******************************************************/
			enum Process
			{
				LoadPlugins		=	0x01,
				LoadImages		=	0x02,
				Compile			=	0x04,
				SaveFile		=	0x08,
				LoadFile		=	0x10
			};

			/**************************************************//*!
			*	@brief	Posts the process to be scheduled.
			******************************************************/
			void postProcess(Process process);

			/**************************************************//*!
			*	@brief	Returns whether or not a process is
			*			currently scheduled.
			******************************************************/
			const bool &busy();

		private:

			/**************************************************//*!
			*	@brief	Holds scheduled process bits.
			******************************************************/
			uint16_t process;

			/**************************************************//*!
			*	@brief	Shared memory to be used with executables.
			******************************************************/
			QSharedMemory *sharedMemory;

			/**************************************************//*!
			*	@brief	Processes all scheduled events.
			******************************************************/
			processEvents();

			/**************************************************//*!
			*	@brief	Holds
			******************************************************/

		};
	}
}

#endif // _NGM_THREADMANAGER__HPP
