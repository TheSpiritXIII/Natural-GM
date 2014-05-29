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
		struct Serializer;

		/**************************************************//*!
		*  @brief  Stores project serializer properties.
		*
		* St
		******************************************************/
		struct Extension
		{
			/**************************************************//*!
			*  @brief  The name of the project that the
			*          serializer is part of.
			******************************************************/
			const QString project;

			/**************************************************//*!
			*  @brief  The cateogry of the project that the
			*          serializer is part of.
			******************************************************/
			const QString category;

			/**************************************************//*!
			*  @brief  Contains the project serializer.
			******************************************************/
			const Serializer *serializer;
		};
	}
}
