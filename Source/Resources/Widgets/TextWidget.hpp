/**
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
#pragma once
#ifndef _NGM_TEXTWIDGET__HPP
#define _NGM_TEXTWIDGET__HPP
#include "../Resources/Widget.hpp"
#include "../Global.hpp"
#define QSCINTILLA_DLL
#include <Qsci/qsciscintilla.h>

namespace NGM
{
	namespace Resource
	{
		class TextWidget : public Widget
		{
		public:

			/**************************************************//*!
			 *	@brief Creates a widget with the indicated parent.
			******************************************************/
			TextWidget(NGM::Widget::ResourceTab *parent);

			/**************************************************//*!
			 *	@brief Destroys the widget and all of its children.
			******************************************************/
			~TextWidget();

			/**************************************************//*!
			 *	@brief Requests the widget to cut its data.
			******************************************************/
			void cutRequest();

			/**************************************************//*!
			 *	@brief Requests the widget to copy its data->
			******************************************************/
			void copyRequest();

			/**************************************************//*!
			 *	@brief Requests the widget to paste its data.
			******************************************************/
			void pasteRequest();

			/**************************************************//*!
			 *	@brief Requests the widget to undo its data.
			******************************************************/
			void undoRequest();

			/**************************************************//*!
			 *	@brief Requests the widget to redo its data.
			******************************************************/
			void redoRequest();

			/**************************************************//*!
			*	@brief	Requests the widget to zoom in.
			******************************************************/
			void zoomInRequest();

			/**************************************************//*!
			*	@brief	Requests the widget to zoom out.
			******************************************************/
			void zoomOutRequest();

			/**************************************************//*!
			*	@brief	Requests the widget to normalize zoom.
			******************************************************/
			void zoomRequest();

			/**************************************************//*!
			 *	@brief Searches the widget for the indicated data.
			******************************************************/
			void searchRequest(uint8_t settings, QByteArray *data);

			/**************************************************//*!
			 *	@brief Sets the window's status contents.
			******************************************************/
			void statusRequest(QLabel *label, QProgressBar *progress);

			/**************************************************//*!
			*	@return	Tells the widget that it was saved. The
			*			state should remove its modified flag.
			******************************************************/
			void isSaved();

			/**************************************************//*!
			 *	@return The value of the indicated property.
			******************************************************/
			QVariant property(const char* property);

			/**************************************************//*!
			 *	@return A list of all possible properties.
			******************************************************/
			QStringList	getPropertyList();

			/**************************************************//*!
			 *	@brief Sets the indicated property to the
			 *		indicated value.
			******************************************************/
			void setProperty(const char* property, QVariant value);

			void block(const bool &blocked);

		private:

			/**************************************************//*!
			 *	@brief The editable widget.
			******************************************************/
			QsciScintilla *textEdit;
		};
	}
}

#endif // _NGM_TEXTWIDGET__HPP
