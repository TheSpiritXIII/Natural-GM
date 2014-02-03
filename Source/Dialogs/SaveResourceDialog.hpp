/**
 *  @file SaveResourceDialog.hpp
 *  @section License
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
#ifndef NGM__SAVERESOURCEDIALOG__HPP
#define NGM__SAVERESOURCEDIALOG__HPP
#include <QDialog>

namespace NGM
{
	namespace Dialog
	{
		/**************************************************//*!
		*	@brief	A dialog that displays a tree that
		*			contains checkable resource items. The
		*			items that are checked are saved by
		*			their respective serializers.
		******************************************************/
		class SaveResourceDialog : public QDialog
		{
		public:
			// TODO Add list parameter to constructor.
			SaveResourceDialog(QWidget *parent = 0);
		private slots:
			void saveButtonPressed();
		};
	}
}

#endif // NGM__SAVERESOURCEDIALOG__HPP
