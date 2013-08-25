/**
 *  @file Project.hpp
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
#ifndef _NGM_RESOURCE_PROJECT__HPP
#define _NGM_RESOURCE_PROJECT__HPP
#include "Type.hpp"
#include <QString>
#include <QIcon>

namespace NGM
{
	namespace Resource
	{
		struct Serializer;

		/**************************************************//*!
		*	@brief	Metadata for project types.
		******************************************************/
		struct Project
		{

			/**************************************************//*!
			*	@brief	The serializer is what loads and saves
			*			the resources used in this project type.
			******************************************************/
			const Serializer * const serializer;

			/**************************************************//*!
			*	@brief	The resource item type. For icons and actions.
			******************************************************/
			const Type * const type;

			/**************************************************//*!
			*	@brief	The category of which the project belongs to.
			******************************************************/
			const QString category;

			/**************************************************//*!
			*	@brief	Contains a short description of this
			*			project type.
			******************************************************/
			const QString description;

			/**************************************************//*!
			*	@brief	Contains a list of extensions used in the
			*			project type.
			******************************************************/
			const QStringList extensions;

			/**************************************************//*!
			*	@brief	Initializes all member variables.
			******************************************************/
			Project(const Serializer * const serializer, const Type * const type,
					const QString category, const QString description, const QStringList extensions);

		};
	}
}

#endif // _NGM_RESOURCE_PROJECT__HPP
