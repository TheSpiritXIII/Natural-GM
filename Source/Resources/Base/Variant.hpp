/**
 *  @file Variant.hpp
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
#ifndef _NGM_RESOURCE_VARIANT__HPP
#define _NGM_RESOURCE_VARIANT__HPP
#include <cstdint>
#include <QIcon>
#include <QImage>
#include <QPixmap>
#include "Vector.hpp"

namespace NGM
{
	namespace Resource
	{
		/**************************************************//*!
		*	@brief	Stores a variety of different data types.
		******************************************************/
		class Variant
		{
		public:

			/**************************************************//*!
			*	@brief	By default, variants are "None" type.
			*	@see	Type
			******************************************************/
			Variant() : _type(None) {}

			/**************************************************//*!
			*	@brief	Contains all possible variable types.
			******************************************************/
			enum Type : uint8_t
			{
				None		=	0,
				Int8		=	1,
				Int16		=	2,
				Int32		=	3,
				UInt8		=	4,
				UInt16		=	5,
				UInt32		=	6,
				CharPtr		=	7,
				Pixmap		=	8,
				Image		=	9,
				PixmapVec	=	10,
				ImageVec	=	11,
				Icon		=	12
			};

			/**************************************************//*!
			*	@brief	Returns if the current value is the
			*			quested value type.
			******************************************************/
			inline bool isType(const Type &type) const
			{
				return type == _type;
			}

			Variant(char *value)
			{
				setCharPtr(value);
			}

			Variant(Vector<QImage*> *value)
			{
				setImageVec(value);
			}

			inline void setInt8(int8_t value)
			{
				_type = Int8;
				int8_ = value;
			}

			inline void setCharPtr(char *value)
			{
				_type = CharPtr;
				charptr_ = value;
			}

			inline void setPixmap(QPixmap *value)
			{
				_type = Pixmap;
				pixmap_ = value;
			}

			inline void setImage(QImage *value)
			{
				_type = Image;
				image_ = value;
			}

			inline void setPixmapVec(Vector<QPixmap*> *value)
			{
				_type = PixmapVec;
				pixmapvec_ = value;
			}

			inline void setImageVec(Vector<QImage*> *value)
			{
				_type = ImageVec;
				imagevec_ = value;
			}

			inline void setIcon(QIcon *value)
			{
				_type = Icon;
				icon_ = value;
			}

			inline char *charPtr()
			{
				return charptr_;
			}

			inline QIcon *icon()
			{
				return icon_;
			}

		private:

			/**************************************************//*!
			*	@brief	Stores the current type. It is changed
			*			when the value is changed.
			******************************************************/
			Type _type;

			union
			{
				int8_t				int8_;
				int16_t				int16_;
				int32_t				int32_;
				uint8_t				uint8_;
				uint16_t			uint16_;
				uint32_t			uint32_;
				char*				charptr_;
				QPixmap*			pixmap_;
				QImage*				image_;
				Vector<QPixmap*>*	pixmapvec_;
				Vector<QImage*>*	imagevec_;
				QIcon*				icon_;
			};
		};
	}
}

#endif
