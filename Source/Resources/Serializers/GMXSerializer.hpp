/**
 *  @file GMXSerializer.hpp
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
#ifndef _NGM_GMXSERIALIZER__HPP
#define _NGM_GMXSERIALIZER__HPP
#include "Serializer.hpp"

namespace NGM
{
	namespace Resource
	{
		struct GMXSerializer : Serializer
		{
		public:

			/**************************************************//*!
			*	@brief	Inputs resource data to editor data.
			******************************************************/
			void read(Editor *editor, Resource *resource) const;

			/**************************************************//*!
			*	@brief	Outputs editor data to resource data.
			******************************************************/
			void write(Editor *editor, Resource *resource) const;

			/**************************************************//*!
			*	@brief	Creates the project tree structure.
			******************************************************/
			void structure(Model::ResourceProjectItem *item) const;

			/**************************************************//*!
			*	@brief	Requests a restructure of the indicated item.
			******************************************************/
			void restructure(Model::ResourceProjectItem *item) const;

		};
	}
}

#endif // _NGM_GMXSERIALIZER__HPP
