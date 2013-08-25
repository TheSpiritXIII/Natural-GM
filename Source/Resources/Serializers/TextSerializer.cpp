/**
 *  @file TextSerializer.cpp
 *  @section License
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
#include "TextSerializer.hpp"
#include "Editor.hpp"
#include <QFile>

namespace NGM
{
	namespace Resource
	{
		TextSerializer::TextSerializer() : Serializer(CanPreload | CanBeTemporary)
		{
			// Intentionally empty.
		}

		void TextSerializer::read(Editor *widget, Resource *resource) const
		{
			if (resource->status & Resource::IsFilename)
			{
				QFile file(resource->location);
				file.open(QIODevice::ReadOnly);
				widget->setProperty("text", file.readAll());
				file.close();
				return;
			}
			auto &i = resource->serialData->attributes.find("text");
			char *data = i->second.data();
			widget->setProperty("text", QByteArray(data, static_cast<int>(i->second.size())));
			resource->serialData->attributes.erase(i);
		}

		void TextSerializer::write(Editor *widget, Resource *resource) const
		{
			if (resource->status & Resource::IsFilename)
			{
				QFile file(resource->location);
				file.open(QIODevice::WriteOnly);
				file.write(widget->property("text").toByteArray());
				file.close();
				return;
			}
			QByteArray text = widget->property("text").toByteArray();
			std::vector<int8_t> data;
			data.emplace_back(text.data(), text.size());
			//resource->serialData->attributes["text"] = &data;
		}

		void TextSerializer::structure(Model::ResourceProjectItem *item) const
		{
			if (~item->resource->status & Resource::IsFilename)
			{
				QFile file(item->resource->location);
				file.open(QIODevice::WriteOnly);
				QByteArray text = file.readAll();
				std::vector<int8_t> data;
				data.emplace_back(text.data(), text.size());
				//item->resource->serialData->attributes["text"] = data;
				file.close();
			}
		}

		void TextSerializer::restructure(Model::ResourceProjectItem *) const
		{
			// Intentionally empty.
		}

	}
}
