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
#include "Loader.hpp"

namespace NGM
{
	namespace API
	{
		/**************************************************//*!
		*  @brief  Contains file meta-data and loader.
		******************************************************/
		struct Project
		{

			/**************************************************//*!
			*  @brief  The type of project. It either contains
			*          multiple files and is a Group, or it is a
			*          standalone file and is a Single.
			******************************************************/
			enum Type
			{
				Group	= 0,
				Single	= 1
			};

			/**************************************************//*!
			*  @brief  Contains the name of the project.
			******************************************************/
			const QString name;

			/**************************************************//*!
			*  @brief  The category of which the project belongs
			*          to.
			******************************************************/
			const QString category;

			/**************************************************//*!
			*  @brief  Contains a short description on the
			*          project.
			******************************************************/
			const QString description;

			/**************************************************//*!
			*  @brief  Stores the project type.
			******************************************************/
			const Type type;

			/**************************************************//*!
			*  @brief  Contains the file loader.
			******************************************************/
			Loader loader;
		};
	}
}
