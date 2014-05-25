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
	namespace Manager
	{
		struct IconManager;

		/**************************************************//*!
		*  @brief  Interacts with other managers.
		******************************************************/
		class GlobalManager
		{
		public:

			/**************************************************//*!
			*  @brief  Returns the icon manager.
			******************************************************/
			IconManager *iconManager() const;

			/**************************************************//*!
			*  @brief  Finds and returns the plugin with the
			*          given name.
			******************************************************/
			Plugin *plugin(const QString &name);
		};
	}
}
