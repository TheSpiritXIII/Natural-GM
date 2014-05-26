/*-
 *  Copyright (c) 2014 Daniel Hrabovcak
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
#include "SerialData.hpp"

uint32_t NGM::API::SerialData::identifier() const
{
	return _identifier;
}

NGM::API::SerialData::SerialData(uint32_t identifier) :
  _identifier(identifier) {}

NGM::API::SerialObject *NGM::API::SerialData::toObject()
{
	return nullptr;
}

NGM::API::SerialImage *NGM::API::SerialData::toImage()
{
	return nullptr;
}

NGM::API::SerialAnimation *NGM::API::SerialData::toAnimation()
{
	return nullptr;
}

NGM::API::SerialBlob *NGM::API::SerialData::toBlob()
{
	return nullptr;
}

NGM::API::SerialPixmap *NGM::API::SerialData::toPixmap()
{
	return nullptr;
}

NGM::API::SerialIcon *NGM::API::SerialData::toIcon()
{
	return nullptr;
}

NGM::API::SerialVariant *NGM::API::SerialData::toVariant()
{
	return nullptr;
}

NGM::API::SerialObject::SerialObject() : SerialData(id()) {}

NGM::API::SerialObject *NGM::API::SerialObject::toObject()
{
	return this;
}

uint32_t NGM::API::SerialObject::id()
{
	return 0x4E01;
}

NGM::API::SerialImage::SerialImage() : SerialData(id()) {}

NGM::API::SerialImage *NGM::API::SerialImage::toImage()
{
	return this;
}

uint32_t NGM::API::SerialImage::id()
{
	return 0x4E02;
}

NGM::API::SerialAnimation::SerialAnimation() : SerialData(id()) {}

NGM::API::SerialAnimation *NGM::API::SerialAnimation::toAnimation()
{
	return this;
}

uint32_t NGM::API::SerialAnimation::id()
{
	return 0x4E03;
}

NGM::API::SerialBlob::SerialBlob() : SerialData(id()) {}

NGM::API::SerialBlob *NGM::API::SerialBlob::toBlob()
{
	return this;
}

uint32_t NGM::API::SerialBlob::id()
{
	return 0x4E04;
}

NGM::API::SerialPixmap::SerialPixmap() : SerialData(id()) {}

NGM::API::SerialPixmap *NGM::API::SerialPixmap::toPixmap()
{
	return this;
}

uint32_t NGM::API::SerialPixmap::id()
{
	return 0x4E05;
}

NGM::API::SerialIcon::SerialIcon() : SerialData(id()) {}

NGM::API::SerialIcon *NGM::API::SerialIcon::toIcon()
{
	return this;
}

uint32_t NGM::API::SerialIcon::id()
{
	return 0x4E06;
}

NGM::API::SerialVariant::SerialVariant() : SerialData(id()) {}

NGM::API::SerialVariant *NGM::API::SerialVariant::toVariant()
{
	return this;
}

uint32_t NGM::API::SerialVariant::id()
{
	return 0x4E07;
}
