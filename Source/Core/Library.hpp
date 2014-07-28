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
#include <QLibrary>

namespace NGM
{
	namespace API
	{
		struct Plugin;
	}
	namespace Core
	{
		/**************************************************//*!
		*  @brief  Contains a library and its plugin data.
		******************************************************/
		struct Library
		{
			/**************************************************//*!
			*  @brief  Creates the library.
			******************************************************/
			Library(API::Plugin *plugin, QLibrary *library);

			/**************************************************//*!
			*  @brief  Deallocates all data.
			******************************************************/
			~Library();

			/**************************************************//*!
			*  @brief  Stores the plugin.
			******************************************************/
			const API::Plugin * const plugin;

			/**************************************************//*!
			*  @brief  Contains the library.
			******************************************************/
			QLibrary * const library;

			/**************************************************//*!
			*  @brief  Returns true if the other library has a
			*          lower priority value.
			******************************************************/
			bool operator<(const Library &other);
		};
	}
}
