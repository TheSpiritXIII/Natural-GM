/**
 *  @file Resource.hpp
 *  @brief Declares a basic resource class that holds bytes.
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
#ifndef _NGM_RESOURCE__HPP
#define _NGM_RESOURCE__HPP
#include "../Global.hpp"
#include <QString>
#include <string>
#include <vector>
#include <QByteArray>
#include "Type.hpp"

namespace NGM
{
	namespace Resource
	{
		//class Type;
		namespace Types
		{
			using std::string;

			/*! Basic types. */
			const string Path("FilePath");
			const string RichText("RichText");
			const string PlainText("PlainText");
			const string Table("PlainTable");

			/*! Programming based. */
			const string ProgrammingGLSL("Programming-GLSL");
			const string ProgrammingXML("Programming-XML");

			/*! Web Based. */
			const string WebCSS("Web-CSS");

			/*! Scripting Based. */
			const string ScriptingGML("Scripting-GML");
			const string ScriptingGMLObject("Scripting-GMLObject");

			/*! GameMaker Based. */
			const string GMSSprite("GMS-Sprite");
			const string GM8Sprite("GM8-Sprite");
			const string GM7Sprite("GM7-Sprite");
			const string GMSSound("GMS-Sound");
			const string GM8Sound("GM8-Sound");
			const string GMSBackground("GMS-Background");
			const string GM8Background("GM8-Background");
			const string GMSPath("GMS-Path");
			const string GM8Path("GM8-Path");
			const string GMSFont("GMS-Font");
			const string GM8Font("GM8-Font");
			const string GMSTimeline("GMS-Timeline");
			const string GM8Timeline("GM8-Timeline");
			const string GMSObject("GMS-Object");
			const string GM8Object("GM8-Object");
			const string GMSRoom("GMS-Room");
			const string GM8Room("GM8-Room");
		}

		class Resource
		{
		public:

			/*! Describes the bits used to check a resource's status. */
			enum StatusBits
			{
				Edited      =   0x01,//0b00000001,
				Loaded      =   0x02,//0b00000010,
				IsCached	=	0x04,//0b00000100,
				IsLoading	=	0x08,//0b00001000,
				HasError	=	0x10,//0b00010000,
				Reserved	=	0x20,//0b00100000,
				IsFilename	=	0x40,//0b01000000,
				Bit2		=	0x80//0b10000000
			};

			/*! Contains the status of the resource (eg. loaded or edited). */
			uint8_t status;

			/*! Contains the type identifier of the resource. */
			Type *type;

			/*! Stores all of the cached resource data. */
			QByteArray data;

			/*! Stores the file location of the resource, if there is one. */
			QString location;

			/*! Returns an icon for this resource. */
			virtual QIcon getIcon() { return type->icon; }

			/*! You must set type identifier to a resource. */
			Resource(Type *type, QByteArray data, QString location, uint8_t status = 0) :
				status(status), type(type), data(data), location(location) {}

			~Resource() {}
		};
	}
}

#endif // _NGM_RESOURCE__HPP
