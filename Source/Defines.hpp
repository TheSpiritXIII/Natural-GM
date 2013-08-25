/**
 *  @file Defines.hpp
 *	@section License
 *
 *      Copyright (C) 2013 Daniel Hrabovcak
 *
 *      This file is a part of the Natural GM IDE. MIT License.
 *
 *      Permission is hereby granted, free of charge, to any person obtaining a copy
 *		of this software and associated documentation files (the "Software"), to deal
 *		in the Software without restriction, including without limitation the rights
 *		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *		copies of the Software, and to permit persons to whom the Software is
 *		furnished to do so, subject to the following conditions:
 *
 *		The above copyright notice and this permission notice shall be included in
 *		all copies or substantial portions of the Software.
 *
 *		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *		THE SOFTWARE.
**/
#ifndef _NGM_DEFINES__HPP
#define _NGM_DEFINES__HPP
#include "../Global.hpp"
#include <string>

namespace NGM
{
	/**************************************************//*!
	*	@brief	This namespace contains default projects.
	******************************************************/
	namespace Definition
	{
		const QString General = QStringLiteral("General");
		const QString PlainText = QStringLiteral("Plain Text");
		const QString PlainTextDesc = QStringLiteral("A text file encoded with UTF-8.");
		const QString RichText = QStringLiteral("Rich Text");
		const QString RichTextDesc = QStringLiteral("A text based format that supports formatting.");
		const QString GMLScript = QStringLiteral("GML Script");
		const QString GMLScriptDesc = QStringLiteral("A scripting language used in GameMaker and other game engines. GML is a C-based language based around rapid game developement.");
		const QString GMOther = QStringLiteral("GameMaker-Other");
		const QString GMStudio = QStringLiteral("GameMaker-Studio");
		const QString GMStudioProj = QStringLiteral("GameMaker Studio Project");
		const QString GMStudioProjDesc = QStringLiteral("An XML based file format that is compatible with GameMaker Studio 1.1 and higher.\n");
		const QString GMStudioProjComp = QStringLiteral("GameMaker Studio Project Compressed");
		const QString GMLegacy = QStringLiteral("GameMaker-Legacy");
	}

	/**************************************************//*!
	*	@brief	This namespace contains default types.
	******************************************************/
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
}

#endif // _NGM_DEFINES__HPP
