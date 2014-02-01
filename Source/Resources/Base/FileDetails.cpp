/**
 *  @file FileDetails.cpp
 *	@section License
 *
 *      Copyright (C) 2014 Daniel Hrabovcak
 *
 *      This file is part of the Natural GM IDE.
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
#include "FileDetails.hpp"
#include <QFile>

#include <QDebug>

NGM::Resource::FileDetails::FileDetails(const QStringList &extensions,
		const char *header, size_t size, size_t offset) :
	extensions(extensions), header(header), size(size), offset(offset) {}

bool NGM::Resource::FileDetails::check(const QString &filename) const
{
	if (this->header != nullptr)
	{
		QFile file(filename);
		file.open(QFile::ReadOnly);
		if (file.size() < offset + size)
		{
			return false;
		}
		file.seek(offset);

		char *buffer = new char[size];
		file.read(buffer, size);
		bool good = matches(filename, buffer);
		delete[] buffer;
		return good;
	}
	return matches(filename, nullptr);
}

bool NGM::Resource::FileDetails::matches(const QString &filename,
										 const char *data) const
{
	if (!isfile(filename) || !strncmp(data, header, offset))
	{
		return false;
	}
	return true;
}

bool NGM::Resource::FileDetails::isfile(const QString &filename) const
{
	for (QStringList::const_iterator i = extensions.begin();
		 i != extensions.end(); ++i)
	{
		if (match(filename, *i))
		{
			return true;
		}
	}
	return false;
}

QString NGM::Resource::FileDetails::makefile(const QString &filename) const
{
	QString made = filename;
	for (QStringList::const_iterator i = extensions.begin();
		 i != extensions.end(); ++i)
	{
		if (i->count(QChar('*')) == 1 && i->at(0) == QChar('*'))
		{
			made += i->right(i->size() - 1);
			return made;
		}
	}
	return made;
}

bool NGM::Resource::FileDetails::match(const QString &filename,
									   const QString &extension)
{
	int location;
	int otherlocation;
	int find = 0;
	int check = 0;
	QStringRef compare;
	while (find < extension.size())
	{
		location = extension.indexOf(QChar('*'), find);
		if (location == -1)
		{
			location = filename.size();
		}
		if (location == 0)
		{
			++find;
			continue;
		}
		compare = extension.midRef(find, location - find);
		otherlocation = filename.indexOf(compare, check);
		if (otherlocation == -1)
		{
			return false;
		}
		find = location + 1;
		check = otherlocation + 1;
	}
	return true;
}
