/**
 *  @file ErrorMessageBox.hpp
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
#pragma once
#ifndef _NGM_ERRORMESSAGEBOX__HPP
#define _NGM_ERRORMESSAGEBOX__HPP
#include <QDialog>

namespace NGM
{
	namespace Widget
	{
		/**************************************************//*!
		*	@brief	An error box with with an abort and
		*		ignore button.
		*
		*	Unlike QMessageBox, the user can add widgets.
		******************************************************/
		class ErrorMessageBox : public QDialog
		{
		public:
		
			/**************************************************//*!
			*	@brief	Creates a generic error with the
			*		indicated message displayed framed.
			******************************************************/
			ErrorMessageBox(const QString *message, QWidget *parent = 0);
			
			/**************************************************//*!
			*	@brief	Creates the message box and returns
			*		whether there the abort button was pressed.
			******************************************************/
			static bool abort(const QString *message);
			
			/**************************************************//*!
			*	@brief	Sets the current added widget's
			*			layout.
			******************************************************/
			void setLayout(QLayout *)
			
		private:
		
			/**************************************************//*!
			*	@brief	The widget that added items are added to.
			******************************************************/
			QWidget *widget;
			
		signals:
		
			/**************************************************//*!
			*	@brief		Indicates that the abort button was
			*			pressed.
			******************************************************/
			abort();
			
			/**************************************************//*!
			*	@brief	Indicates that either the ignore
			*			button or the window was closed.
			******************************************************/
			ignore();
			
		}
	}
}

#endif // _NGM_ERRORMESSAGEBOX_HPP 