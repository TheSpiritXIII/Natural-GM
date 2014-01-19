/**
 *  @file Variant.hpp
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
#ifndef NGM__RESOURCE_VARIANT__HPP
#define NGM__RESOURCE_VARIANT__HPP
#include <cstdint>
#include <QIcon>
#include <QImage>
#include <QPixmap>
#include <QVector>
#include <QString>

namespace NGM
{
	namespace Resource
	{
		/**************************************************//*!
		*	@brief	Stores a variety of different data types.
		*
		* Most pointers stored here are not deleted.
		* Currently, the only exception to this rule is the
		* StringVal type, which allocates its own data.
		******************************************************/
		class Variant
		{
		public:

			/**************************************************//*!
			*	@brief	Contains all possible variable types.
			******************************************************/
			enum Type : char
			{
				None		=	0,
				Int			=	1,
				Char		=	2,
				Short		=	3,
				Long		=	4,
				UInt		=	5,
				UChar		=	6,
				UShort		=	7,
				ULong		=	8,
				CharPtr		=	9,
				Pixmap		=	10,
				Image		=	11,
				PixmapVec	=	12,
				ImageVec	=	13,
				Icon		=	14,
				String		=	15,
				StringVal	=	16
			};

			/**************************************************//*!
			*	@brief	By default, variants are "None" type.
			*	@see	Type
			******************************************************/
			Variant() : _type(None) {}

			/**************************************************//*!
			*	@brief	Clears the variant.
			******************************************************/
			~Variant()
			{
				clear();
			}

			/**************************************************//*!
			*	@brief	Deletes the current variable. If you are
			*			changing variant types, you must always
			*			call this first.
			******************************************************/
			void clear()
			{
				switch(_type)
				{
				case StringVal:
					delete stringval_;
					stringval_ = nullptr;
					return;
				default:
					return;
				}
			}

			/**************************************************//*!
			*	@brief	Returns if the current value is the
			*			quested value type.
			******************************************************/
			inline bool isType(const Type &type) const
			{
				return type == _type;
			}

			Variant(int value)
			{
				setInt(value);
			}

			Variant(char value)
			{
				setChar(value);
			}

			Variant(short value)
			{
				setShort(value);
			}

			Variant(long value)
			{
				setLong(value);
			}

			// fill in the blanks.

			Variant(char *value)
			{
				setCharPtr(value);
			}

			Variant(QVector<QImage*> *value)
			{
				setImageVec(value);
			}

			inline void setInt(int value)
			{
				_type = Int;
				int_ = value;
			}

			inline void setChar(char value)
			{
				_type = Char;
				char_ = value;
			}

			inline void setShort(short value)
			{
				_type = Short;
				short_ = value;
			}

			inline void setLong(long value)
			{
				_type = Long;
				long_ = value;
			}

			inline void setUInt(unsigned int value)
			{
				_type = UInt;
				uint_ = value;
			}

			inline void setUChar(unsigned char value)
			{
				_type = UChar;
				uchar_ = value;
			}

			inline void setUShort(unsigned short value)
			{
				_type = UShort;
				ushort_ = value;
			}

			inline void setUInt64(unsigned long value)
			{
				_type = ULong;
				ulong_ = value;
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

			inline void setPixmapVec(QVector<QPixmap*> *value)
			{
				_type = PixmapVec;
				pixmapvec_ = value;
			}

			inline void setImageVec(QVector<QImage*> *value)
			{
				_type = ImageVec;
				imagevec_ = value;
			}

			inline void setIcon(QIcon *value)
			{
				_type = Icon;
				icon_ = value;
			}

			inline void setString(QString *value)
			{
				_type = String;
				string_ = value;
			}

			inline void setStringVal(const QString &value)
			{
				_type = StringVal;
				stringval_ = new QString(value);
			}

			inline int getInt()
			{
				return int_;
			}

			inline short getChar()
			{
				return char_;
			}

			inline int getShort()
			{
				return short_;
			}

			inline long getLong()
			{
				return long_;
			}

			inline unsigned int getUInt()
			{
				return uint_;
			}

			inline unsigned char getUChar()
			{
				return uchar_;
			}

			inline unsigned short getUShort()
			{
				return ushort_;
			}

			inline unsigned long getULong()
			{
				return ulong_;
			}

			inline char *getCharPtr()
			{
				return charptr_;
			}

			inline QPixmap *getPixmap()
			{
				return pixmap_;
			}

			inline QImage *getImage()
			{
				return image_;
			}

			inline QVector<QPixmap*> *getPixmapVec()
			{
				return pixmapvec_;
			}

			inline QVector<QImage*> *getImageVec()
			{
				return imagevec_;
			}

			inline QIcon *getIcon()
			{
				return icon_;
			}

			inline QString *getString()
			{
				return string_;
			}

			inline QString &getStringVal()
			{
				return (*stringval_);
			}

		private:

			/**************************************************//*!
			*	@brief	Stores the current type. It is changed
			*			when the value is changed.
			******************************************************/
			Type _type;

			union
			{
				int					int_;
				char				char_;
				short				short_;
				long			long_;
				unsigned int		uint_;
				unsigned char		uchar_;
				unsigned short		ushort_;
				unsigned long	ulong_;
				char*				charptr_;
				QPixmap*			pixmap_;
				QImage*				image_;
				QVector<QPixmap*>*	pixmapvec_;
				QVector<QImage*>*	imagevec_;
				QIcon*				icon_;
				QString*			string_;
				QString*			stringval_;
			};
		};
	}
}

#endif // NGM__RESOURCE_VARIANT__HPP
