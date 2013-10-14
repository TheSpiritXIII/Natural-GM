/**
 *  @file TextType.hpp
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
#ifndef _NGM_TEXTTYPE__HPP
#define _NGM_TEXTTYPE__HPP
#include "Type.hpp"

namespace NGM
{
	namespace Resource
	{
		class TextType : public Type
		{
		public:

			/**************************************************//*!
			*	@return	A usable widget for this type.
			******************************************************/
			Editor *widget(const Model::ResourceProjectItem * const item,
						   Widget::ResourceTab * const tab) const;

			/**************************************************//*!
			*	@brief	Sets up constant metadata.
			******************************************************/
			TextType(QString name, QString plural);
		};
	}
}

#endif // _NGM_TEXTTYPE__HPP
