/**
 *  @file SerialData.cpp
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
#include "SerialData.hpp"

namespace NGM
{
	namespace Resource
	{
		const uint8_t *SerialData::getUUID()
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

		const uint8_t *SerialObject::getUUID()
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

		const uint8_t *SerialImage::getUUID()
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

		const uint8_t *SerialAnimation::getUUID()
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

		const uint8_t *SerialBlob::getUUID()
		{
			return &SerialUUID::blob[0];
		}

		SerialBlob *SerialBlob::asBlob()
		{
			return this;
		}

		const uint8_t *SerialResource::getUUID()
		{
			return &SerialUUID::resource[0];
		}

		SerialResource *SerialResource::asResource()
		{
			return this;
		}
	}
}
