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
#include "Loader.hpp"

NGM::API::Loader::Loader(Serializer *serializer)
{
	_serializers.push_back(serializer);
}

void NGM::API::Loader::addSerializer(Serializer *serializer)
{
	_serializers.push_back(serializer);
}

void NGM::API::Loader::projectCreate(Model::ResourceProjectItem *item) const
{
	for (auto &i : _serializers)
	{
		i->projectCreate(item);
	}
}

void NGM::API::Loader::projectSave(Model::ResourceProjectItem *item) const
{
	for (auto &i : _serializers)
	{
		i->projectSave(item);
	}
}

void NGM::API::Loader::projectLoad(Model::ResourceProjectItem *item) const
{
	for (auto &i : _serializers)
	{
		i->projectLoad(item);
	}
}

void NGM::API::Loader::projectReload(Model::ResourceProjectItem *item) const
{
	for (auto &i : _serializers)
	{
		i->projectReload(item);
	}
}

bool NGM::API::Loader::fileAllowed(const QString &filename,
  const Model::ResourceBaseItem *item) const
{
	for (auto &i : _serializers)
	{
		if (i->fileAllowed(filename, item))
		{
			return true;
		}
	}
	return false;
}

void NGM::API::Loader::fileDropped(const QString &filename,
  Model::ResourceBaseItem *item) const
{
	for (auto &i : _serializers)
	{
		i->fileDropped(filename, item);
	}
}

bool NGM::API::Loader::itemAllowed(const Model::ResourceBaseItem *from,
  const Model::ResourceGroupItem *to) const
{
	for (auto &i : _serializers)
	{
		if (i->itemAllowed(from, to))
		{
			return true;
		}
	}
	return false;
}

void NGM::API::Loader::itemDropped(const Model::ResourceBaseItem *from,
  Model::ResourceGroupItem *to) const
{
	for (auto &i : _serializers)
	{
		i->itemDropped(from, to);
	}
}

void NGM::API::Loader::itemDeleted(const Model::ResourceBaseItem *item) const
{
	for (auto &i : _serializers)
	{
		i->itemDeleted(item);
	}
}

void NGM::API::Loader::itemAddRequested(QList<TypeDisplay> *typeList,
  const Model::ResourceGroupItem *item) const
{
	for (auto &i : _serializers)
	{
		i->itemAddRequested(typeList, item);
	}
}
