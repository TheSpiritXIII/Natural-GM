/**
 *  @file TextEditor.hpp
 *	@section License
 *
 *      Copyright (C) 2013 Daniel Hrabovcak
 *
 *      This file is a part of the Natural GM IDE. MIT License.
 *
 *      Permission is hereby granted, free of charge, to any person obtaining a copy
 *		of this software and associated documentation files (the "Software"), to deal
 *		in the Software without restriction, including without limitation the rights
 *		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *		copies of the Software, and to permit persons to whom the Software is
 *		furnished to do so, subject to the following conditions:
 *
 *		The above copyright notice and this permission notice shall be included in
 *		all copies or substantial portions of the Software.
 *
 *		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *		THE SOFTWARE.
**/
#pragma once
#ifndef _NGM_TEXTEDITOR__HPP
#define _NGM_TEXTEDITOR__HPP
#include "Editor.hpp"
#include <Qsci/qsciscintilla.h>

namespace NGM
{
	namespace Resource
	{
		class TextEditor : public Editor
		{
		public:

			/**************************************************//*!
			 *	@brief Creates a widget with the indicated parent.
			******************************************************/
			TextEditor(NGM::Widget::ResourceTab *parent);

			/**************************************************//*!
			 *	@brief Destroys the widget and all of its children.
			******************************************************/
			~TextEditor();

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
			QVariant property(const char* property) const;

			/**************************************************//*!
			 *	@return A list of all possible properties.
			******************************************************/
			QStringList	getPropertyList();

			/**************************************************//*!
			 *	@brief Sets the indicated property to the
			 *		indicated value.
			******************************************************/
			void setProperty(const char* property, QVariant value);

			/**************************************************//*!
			*	@brief	Block's the widget's signals.
			******************************************************/
			void block(const bool &blocked);

			/**************************************************//*!
			*	@brief	Clones the widget into another view.
			******************************************************/
			Editor *clone(NGM::Widget::ResourceTab *parent);

			/**************************************************//*!
			*	@brief	Saves this widget's state.
			******************************************************/
			void saveState();

			/**************************************************//*!
			*	@brief	Saves this widget's state.
			******************************************************/
			void loadState();

		private:

			/**************************************************//*!
			 *	@brief The editable widget.
			******************************************************/
			QsciScintilla *textEdit;

			/**************************************************//*!
			 *	@brief Updates the line font metrics width.
			******************************************************/
			void updateLineLength();
		};
	}
}

#endif // _NGM_TEXTEDITOR__HPP
