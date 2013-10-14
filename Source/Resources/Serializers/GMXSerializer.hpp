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
#include "RapidXML.hpp"

namespace NGM
{
	namespace Resource
	{
		struct GMXSerializer : Serializer
		{
		public:

			/**************************************************//*!
			*	@brief	Sets the default settings.
			******************************************************/
			GMXSerializer();

			/**************************************************//*!
			*	@brief	Inputs resource data to editor data.
			******************************************************/
			void read(Editor *editor, Resource *resource, const SerializerOptions &options = 0) const;

			/**************************************************//*!
			*	@brief	Outputs editor data to resource data.
			******************************************************/
			void write(Editor *editor, Resource *resource, const SerializerOptions &options = 0) const;

			bool save(Model::ResourceProjectItem *item, QProgressBar *progressBar) const;

			/**************************************************//*!
			*	@brief	Creates the project tree structure.
			******************************************************/
			bool structure(Model::ResourceProjectItem *item, QProgressBar *progressBar) const;

			/**************************************************//*!
			*	@brief	Requests a restructure of the indicated item.
			******************************************************/
			void restructure(Model::ResourceProjectItem *item) const;

			/**************************************************//*!
			*	@brief	Destoys the indicated item.
			******************************************************/
			void destructure(Model::ResourceProjectItem *item) const;

		private:

			enum Types
			{
				Sprite,
				Sound,
				Background,
				Path,
				Script,
				Shader,
				Font,
				Timeline,
				Object,
				Room,
				Datafile,
				Extension,
				Constant,
				Size
			};

			/**************************************************//*!
			*	@brief	Adds sprite items recrusively.
			******************************************************/
			void addSprite(Model::ResourceGroupItem *item, rapidxml::xml_node<> *node,
				const Queue<Type*> &type, const SerializerOptions &options = 0) const;

			/**************************************************//*!
			*	@brief	Adds background items recrusively.
			******************************************************/
			void addBackground(Model::ResourceGroupItem *item, rapidxml::xml_node<> *node) const;

			/**************************************************//*!
			*	@brief	Adds sound items recrusively.
			******************************************************/
			void addSound(Model::ResourceGroupItem *item, rapidxml::xml_node<> *node) const;

			/**************************************************//*!
			*	@brief	Adds path items recrusively.
			******************************************************/
			void addPath(Model::ResourceGroupItem *item, rapidxml::xml_node<> *node) const;

			/**************************************************//*!
			*	@brief	Adds script items recrusively.
			******************************************************/
			void addScript(Model::ResourceGroupItem *item, rapidxml::xml_node<> *node) const;

			/**************************************************//*!
			*	@brief	Adds shader items recrusively.
			******************************************************/
			void addShader(Model::ResourceGroupItem *item, rapidxml::xml_node<> *node) const;

			/**************************************************//*!
			*	@brief	Adds timeline items recrusively.
			******************************************************/
			void addTimeline(Model::ResourceGroupItem *item, rapidxml::xml_node<> *node) const;

			/**************************************************//*!
			*	@brief	Adds font items recrusively.
			******************************************************/
			void addFont(Model::ResourceGroupItem *item, rapidxml::xml_node<> *node) const;

			/**************************************************//*!
			*	@brief	Adds object items recrusively.
			******************************************************/
			void addObject(Model::ResourceGroupItem *item, rapidxml::xml_node<> *node) const;

			/**************************************************//*!
			*	@brief	Adds room items recrusively.
			******************************************************/
			void addRoom(Model::ResourceGroupItem *item, rapidxml::xml_node<> *node) const;

			/**************************************************//*!
			*	@brief	Adds included file items recrusively.
			******************************************************/
			void addDatafile(Model::ResourceGroupItem *item, rapidxml::xml_node<> *node) const;

			/**************************************************//*!
			*	@brief	Adds extension items recrusively.
			******************************************************/
			void addExtension(Model::ResourceGroupItem *item, rapidxml::xml_node<> *node) const;

			void createTree(const char *typeName, const char *groupName, rapidxml::xml_document<> *document,
							Model::ResourceGroupItem *item, rapidxml::xml_node<> *node) const;
		};
	}
}

#endif // _NGM_GMXSERIALIZER__HPP
