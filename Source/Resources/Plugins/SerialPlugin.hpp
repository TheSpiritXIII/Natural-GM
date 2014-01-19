/**
 *  @file SerialPlugin.hpp
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
#ifndef NGM__SERIALPLUGIN__HPP
#define NGM__SERIALPLUGIN__HPP

namespace NGM
{
	namespace Manager
	{
		class ProjectManager;
	}
	namespace Resource
	{
		/**************************************************//*!
		*	@brief	Possible requests that can be requested
		*			for information from plugins.
		******************************************************/
		enum class Request : char
		{
			Name			=	0, // The name of the plugin.
			Version			=	1, // The version number.
			Author			=	2, // The author of the plugin.
			Website			=	3, // The website where the plugin is hosted.
			Description		=	4, // A brief description of the plugin.
			Contributors	=	5, // A list of contributors.
		};

		/**************************************************//*!
		*	@brief	A function that returns information about
		*			plugins to be used by plugins.
		*	@see	Request
		******************************************************/
		typedef const QString &(*PluginRequestFunc)(Request request);

		/**************************************************//*!
		*	@brief	A function that is given the ability to
		*			add new file formats.
		******************************************************/
		typedef void (*SerialPluginFunc)(Manager::ProjectManager *manager);

		/**************************************************//*!
		*	@brief	A plugin for the sole purpose of creating
		*			new file formats.
		******************************************************/
		struct SerialPlugin
		{
			SerialPlugin(const PluginRequestFunc request_,
						 const SerialPluginFunc serialize_) :
				request(request_), serialize(serialize_) {}

			/**************************************************//*!
			*	@brief	Function pointer to request information.
			*	@see	ToolPluginRequestFunc
			******************************************************/
			const PluginRequestFunc request;

			/**************************************************//*!
			*	@brief	A pointer to a function that creates new
			*			file formats.
			******************************************************/
			const SerialPluginFunc serialize;
		};
	}
}

#endif // NGM__SERIALPLUGIN__HPP
