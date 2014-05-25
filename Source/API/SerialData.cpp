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

NGM::API::SerialObject::SerialObject() : SerialData(id()) {}

uint32_t NGM::API::SerialObject::id()
{
	return 0x4E01;
}

NGM::API::SerialImage::SerialImage() : SerialData(id()) {}

uint32_t NGM::API::SerialImage::id()
{
	return 0x4E02;
}
