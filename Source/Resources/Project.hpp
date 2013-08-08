/**
 *  @file Project.hpp
 *  @brief Declares a project class that holds metadata.
 *
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
#ifndef _NGM_RESOURCE_PROJECT__HPP
#define _NGM_RESOURCE_PROJECT__HPP
#include "Type.hpp"
#include "Global.hpp"
#include <QString>
#include <QIcon>

namespace NGM
{
	namespace Resource
	{
		class Serializer;

		class Project
		{
		public:

			/*! Contains serializer which does the actual loading. */
			Serializer *serializer;

			/*! The type of resource item type, or NULL if it is not a type. */
			Type *type;

			/*! The name of the project type. */
			//QString name;

			/*! The category of which the project belongs to. */
			QString category;

			/*! Contains a short description of the project type. */
			QString description;

			/*! Contains a list of extensions used in the project type. */
			QStringList extensions;

			/*! Creates the project. */
			Project(Serializer *serializer, Type *type,
					QString category, QString description, QStringList extensions) :
				serializer(serializer), type(type), category(category),
				description(description), extensions(extensions) {}
		};

		const QString General("General");
		const QString PlainText("Plain Text");
		const QString PlainTextDesc("A text file encoded with UTF-8.");
		const QString RichText("Rich Text");
		const QString RichTextDesc("A text based format that supports formatting.");

		const QString GMLScript("GML Script");
		const QString GMLScriptDesc("A scripting language used in "
		"GameMaker and other game engines. GML is a C-based language "
		"based around rapid game developement.");
		const QString GMOther("GameMaker-Other");
		const QString GMStudio("GameMaker-Studio");
		const QString GMStudioProj("GameMaker Studio Project");
		const QString GMStudioProjDesc("An XML based file format "
		"that is compatible with GameMaker Studio 1.1 and higher.\n");
		const QString GMStudioProjComp("GameMaker Studio Project Compressed");
		const QString GMLegacy("GameMaker-Legacy");
	}
}

#endif // _NGM_RESOURCE_PROJECT__HPP
