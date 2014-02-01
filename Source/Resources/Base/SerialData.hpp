/**
 *  @file SerialData.hpp
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
#ifndef NGM__SERIALDATA__H
#define NGM__SERIALDATA__H
#include <cstdint>
#include <QMap>
#include <QString>
#include <QVector>
#include "Variant.hpp"

namespace NGM
{
	namespace Resource
	{
		struct Content;

		/**************************************************//*!
		*	@brief	Contains SerialData identifiers. As a
		*			convention, these are in the formated
		*			with the first four characters as the
		*			plugin identifier and the last four for
		*			the actual class identifier.
		******************************************************/
		namespace SerialID
		{
			const uint64_t Object		=	0x4e474d2d6f626a74;
			const uint64_t Image		=	0x4e474d2d696d6765;
			const uint64_t Animation	=	0x4e474d2d616e696d;
			const uint64_t Blob			=	0x4e474d2d626c6f62;
			const uint64_t Resource		=	0x4e474d2d72737263;
			const uint64_t Variant		=	0x4e474d2d7661726e;
		}

		/**************************************************//*!
		*	@brief	Represents serialized data.
		******************************************************/
		struct SerialData
		{

			typedef void (*CleanFunc)();

			/**************************************************//*!
			*	@brief	Stores a unique identifier. Each subclass
			*			should have unique numbers, so that it is
			*			easier to cast.
			******************************************************/
			const uint64_t identifier;

		protected:

			/**************************************************//*!
			*	@brief	Only inherited fields can identify.
			******************************************************/
			CleanFunc Clean;

			/**************************************************//*!
			*	@brief	Only inherited fields can identify.
			******************************************************/
			SerialData(const uint64_t &identifier)
				: identifier(identifier) {}

		private:

			/**************************************************//*!
			*	@brief	Using this class directly is prohibited.
			******************************************************/
			SerialData() : identifier(0) {}

		};

		/**************************************************//*!
		*	@brief	Contains data as children.
		******************************************************/
		struct SerialObject: SerialData
		{
			/**************************************************//*!
			*	@brief	Uses SerialID::Object.
			******************************************************/
			SerialObject() : SerialData(SerialID::Object) {}

			/**************************************************//*!
			*	@brief	A group of children.
			******************************************************/
			QMap<QString, SerialData*> children;

			/**************************************************//*!
			*	@brief	A group of attributes
			******************************************************/
			QMap<QLatin1String, QLatin1String> attributes;
		};

		/**************************************************//*!
		*	@brief	An image in the serial data.
		******************************************************/
		struct SerialImage : SerialData
		{
			/**************************************************//*!
			*	@brief	Uses SerialID::Image.
			******************************************************/
			SerialImage() : SerialData(SerialID::Image), image(nullptr) {}

			/**************************************************//*!
			*	@brief	An image.
			******************************************************/
			QImage *image;
		};

		/**************************************************//*!
		*	@brief	An animation in the serial data.
		******************************************************/
		struct SerialAnimation: SerialData
		{
			/**************************************************//*!
			*	@brief	Uses SerialID::Animation.
			******************************************************/
			SerialAnimation() : SerialData(SerialID::Animation) {}

			/**************************************************//*!
			*	@brief	A group of images.
			******************************************************/
			QVector<QImage*> images;
		};

		/**************************************************//*!
		*	@brief	Stores raw binary data.
		******************************************************/
		struct SerialBlob: SerialData
		{
			/**************************************************//*!
			*	@brief	Uses SerialID::Blob.
			******************************************************/
			SerialBlob() : SerialData(SerialID::Blob) {}

			/**************************************************//*!
			*	@brief	Contains the data.
			******************************************************/
			char *data;
		};

		/**************************************************//*!
		*	@brief	Stores indexed resources.
		******************************************************/
		struct SerialResource : SerialData
		{
			/**************************************************//*!
			*	@brief	Uses SerialID::Resource.
			******************************************************/
			SerialResource() : SerialData(SerialID::Resource) {}

			/**************************************************//*!
			*	@brief	Contains all resources.
			******************************************************/
			QVector<Content*> resources;
		};

		/**************************************************//*!
		*	@brief	Stores indexed resources.
		******************************************************/
		struct SerialVariant : SerialData
		{
			/**************************************************//*!
			*	@brief	Uses SerialID::Variant.
			******************************************************/
			SerialVariant() : SerialData(SerialID::Variant) {}

			/**************************************************//*!
			*	@brief	Contains all resources.
			******************************************************/
			Variant value;
		};
	}
}

#endif // NGM__SERIALDATA__H
