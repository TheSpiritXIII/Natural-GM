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
		struct Factory;
		struct Project;
		struct Extension;

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
			* This number is used by the plugin loader. By
			* default, most plugins have a priority of 50, and
			* typically range between 0 and 100. Anything above
			* or below these values should be purely independent
			* or dependent, respectively, by other plugins.
			******************************************************/
			const float priority;

			/**************************************************//*!
			*  @brief  A unique identifier for this plugin.
			*
			* Other plugins may use this value for obtaining a
			* certain plugin. For this reason, it is important
			* that this value is unique.
			******************************************************/
			const uint32_t uuid;

			/**************************************************//*!
			*  @brief  Executes the given command with the given
			*          parameters.
			*
			* Other plugins may use this for accessing this
			* plugin's functionality.
			******************************************************/
			virtual SerialData *execute(const char *command,
			  SerialData *params) const;

		protected:

			/**************************************************//*!
			*  @brief  Creates a plugin with meta-data.
			*
			* Subclasses should write their own constructors,
			* where they add their data. Data should only be
			* added in the constructor, and should be valid
			* throughout the lifetime of the application.
			******************************************************/
			Plugin(const QString &name, const QString &authors,
			  const QString &description, Version version, uint32_t uuid,
			  float priority = 50.0f);

			/**************************************************//*!
			*  @brief  Contains all factories, or is empty if the
			*          plugin does not suport factories.
			******************************************************/
			QVector<Factory*> _factories;

			/**************************************************//*!
			*  @brief  Contains all projects, or is empty if the
			*          plugin does not suport projects.
			******************************************************/
			QVector<Project*> _projects;

			/**************************************************//*!
			*  @brief  Contains all extensions, or is empty if
			*          the plugin does not suport extensions.
			******************************************************/
			QVector<Extension*> _extensions;
		};
	}
}
