#include "TextSerializer.hpp"
#include "Widget.hpp"
#include <QFile>
#include <QDebug>

namespace NGM
{
	namespace Resource
	{
		void TextSerializer::read(Widget *widget, Resource *resource)
		{
			if (resource->status & Resource::IsFilename)
			{
				QFile file(resource->location);
				file.open(QIODevice::ReadOnly);
				widget->setProperty("text", file.readAll());
				file.close();
				return;
			}
			widget->setProperty("text", resource->data);
		}

		void TextSerializer::write(Widget *widget, Resource *resource)
		{
			if (resource->status & Resource::IsFilename)
			{
				QFile file(resource->location);
				file.open(QIODevice::WriteOnly);
				file.write(widget->property("text").toByteArray());
				file.close();
				return;
			}
			resource->data = widget->property("text").toByteArray();
		}
	}
}
