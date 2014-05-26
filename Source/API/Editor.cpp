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
#include "Editor.hpp"
#include "Factory.hpp"

const NGM::API::Factory *NGM::API::Editor::factory() const
{
	return _factory;
}

QWidget *NGM::API::Editor::widget() const
{
	return _widget;
}

NGM::API::Editor::Status NGM::API::Editor::status() const
{
	return _factory->status(_widget);
}

void NGM::API::Editor::connect(Context::EditContext *context,
  const QWidget *location)
{
	_factory->connect(_widget, _factory->editorTools(location), context);
}

void NGM::API::Editor::disconnect(Context::EditContext *context,
  const QWidget *location)
{
	_factory->disconnect(_widget, _factory->editorTools(location), context);
}

NGM::API::Editor *NGM::API::Editor::duplicate(
  const Manager::GlobalManager *manager)
{
	if (!_factory->clonable)
	{
		return nullptr;
	}
	QWidget *cloneWidget = _factory->duplicateWidget(_widget, manager);
	if (cloneWidget == nullptr)
	{
		return nullptr;
	}
	return new Editor(_factory, cloneWidget);
}

NGM::API::SerialData *NGM::API::Editor::execute(const char *command,
  SerialData *params)
{
	return _factory->execute(_widget, command, params);
}

NGM::API::Editor::Editor(Factory *factory,
  const Manager::GlobalManager *manager) : _factory(factory),
  _widget(factory->createWidget(this, manager)) {}

NGM::API::Editor::Editor(Factory *factory, QWidget *widget) :
  _factory(factory), _widget(widget) {}
