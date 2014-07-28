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

class QLibrary;

namespace NGM
{
	namespace API
	{
		struct Plugin;
	}
	namespace Core
	{
		class Plugin
		{
		private:
			QString _title;
			QString _name;
			QString _version;
			QString _authors;
			QString _description;
			QString _licenses;

			// TODO: Dependencies.

			QLibrary *library;
			API::Plugin *plugin;
		};
	}
}
