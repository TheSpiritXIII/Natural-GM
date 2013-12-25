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
#include <string>
#include <list>
#include <map>
#include <QString>
using std::string;
using std::list;
using std::map;

namespace NGM
{
	namespace Resource
	{
		class SerialData;
	}

	/**************************************************//*!
	*	@brief	Manages a plugin interface.
	******************************************************/
	class Plugin
	{
	public:

		/**************************************************//*!
		*	@brief	Possible requests that can be requested
		*			for information.
		******************************************************/
		enum Request
		{
			Name			=	0, // The name of the plugin.
			Version			=	1, // The version number.
			Author			=	2, // The author of the plugin.
			Website			=	3, // The website where the plugin is hosted.
			Description		=	4, // A brief description of the plugin.
			Contributors	=	5, // A list of contributors.
		};

		/**************************************************//*!
		*	@brief	A function pointer that plugins are able
		*			to create and share.
		******************************************************/
		typedef Resource::SerialData *(*Function)(Resource::SerialData);

		/**************************************************//*!
		*	@brief	Called when the plugin is loaded.
		******************************************************/
		virtual void init() {}

		/**************************************************//*!
		*	@brief	Called when the plugin is unloaded.
		******************************************************/
		virtual void destroy() {}

		/**************************************************//*!
		*	@brief	Called when the user activates the
		*			plugin.
		******************************************************/
		virtual void activate() {}

		/**************************************************//*!
		*	@brief	Extendible get function.
		*	@see	Request
		******************************************************/
		virtual QString get(const Request &request) const = 0;

		/**************************************************//*!
		*	@brief	Returns whether or not this plugin can
		*			be placed in the toolbar or menu.
		******************************************************/
		inline float priority() const
		{
			return _priority;
		}

		/**************************************************//*!
		*	@brief	Returns the function of the indicated
		*			name. Other plugins may call this.
		******************************************************/
		inline Function function(const string &name) const
		{
			return _functions.find(name)->second;
		}

		/**************************************************//*!
		*	@brief	A list of all of the other plugin that
		*			this plugin is dependent on.
		******************************************************/
		const list<QString> *dependencies() const
		{
			return &_dependencies;
		}

	protected:

		/**************************************************//*!
		*	@brief	Constructs a plugin with a priority.
		******************************************************/
		Plugin(const float &priority_ = 0) : _priority(priority_) {}

		/**************************************************//*!
		*	@brief	Constructs a plugin with the indicated
		*			priority and dependencies
		******************************************************/
		Plugin(const float &priority_, const list<QString> &dependencies_) :
			_priority(priority_), _dependencies(dependencies_) {}

		/**************************************************//*!
		*	@brief	Constructs a plugin with the indicated
		*			priority, dependencies and functions.
		******************************************************/
		Plugin(const float &priority_, const list<QString> &dependencies_,
			   const map<string, Function> &functions_) : _priority(priority_),
			_dependencies(dependencies_), _functions(functions_) {}

	private:

		/**************************************************//*!
		*	@brief	The priority of the plugin. A higher
		*			priority means that the plugin is
		*			initialized earlier.
		******************************************************/
		float _priority;

		/**************************************************//*!
		*	@brief	Stores any dependencies the plugin might
		*			have.
		******************************************************/
		list<QString> _dependencies;

		/**************************************************//*!
		*	@brief	Stores internal functions that other
		*			plugins may call.
		******************************************************/
		map<string, Function> _functions;

	};
}

#endif // NGM__PLUGIN__HPP
