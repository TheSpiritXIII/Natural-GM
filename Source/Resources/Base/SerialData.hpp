/**
 *  @file SerialData.hpp
 *	@section License
 *
 *      Copyright (C) 2013 Josh Ventura and Daniel Hrabovcak
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
#ifndef _NGM_SERIALDATA__H
#define _NGM_SERIALDATA__H
#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <QImage>
#include <QByteArray>

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
		}

		/**************************************************//*!
		*	@brief	Represents serialized data.
		******************************************************/
		struct SerialData
		{

			/**************************************************//*!
			*	@return	The unique identifier for this data type.
			******************************************************/
			virtual const uint8_t *getUUID();

			/**************************************************//*!
			*	@return	A safe cast to an object type.
			******************************************************/
			virtual SerialObject *asObject();

			/**************************************************//*!
			*	@return	A safe cast to an image type.
			******************************************************/
			virtual SerialImage *asImage();

			/**************************************************//*!
			*	@return	A safe cast to an animation type.
			******************************************************/
			virtual SerialAnimation *asAnimation();

			/**************************************************//*!
			*	@return	A safe cast to a blob type.
			******************************************************/
			virtual SerialBlob *asBlob();

			/**************************************************//*!
			*	@return	A safe cast to a resource type.
			******************************************************/
			virtual SerialResource *asResource();

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
			map<string, vector<char>> attributes;

			/**************************************************//*!
			*	@return	The unique identifier for this data type.
			******************************************************/
			virtual const uint8_t *getUUID();

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
			*	@return	The unique identifier for this data type.
			******************************************************/
			virtual const uint8_t *getUUID();

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
			*	@return	The unique identifier for this data type.
			******************************************************/
			virtual const uint8_t *getUUID();

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
			QByteArray data;

			/**************************************************//*!
			*	@return	The unique identifier for this data type.
			******************************************************/
			virtual const uint8_t *getUUID();

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
			*	@return	The unique identifier for this data type.
			******************************************************/
			virtual const uint8_t *getUUID();

			/**************************************************//*!
			*	@brief	Returns this.
			******************************************************/
			virtual SerialResource *asResource();
		};
	}
}

#endif // _NGM_SERIALDATA__H
