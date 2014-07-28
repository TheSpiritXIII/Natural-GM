/*-
 *  Copyright (c) 2013 - 2014 Daniel Hrabovcak
 *
 *  This program is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or (at your
 *  option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 *  for more details.
**/
#pragma once

namespace NGM
{
	namespace API
	{
		/**************************************************//*!
		*  @brief  Contains real numbers.
		******************************************************/
		struct Variant
		{
			/**************************************************//*!
			*  @brief  Contains real numbers.
			******************************************************/
			enum Type : uint8_t
			{
				None      = 0,
				Int8      = 1,
				UInt8     = 2,
				Int16     = 3,
				UInt16    = 4,
				Int32     = 5,
				UInt32    = 6,
				Int64     = 7,
				UInt64    = 8,
				Float     = 9,
				Double    = 10,
			};
			Variant() : _type(None) {}
			Variant(char value)
			{
				setChar(value);
			}
			Variant(unsigned char value)
			{
				setUChar(value);
			}
			Variant(short value)
			{
				setShort(value);
			}
			Variant(unsigned short value)
			{
				setUShort(value);
			}
			Variant(int value)
			{
				setInt(value);
			}
			Variant(unsigned int value)
			{
				setUInt(value);
			}
			Variant(long value)
			{
				setLong(value);
			}
			Variant(unsigned long value)
			{
				setULong(value);
			}
			inline void setChar(char value)
			{
				_type = Int8;
				_c = value;
			}
			inline void setUChar(unsigned char value)
			{
				_type = UInt8;
				_uc = value;
			}
			inline void setShort(short value)
			{
				_type = Int16;
				_s = value;
			}
			inline void setUShort(unsigned short value)
			{
				_type = Int16;
				_us = value;
			}
			inline void setInt(int value)
			{
				_type = Int32;
				_i = value;
			}
			inline void setUInt(unsigned int value)
			{
				_type = UInt32;
				_ui = value;
			}
			inline void setLong(long value)
			{
				_type = Int64;
				_l = value;
			}
			inline void setULong(unsigned long value)
			{
				_type = UInt64;
				_ul = value;
			}
			inline bool isType(Type type)
			{
				return type == _type;
			}
		private:
			Type _type;
			union
			{
				int8_t   _c;
				uint8_t  _uc;
				int16_t  _s;
				uint16_t _us;
				int32_t  _i;
				int32_t  _ui;
				int64_t  _l;
				int64_t  _ul;
				float    _f;
				double   _d;
			};
		};
	}
}
