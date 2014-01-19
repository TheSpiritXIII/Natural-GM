/**
 *  @file Plugin.hpp
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
#ifndef NGM__PLUGIN__HPP
#define NGM__PLUGIN__HPP
#include "ToolPlugin.hpp"

namespace NGM
{
	namespace Manager
	{
		class GlobalManager;
	}
	namespace Resource
	{
		/**************************************************//*!
		*	@brief	A plugin function that gives access to
		*			the global manager which is able to
		*			access all other managers.
		******************************************************/
		typedef void *(*PluginMainFunc)(Manager::GlobalManager *manager);

		/**************************************************//*!
		*	@brief	Manages a generic plugin interface.
		*
		* This interface is mainly for plugins that create
		* widgets somewhere alongs its lifetime, usually
		* being a new editor.
		*
		* This plugin must also be compiled with the same
		* compiler that the
		******************************************************/
		struct Plugin : ToolPlugin
		{
			Plugin(const PluginRequestFunc request_,
				   const PluginMainFunc init_,
				   const PluginMainFunc destroy_,
				   const float priority_ = 100,
				   const SerialPluginFunc serialize_ = nullptr,
				   const ToolPluginFunction * const functions_ = nullptr,
				   const size_t functionSize_ = 1,
				   const QString *dependencies_ = nullptr,
				   const size_t dependencySize_ = 0) :
				ToolPlugin(request_,
						   serialize_,
						   functions_,
						   functionSize_,
						   dependencies_,
						   dependencySize_),
				init(init_), destroy(destroy_), priority(priority_) {}

			/**************************************************//*!
			*	@brief	Called when the plugin is loaded.
			******************************************************/
			const PluginMainFunc init;

			/**************************************************//*!
			*	@brief	Called when the plugin is unloaded.
			******************************************************/
			const PluginMainFunc destroy;

			/**************************************************//*!
			*	@brief	The priority. A higher priority goes
			*			first.
			******************************************************/
			const float priority;

			/**************************************************//*!
			*	@brief	Returns the higher priority. A plugin is
			*			before another if it has a higher one.
			******************************************************/
			bool operator <(const Plugin &right)
			{
				return priority > right.priority;
			}
		};
	}
}

#endif // NGM__PLUGIN__HPP
