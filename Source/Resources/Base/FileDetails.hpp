/**
 *  @file FileDetails.hpp
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
#ifndef NGM__FILEDETAILS__HPP
#define NGM__FILEDETAILS__HPP
#include <QStringList>

namespace NGM
{
	namespace Resource
	{
		/**************************************************//*!
		*	@brief	Contains details about file formats. Used
		*			to guess which format a file is.
		*
		* It is expected that the header data is a constant
		* string, and so it must exist throughout the
		* application lifetime. Although this class provides
		* clues for formats, it does not guarantee it.
		******************************************************/
		struct FileDetails
		{
			// deprecated
			FileDetails() {}

			/**************************************************//*!
			*	@brief	Sets up the file details.
			*	@param	extensions The file extensions to check
			*			for. Note, that the full file name is
			*			checked unless you use the '*' character
			*			as a regular expression. This is the only
			*			regular expression character permitted.
			******************************************************/
			FileDetails(const QStringList &extensions, const char *header = nullptr,
					size_t size = 0, size_t offset = 0);

			/**************************************************//*!
			*	@brief	Stores a list of all possible extensions.
			******************************************************/
			QStringList extensions;

			/**************************************************//*!
			*	@brief	Contains header data of the file, or
			*			nullptr if there is no concise header.
			******************************************************/
			const char * header;

			/**************************************************//*!
			*	@brief	The size of the header, or 0 is there is
			*			no header.
			******************************************************/
			size_t size;

			/**************************************************//*!
			*	@brief	The offset to the header data in the
			*			files, or 0 if there is no offset or
			*			header.
			******************************************************/
			size_t offset;

			/**************************************************//*!
			*	@brief	Opens a file and reads its header content
			*			based on the current offset and size.
			*			Then, it compares the read header with
			*			the actual header as well the filename.
			*			Returns true if there was a match.
			*	@see	matches()
			******************************************************/
			bool check(const QString &filename) const;

			/**************************************************//*!
			*	@brief	Returns true if the filename matches and
			*			the header data matches. If there is no
			*			header data, then only the extension is
			*			checked. Cases are insensitive for
			*			extensions.
			*	@param	filename The name of the file. This is
			*			compared about extensions.
			*	@param	data The data of the file. This is
			*			checked against the header. The header
			*			data should be at least its correct size.
			******************************************************/
			bool matches(const QString &filename, const char *data = nullptr) const;

			/**************************************************//*!
			*	@brief	Returns true if the filename matches
			*			the extensions.
			*	@see	matches()
			*	@see	makefile()
			******************************************************/
			bool isfile(const QString &filename) const;

			/**************************************************//*!
			*	@brief	Adds an extension to the filename. The
			*			first extension that is applicable is
			*			chosen (one that has only a single
			*			asterisk and it is at the beginning).
			*	@see	isfile
			******************************************************/
			QString makefile(const QString &filename) const;

			/**************************************************//*!
			*	@brief	Compares a filename to an extension. The
			*			extension is allowed to use '*' as a
			*			regular expression character.
			******************************************************/
			static bool match(const QString &filename, const QString &extension);
		};
	}
}

#endif // NGM__FILEDETAILS__HPP
