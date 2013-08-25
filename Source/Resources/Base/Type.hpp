/**
 *  @file Type.hpp
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
#pragma once
#ifndef _NGM_TYPE__HPP
#define _NGM_TYPE__HPP
#include <QString>
#include <QAction>

namespace NGM
{
	namespace Widget
	{
		class ResourceTab;
	}
	namespace Resource
	{
		class Editor;

		/**************************************************//*!
		*	@brief	Metadata for resource types.
		******************************************************/
		class Type
		{
		public:

			/**************************************************//*!
			*	@brief	The human readable name for menus. This
			*			value is also used for loading the icon.
			******************************************************/
			const QString name;

			/**************************************************//*!
			*	@brief	The plural name. This is used in tabs and groups.
			******************************************************/
			const QString plural;

			/**************************************************//*!
			*	@brief	A visual representation of the type.
			*	@see	name
			******************************************************/
			QIcon icon;

			/**************************************************//*!
			*	@brief	The Qt based action for this type.
			******************************************************/
			QAction *action;

			/**************************************************//*!
			*	@return	A usable widget for this type.
			******************************************************/
			virtual Editor *widget(NGM::Widget::ResourceTab *parent = 0) const = 0;

			/**************************************************//*!
			*	@brief	Sets up constant metadata.
			******************************************************/
			Type(const QString &name, const QString &plural);

		};
	}
}

#endif // _NGM_Type__HPP
