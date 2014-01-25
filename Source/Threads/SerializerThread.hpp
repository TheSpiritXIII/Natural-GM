/**
 *  @file SerializerThread.hpp
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
#ifndef NGM__SERIALIZERTHREAD__HPP
#define NGM__SERIALIZERTHREAD__HPP
#include <QThread>
#include <QMutex>

namespace NGM
{
	namespace Resource
	{
		class Serializer;
	}
	namespace Thread
	{
		/**************************************************//*!
		*	@brief	A thread that has the ability to load,
		*			save or create a project using a
		*			serializer.
		******************************************************/
		class SerializerThread : public QThread
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Possible commands that can be executed
			*			with serializers.
			******************************************************/
			enum class Command : char
			{
				Create	=	0,	/*!< Creates the project layout. */
				Load	=	1,	/*!< Loads the project layout. */
				Save	=	2,	/*!< Saves the project layout. */
				Reload	=	3	/*!< Requests a reload of the project layout. */
			};

			/**************************************************//*!
			*	@brief	Creates a thread object with the
			*			indicated parent.
			******************************************************/
			SerializerThread(QObject *parent = 0);

			/**************************************************//*!
			*	@brief	Sets a command to be executed and the
			*			serializer to execute when the thread is
			*			started. This function will be blocked
			*			if the thread is running. However, a
			*			deadlock can always occur.
			******************************************************/
			void setSerializer(Resource::Serializer *serializer,
							   Command command);

		protected:

			/**************************************************//*!
			*	@brief	Executes the stored serializer with the
			*			stored command. This function is blocked
			*			when setSerializer() is used. In
			*			addition, the serializer and commands
			*			are erased after the command is finished
			*			executing.
			******************************************************/
			void run();

		private:

			/**************************************************//*!
			*	@brief	Reponsible for blocking data.
			******************************************************/
			QMutex _mutex;

			/**************************************************//*!
			*	@brief	Stores the serializer to be executed.
			******************************************************/
			Resource::Serializer *_serializer;

			/**************************************************//*!
			*	@brief	Stores the command to be executed to the
			*			serializer.
			******************************************************/
			Command _command;
		};
	}
}

#endif // NGM__SERIALIZERTHREAD__HPP
