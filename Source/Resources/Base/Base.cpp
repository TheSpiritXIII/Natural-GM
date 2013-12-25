/**
 *  @file Base.cpp
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
#include "Type.hpp"
#include "Editor.hpp"
#include "Factory.hpp"
#include "Project.hpp"
#include "Resource.hpp"
#include "Serializer.hpp"
#include "ResourceTab.hpp"
#include <QDebug>

namespace NGM
{
	namespace Resource
	{
		Factory::Factory(const QString &name, Editor *(* const create)
				(const Model::ResourceProjectItem * const,
				 Widget::ResourceTab * const)) : name(name), create(create) {}

		Project::Project(const Serializer * const serializer,const Type * const type,
				const QString category, const QString description, const QStringList extensions) :
			serializer(serializer), type(type), category(category),
			description(description), extensions(extensions) {}

		Resource::Resource(const Type * const type, QString location,
			const ResourceStatus status) : status(status), type(type),
			location(location),	serialData(nullptr){}

		Serializer::Serializer(const SerializerSettings &settings) : settings(settings) {}

		Editor *Type::create(const Model::ResourceProjectItem * const item,
							 Widget::ResourceTab * const tab) const
		{
			if (factories.size() == 0)
			{
				return nullptr;
			}
			return factories.front()->create(item, tab);
		}

		Type::~Type()
		{
			while (!factories.empty())
			{
				delete factories.front();
				factories.pop_front();
			}
		}

		const QIcon &Type::getIcon(SerialObject *data) const
		{
			if (data)
			{
				qDebug() << data->children.size();
				if (data->children.find("icon") != data->children.end())
				{
					return (*data->children.at("icon")->asVariant()->variant.icon());
				}
			}
			return icon;
		}

		Editor::Editor(const Model::ResourceProjectItem * const item, Widget::ResourceTab * const tab) :
			QWidget(tab), projectItem(item), resourceTab(tab), state(0) {}

		bool Editor::event(QEvent *event)
		{
			if (event->type() == QEvent::FocusIn || event->type() == QEvent::Show || event->type() == QEvent::MouseButtonPress)
			{
				emit isFocused(this);
				return true;
			}
			return QWidget::event(event);
		}

		bool Editor::eventFilter(QObject *, QEvent *event)
		{
			if (event->type() == QEvent::FocusIn)
			{
				emit isFocused(this);
			}
			return false;
		}

		QMenu *Editor::menu() const
		{
			return nullptr;
		}

		QWidget *Editor::preferences() const
		{
			return nullptr;
		}
	}
}
