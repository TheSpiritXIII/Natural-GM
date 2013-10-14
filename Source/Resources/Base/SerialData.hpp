/**
 *  @file SerialData.hpp
 *	@section License
 *
 *      Copyright (C) 2013 Daniel Hrabovcak and Josh Ventura
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
#ifndef _NGM_SERIALDATA__H
#define _NGM_SERIALDATA__H
#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <QImage>
#include <Variant.hpp>

namespace NGM
{
	namespace Resource
	{
		using std::map;
		using std::string;
		using std::vector;

		struct Resource;

		struct SerialData;
		struct SerialObject;
		struct SerialAttributes;
		struct SerialImage;
		struct SerialAnimation;
		struct SerialBlob;
		struct SerialResource;
		struct SerialVariant;

		/**************************************************//*!
		*	@brief	Contains SerialData identifiers. As a
		*			convention, these are in the format
		*			"[plugin]-[brief]", where "[plugin]" is
		*			the name of the plugin that created the
		*			ID, and "[brief]" is a brief description.
		******************************************************/
		namespace SerialUUID
		{
			const uint8_t undefined	[8]	=	{'U', 'N', 'D', 'E', 'F', 'I', 'N', 'D'};
			const uint8_t object	[8]	=	{'N', 'G', 'M', '-', 'o', 'b', 'j', 't'};
			const uint8_t image		[8]	=	{'N', 'G', 'M', '-', 'i', 'm', 'g', 'e'};
			const uint8_t animation	[8]	=	{'N', 'G', 'M', '-', 'a', 'n', 'i', 'm'};
			const uint8_t blob		[8]	=	{'N', 'G', 'M', '-', 'b', 'l', 'o', 'b'};
			const uint8_t resource	[8]	=	{'N', 'G', 'M', '-', 'r', 's', 'r', 'c'};
			const uint8_t variant	[8]	=	{'N', 'G', 'M', '-', 'v', 'a', 'r', 't'};
		}

		/**************************************************//*!
		*	@brief	Represents serialized data.
		******************************************************/
		struct SerialData
		{

			/**************************************************//*!
			*	@breif	Returns a unique identifier for class type.
			******************************************************/
			virtual const uint8_t *getUUID() const;

			/**************************************************//*!
			*	@brief	A safe cast to an object type.
			******************************************************/
			virtual SerialObject *asObject();

			/**************************************************//*!
			*	@brief	A safe cast to an image type.
			******************************************************/
			virtual SerialImage *asImage();

			/**************************************************//*!
			*	@brief	A safe cast to an animation type.
			******************************************************/
			virtual SerialAnimation *asAnimation();

			/**************************************************//*!
			*	@brief	A safe cast to a blob type.
			******************************************************/
			virtual SerialBlob *asBlob();

			/**************************************************//*!
			*	@brief	A safe cast to a resource type.
			******************************************************/
			virtual SerialResource *asResource();

			/**************************************************//*!
			*	@brief	A safe cast to a variant type.
			******************************************************/
			virtual SerialVariant *asVariant();

		};

		/**************************************************//*!
		*	@brief	Contains data as children.
		******************************************************/
		struct SerialObject: SerialData
		{
			/**************************************************//*!
			*	@brief	A group of children.
			******************************************************/
			map<string, SerialData*> children;

			/**************************************************//*!
			*	@brief	A group of attributes
			******************************************************/
			map<string, string> attributes;

			/**************************************************//*!
			*	@breif	Returns a unique identifier for class type.
			******************************************************/
			virtual const uint8_t *getUUID() const;

			/**************************************************//*!
			*	@brief	Removes all children.
			******************************************************/
			virtual ~SerialObject();

			/**************************************************//*!
			*	@brief	Returns this.
			******************************************************/
			virtual SerialObject *asObject();
		};

		/**************************************************//*!
		*	@brief	An image in the serial data.
		******************************************************/
		struct SerialImage : SerialData
		{
			/**************************************************//*!
			*	@brief	An image.
			******************************************************/
			QImage *image;

			/**************************************************//*!
			*	@brief	Sets a null image.
			******************************************************/
			SerialImage();

			/**************************************************//*!
			*	@breif	Returns a unique identifier for class type.
			******************************************************/
			virtual const uint8_t *getUUID() const;

			/**************************************************//*!
			*	@brief	Removes image data.
			******************************************************/
			virtual ~SerialImage();

			/**************************************************//*!
			*	@brief	Returns this.
			******************************************************/
			virtual SerialImage *asImage();
		};

		/**************************************************//*!
		*	@brief	An animation in the serial data.
		******************************************************/
		struct SerialAnimation: SerialData
		{
			/**************************************************//*!
			*	@brief	A group of images.
			******************************************************/
			vector<QImage*> images;

			/**************************************************//*!
			*	@breif	Returns a unique identifier for class type.
			******************************************************/
			virtual const uint8_t *getUUID() const;

			/**************************************************//*!
			*	@brief	Removes all image data.
			******************************************************/
			virtual ~SerialAnimation();

			/**************************************************//*!
			*	@brief	Returns this.
			******************************************************/
			virtual SerialAnimation *asAnimation();
		};

		/**************************************************//*!
		*	@brief	Stores raw binary data.
		******************************************************/
		struct SerialBlob: SerialData
		{
			/**************************************************//*!
			*	@brief	Contains the data.
			******************************************************/
			char *data;

			/**************************************************//*!
			*	@breif	Returns a unique identifier for class type.
			******************************************************/
			virtual const uint8_t *getUUID() const;

			/**************************************************//*!
			*	@brief	Returns this.
			******************************************************/
			virtual SerialBlob *asBlob();
		};

		/**************************************************//*!
		*	@brief	Stores indexed resources.
		******************************************************/
		struct SerialResource : SerialData
		{
			/**************************************************//*!
			*	@brief	Contains all resources.
			******************************************************/
			vector<Resource*> resources;

			/**************************************************//*!
			*	@breif	Returns a unique identifier for class type.
			******************************************************/
			virtual const uint8_t *getUUID() const;

			/**************************************************//*!
			*	@brief	Returns this.
			******************************************************/
			virtual SerialResource *asResource();
		};

		/**************************************************//*!
		*	@brief	Stores indexed resources.
		******************************************************/
		struct SerialVariant : SerialData
		{
			/**************************************************//*!
			*	@brief	Contains all resources.
			******************************************************/
			Variant variant;

			/**************************************************//*!
			*	@breif	Returns a unique identifier for class type.
			******************************************************/
			virtual const uint8_t *getUUID() const;

			/**************************************************//*!
			*	@brief	Returns this.
			******************************************************/
			virtual SerialVariant *asVariant();
		};
	}
}

#endif // _NGM_SERIALDATA__H
