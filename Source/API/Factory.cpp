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
#include "Factory.hpp"

NGM::API::Factory::Factory(const QString &name, const QString &type,
  bool clonable) : name(name), type(type), clonable(clonable) {}

NGM::API::Editor *NGM::API::Factory::createEditor(
  const Manager::GlobalManager *manager)
{
	return new Editor(this, manager);
}

NGM::API::EditorTools *NGM::API::Factory::editorTools(const QWidget *location,
  Manager::GlobalManager *manager)
{
	QMap<const QWidget*, EditorTools*>::iterator i = _tools.find(location);
	if (i != _tools.end())
	{
		return i.value();
	}
	if (manager == nullptr)
	{
		return nullptr;
	}
	EditorTools *subWidgets = createTools(manager);
	if (subWidgets == nullptr)
	{
		return nullptr;
	}
	return _tools.insert(location, subWidgets).value();
}

NGM::API::EditorTools *NGM::API::Factory::createTools(
  const Manager::GlobalManager *) const
{
	return nullptr;
}

void NGM::API::Factory::connect(const QWidget*, EditorTools*,
  Context::EditContext*) const
{
	// Intentionally empty.
}

void NGM::API::Factory::disconnect(const QWidget*, EditorTools*,
  Context::EditContext*) const
{
	// Intentionally empty.
}
