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
#include <fstream>
#include <QDebug>

namespace NGM
{
	namespace Resource
	{
		TextSerializer::TextSerializer() : Serializer(0)
		{
			// Intentionally empty.
		}

		void TextSerializer::read(Editor *widget, Resource *resource, const SerializerOptions &options) const
		{
			qDebug() << "READ";
			if (resource->status & Resource::IsFilename)
			{
				qDebug() << "READ2";
				qDebug() << resource->location;
				std::ifstream file;
				file.open(resource->location.toLatin1(), std::ios::in);
				std::string data;
				file.seekg(0, std::ios::end);
				data.resize(file.tellg());
				file.seekg(0, std::ios::beg);
				file.read(&data[0], data.size());
				qDebug() << &data[0];
				Variant var(&data[0]);
				widget->setProperty("text", var);
				file.close();
				/*QFile file(resource->location);
				file.open(QIODevice::ReadOnly);
				QByteArray file.readAll();
				Variant var(&.data()[0]);
				widget->setProperty("text", var);
				file.close();*/
				return;
			}
			//auto i = resource->serialData->attributes.find("text");
			//char *data = i->second.data();
			//widget->setProperty("text", QByteArray(data, static_cast<int>(i->second.size())));
			//resource->serialData->attributes.erase(i);
		}

		void TextSerializer::write(Editor *widget, Resource *resource, const SerializerOptions &options) const
		{
			qDebug() << "WRITE";
			if (resource->status & Resource::IsFilename)
			{
				QFile file(resource->location);
				file.open(QIODevice::WriteOnly);
				file.write(widget->property("text").getCharPtr());
				file.close();
				return;
			}
			QByteArray text = widget->property("text").getCharPtr();
			std::vector<int8_t> data;
			//data.emplace_back(text.data(), text.size());
			//resource->serialData->attributes["text"] = &data;
		}

		bool TextSerializer::structure(Model::ResourceProjectItem *item,
			const Manager::ProjectManager *projectManager,
			QProgressBar *progressBar) const
		{
			qDebug() << "RESTRUCTURE" << item->resource->status;
			if (!(item->resource->status & Resource::IsFilename))
			{
				QFile file(item->resource->location);
				file.open(QIODevice::WriteOnly);
				QByteArray text = file.readAll();
				std::vector<int8_t> data;
				//data.emplace_back(text.data(), text.size());
				//item->resource->serialData->attributes["text"] = data;
				file.close();
				return true;
			}
		}

		void TextSerializer::restructure(Model::ResourceProjectItem *) const
		{
			// Intentionally empty.
		}

	}
}
