/**
 *  @file SerializerThread.cpp
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
#include "SerializerThread.hpp"
#include "Serializer.hpp"
#include <QMutexLocker>

NGM::Thread::SerializerThread::SerializerThread(QObject *parent) :
		QThread(parent), _serializer(nullptr) {}

void NGM::Thread::SerializerThread::setSerializer(
		Resource::Serializer *serializer, Command command)
{
	QMutexLocker locker(&_mutex);
	_serializer = serializer;
	_command = command;
}

void NGM::Thread::SerializerThread::run()
{
	QMutexLocker locker(&_mutex);
	switch (_command)
	{
	case Command::Create:
		//_serializer->layoutCreate();
		break;
	case Command::Load:
		//_serializer->layoutLoad(_resourceProjectItem, _serializerOptions);
		break;
	case Command::Save:
		//_serializer->layoutLoad(_resourceProjectItem, _serializerOptions);
		break;
	case Command::Reload:
		//_serializer->layoutReload(_resourceProjectItem, _serializerOptions);
		break;
	}
}
