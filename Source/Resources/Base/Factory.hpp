/**
 *  @file Editor.hpp
 *	@section License
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
#ifndef _NGM_FACTORY__HPP
#define _NGM_FACTORY__HPP
#include <QString>

namespace NGM
{
	namespace Model
	{
		class ResourceProjectItem;
	}
	namespace Widget
	{
		class ResourceTab;
	}
	namespace Resource
	{
		class Editor;

		/**************************************************//*!
		*	@brief	Creates an editor and stores its name.
		******************************************************/
		class Factory
		{
		public:

			/**************************************************//*!
			*	@brief	Creates a factory with the indicated
			*			name and indicated creator.
			*	@param	create A pointer to the function that
			*			creates a new instance of the editor.
			*	@see	name
			******************************************************/
			Factory(const QString &name, Editor *(* const create)
					(const Model::ResourceProjectItem * const item,
					Widget::ResourceTab * const tab));

			/**************************************************//*!
			*	@brief	The name of the editor type.
			******************************************************/
			const QString name;

			/**************************************************//*!
			*	@brief	Creates the editor.
			******************************************************/
			Editor *(* const create)(const Model::ResourceProjectItem * const item,
									 Widget::ResourceTab * const tab);
		};
	}
}

#endif // _NGM_FACTORY__HPP
