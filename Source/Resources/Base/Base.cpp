/**
 *  @file Base.cpp
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
#include "Project.hpp"
#include "Resource.hpp"
#include "Serializer.hpp"
#include "Editor.hpp"
#include "Type.hpp"

namespace NGM
{
	namespace Resource
	{
		Project::Project(const Serializer * const serializer,const Type * const type,
				const QString category, const QString description, const QStringList extensions) :
			serializer(serializer), type(type), category(category),
			description(description), extensions(extensions) {}

		Resource::Resource(const Type * const type, QString location, uint8_t status) :
			status(status), type(type), location(location) {}

		Serializer::Serializer(const uint8_t &settings) : settings(settings) {}

		Type::Type(const QString &name, const QString &plural) : name(name), plural(plural) {}

		Editor::Editor(NGM::Widget::ResourceTab * const parent) :
			QWidget(parent), resourceTab(parent), state(0) {}

		bool Editor::event(QEvent *event)
		{
			if (event->type() == QEvent::FocusIn || event->type() == QEvent::Show)
			{
				emit isFocused(this);
				return true;
			}
			return QWidget::event(event);
		}

		const uint8_t Editor::getState()
		{
			return state;
		}

		const NGM::Widget::ResourceTab * const Editor::getResourceTabWidget()
		{
			return resourceTab;
		}
	}
}
