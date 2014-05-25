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
#include "Serializer.hpp"

void NGM::API::Serializer::projectReload(Model::ResourceProjectItem *item) const
{
	projectCreate(item);
	projectLoad(item);
}

bool NGM::API::Serializer::fileAllowed(const QString &,
  const Model::ResourceBaseItem *) const
{
	return false;
}

void NGM::API::Serializer::fileDropped(const QString &,
  Model::ResourceBaseItem *) const
{
	// Itentionally empty.
}

bool NGM::API::Serializer::itemAllowed(const Model::ResourceBaseItem *,
  const Model::ResourceGroupItem *) const
{
	return false;
}

void NGM::API::Serializer::itemDropped(const Model::ResourceBaseItem *,
  Model::ResourceGroupItem *) const
{
	// Itentionally empty.
}

void NGM::API::Serializer::itemRenamed(const QString &,
  const Model::ResourceBaseItem *) const
{
	// Itentionally empty.
}

void NGM::API::Serializer::itemDeleted(const Model::ResourceBaseItem *) const
{
	// Intentionally empty.
}
