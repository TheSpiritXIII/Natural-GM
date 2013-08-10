/**
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
#ifndef _NGM_TEXTSERIALIZER__HPP
#define _NGM_TEXTSERIALIZER__HPP
#include "../Resources/Serializer.hpp"

namespace NGM
{
	namespace Resource
	{
		struct TextSerializer : public Serializer
		{
		public:

			/*! Reads a resource and inputs the data onto a widget. */
			void read(Widget *widget, Resource *resource);

			/*! Writes a resource based on widget data. */
			void write(Widget *widget, Resource *resource);

			/**************************************************//*!
			*	@brief	Creates the project tree structure.
			******************************************************/
			virtual void structure(Model::ResourceProjectItem *item) {}

			/**************************************************//*!
			*	@brief	Restructures changed files.
			******************************************************/
			virtual void restructure(const QString &file, Changed changed) {}

		private:

			/*! Contains settings bits. */
			static const char settings = 0;
		};
	}
}

#endif // _NGM_TEXTSERIALIZER__HPP
