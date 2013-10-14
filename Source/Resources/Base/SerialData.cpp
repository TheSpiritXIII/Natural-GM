/**
 *  @file SerialData.cpp
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
#include "SerialData.hpp"

namespace NGM
{
	namespace Resource
	{
		const uint8_t *SerialData::getUUID() const
		{
			return &SerialUUID::undefined[0];
		}

		SerialObject *SerialData::asObject()
		{
			return nullptr;
		}

		SerialImage *SerialData::asImage()
		{
			return nullptr;
		}

		SerialAnimation *SerialData::asAnimation()
		{
			return nullptr;
		}

		SerialBlob *SerialData::asBlob()
		{
			return nullptr;
		}

		SerialResource *SerialData::asResource()
		{
			return nullptr;
		}

		SerialVariant *SerialData::asVariant()
		{
			return nullptr;
		}

		const uint8_t *SerialObject::getUUID() const
		{
			return &SerialUUID::object[0];
		}

		SerialObject::~SerialObject()
		{
			for (auto &i : children)
			{
				delete i.second;
			}
		}

		SerialObject *SerialObject::asObject()
		{
			return this;
		}

		const uint8_t *SerialImage::getUUID() const
		{
			return &SerialUUID::image[0];
		}

		SerialImage::SerialImage() : image(nullptr)
		{
			// Intentionally empty.
		}

		SerialImage::~SerialImage()
		{
			delete image;
		}

		SerialImage *SerialImage::asImage()
		{
			return this;
		}

		const uint8_t *SerialAnimation::getUUID() const
		{
			return &SerialUUID::animation[0];
		}

		SerialAnimation::~SerialAnimation()
		{
			for (auto &i : images)
			{
				delete i;
			}
		}

		SerialAnimation *SerialAnimation::asAnimation()
		{
			return this;
		}

		const uint8_t *SerialBlob::getUUID() const
		{
			return &SerialUUID::blob[0];
		}

		SerialBlob *SerialBlob::asBlob()
		{
			return this;
		}

		const uint8_t *SerialResource::getUUID() const
		{
			return &SerialUUID::resource[0];
		}

		SerialResource *SerialResource::asResource()
		{
			return this;
		}

		const uint8_t *SerialVariant::getUUID() const
		{
			return &SerialUUID::variant[0];
		}

		SerialVariant *SerialVariant::asVariant()
		{
			return this;
		}
	}
}
