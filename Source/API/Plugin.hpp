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

namespace NGM
{
	namespace API
	{
		/**************************************************//*!
		*  @brief  Stores major, minor and revision numbers.
		******************************************************/
		struct Version
		{
			Version(uint8_t major, uint8_t minor, uint8_t revision);
			uint8_t major, minor, revision;
		};

		/**************************************************//*!
		*  @brief  Stores plugin data.
		******************************************************/
		struct Plugin
		{
			/**************************************************//*!
			*  @brief  The name of this plugin.
			******************************************************/
			const QString name;

			/**************************************************//*!
			*  @brief  The name of all authors.
			******************************************************/
			const QString authors;

			/**************************************************//*!
			*  @brief  A brief description on what the plugin
			*          does.
			******************************************************/
			const QString description;

			/**************************************************//*!
			*  @brief  Stores the version number of the plugin.
			******************************************************/
			const Version version;

			/**************************************************//*!
			*  @brief  The priority number of this plugin.
			*
			* This number is used by the plugin loader.
			******************************************************/
			const float priority;

			/**************************************************//*!
			*  @brief  A unique identifier for this plugin.
			******************************************************/
			const uint32_t uuid;
		};
	}
}
