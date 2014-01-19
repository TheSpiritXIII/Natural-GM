/**
 *  @file ToolPlugin.hpp
 *	@section License
 *
 *      Copyright (C) 2013-2014 Daniel Hrabovcak
 *
 *      This file is part of the Natural GM IDE.
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
#ifndef NGM__TOOLPLUGIN__HPP
#define NGM__TOOLPLUGIN__HPP
#include "SerialPlugin.hpp"

namespace NGM
{
	namespace Manager
	{
		class PropertyManager;
	}
	namespace Resource
	{
		/**************************************************//*!
		*	@brief	A function that is given the ability to
		*			edit application properties. This is the
		*			main plugin function.
		******************************************************/
		typedef void (*ToolPluginMainFunc)(Manager::PropertyManager *manager);

		/**************************************************//*!
		*	@brief	Contains a function, with a name and a
		*			visibility marker.
		******************************************************/
		struct ToolPluginFunction
		{
			/**************************************************//*!
			*	@brief	The name of the function.
			******************************************************/
			QString name;

			/**************************************************//*!
			*	@brief	The actual function.
			******************************************************/
			ToolPluginMainFunc main;

			/**************************************************//*!
			*	@brief	Defines whether or not the function is
			*			visible on the toolbar/menubar.
			******************************************************/
			bool visible;
		};

		/**************************************************//*!
		*	@brief	A plugin that is called through a tool
		*			button.
		*
		* This type of class is needed if you're using ABI
		* independent functions - that is, you do not create
		* any widgets (although you are allowed to create
		* them as long as you do not attach it to the main
		* application).
		*
		* There are other limitations. You are not allowed to
		* call any virtual functions from the main
		* application. This is because compilers have
		* implementation dependent vtables, so calling a
		* virtual method created using a different compiler
		* can lead to undesirable consequences.
		******************************************************/
		struct ToolPlugin : SerialPlugin
		{
			ToolPlugin(const PluginRequestFunc request_,
					   const SerialPluginFunc serialize_,
					   const ToolPluginFunction * const functions_,
					   const size_t functionSize_ = 1,
					   const QString *dependencies_ = nullptr,
					   const size_t dependencySize_ = 0) :
				SerialPlugin(request_, serialize_), functions(functions_),
				functionSize(functionSize_), dependencies(dependencies_),
				dependencySize(dependencySize_) {}

			/**************************************************//*!
			*	@brief	Contains a list of functions. Other
			*			plugins are able to call these functions.
			*	@see	functionSize
			******************************************************/
			const ToolPluginFunction * const functions;

			/**************************************************//*!
			*	@brief	Contains the numbers of functions.
			******************************************************/
			const size_t functionSize;

			/**************************************************//*!
			*	@brief	A list of all of the other plugin that
			*			this plugin is dependent on.
			*	@see	dependencySize;
			******************************************************/
			const QString *dependencies;

			/**************************************************//*!
			*	@brief	Contains the numbers of depedencies.
			******************************************************/
			const size_t dependencySize;
		};
	}
}

#endif // NGM__TOOLPLUGIN__HPP
