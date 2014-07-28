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
#include "Plugin.hpp"

NGM::API::Plugin::Plugin(uint32_t uuid, float priority) :
	uuid(uuid), priority(priority) {}

bool NGM::API::Plugin::canDetach() const
{
	return true;
}

void NGM::API::Plugin::onAttach()
{
	// Intentionally Empty.
}

void NGM::API::Plugin::onDetach()
{
	// Intentionally Empty.
}

void NGM::API::Plugin::initializeFactories(QVector<Factory*>&) const
{
	// Intentionally Empty.
}

void NGM::API::Plugin::initializeProjects(QVector<Project*>&) const
{
	// Intentionally Empty.
}

void NGM::API::Plugin::initializeExtensions(QVector<Serializer*>&) const
{
	// Intentionally Empty.
}

QString NGM::API::Plugin::extensionData(size_t, ExtensionData) const
{
	return QString();
}

void NGM::API::Plugin::initializeActions(QVector<QAction*>&) const
{
	// Intentionally Empty.
}

NGM::API::Plugin::ActionLocation NGM::API::Plugin::actionMenuLocation(
	size_t) const
{
	return ActionLocation::None;
}

NGM::API::Plugin::ActionLocation NGM::API::Plugin::actionToolLocation(
	size_t) const
{
	return ActionLocation::None;
}
