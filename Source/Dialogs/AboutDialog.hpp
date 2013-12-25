/**
 *  @file AboutDialog.hpp
 *  @section License
 *
 *      Copyright (C) 2013-2014 Daniel Hrabovcak
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
#ifndef NGM__ABOUTDIALOG__HPP
#define NGM__ABOUTDIALOG__HPP
#include <QDialog>

namespace NGM
{
	namespace Dialog
	{
		/**************************************************//*!
		*	@brief	Displays Natural GM's copyrights.
		******************************************************/
		class AboutDialog : public QDialog
		{
		public:

			/**************************************************//*!
			*	@brief	Creates the dialog with text.
			******************************************************/
			AboutDialog(QWidget *parent);

		};
	}
}

#endif // NGM__ABOUTDIALOG__HPP
