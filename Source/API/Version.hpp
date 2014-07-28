/*-
 *  Copyright (c) 2013 - 2014 Daniel Hrabovcak
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

namespace NGM
{
	namespace API
	{
		/**************************************************//*!
		*  @brief  Stores major, minor and revision numbers.
		******************************************************/
		struct Version
		{
			Version(uint8_t major, uint8_t minor, uint8_t revision = 0);
			uint8_t major, minor, revision;
			static Version version();
		};
	}
}

#define NGM_VERSION_MAJOR 0
#define NGM_VERSION_MINOR 0
#define NGM_VERSION_PATCH 0
#define NGM__PLUGIN_ENTRY pluginPWXuwR9s
#define NGM_PLUGIN_MAIN extern "C" NGM::API::Version NGM__version() \
{ \
	return NGM::API::Version(NGM_VERSION_MAJOR, NGM_VERSION_MINOR, \
		NGM_VERSION_PATCH); \
} \
extern "C" NGM::API::Plugin *NGM__PLUGIN_ENTRY()
