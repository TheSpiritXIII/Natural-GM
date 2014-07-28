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
#include "PluginDepr.hpp"

NGM::API::Version::Version(uint8_t major, uint8_t minor, uint8_t revision) :
	major(major), minor(minor), revision(revision) {}

NGM::API::Version NGM::API::Version::version()
{
	return NGM::API::Version(NGM_VERSION_MAJOR, NGM_VERSION_MINOR,
		NGM_VERSION_PATCH);
}

NGM::API::SerialData *NGM::API::Plugin::execute(const char*, SerialData*) const
{
	return nullptr;
}

bool NGM::API::Plugin::operator<(const Plugin &other)
{
	return priority < other.priority;
}

NGM::API::Plugin::Plugin(const QString &name, const QString &authors,
  const QString &description, Version version, uint32_t uuid, float priority) :
  name(name), authors(authors), description(description), version(version),
  priority(priority), uuid(uuid) {}
