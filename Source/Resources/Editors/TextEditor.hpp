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
//#include <Qsci/qsciscintilla.h>
#include <QComboBox>
#include <QLabel>
#include <QDebug>

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
			TextEditor(const Model::ResourceProjectItem * const item,
					   Widget::ResourceTab * const tab);

			/**************************************************//*!
			 *	@brief Destroys the widget and all of its children.
			******************************************************/
			~TextEditor();

			/**************************************************//*!
			 *	@brief Allocates a new editor of this type.
			******************************************************/
			static Editor *create(const Model::ResourceProjectItem * const item,
								  Widget::ResourceTab * const tab);

			/**************************************************//*!
			*	@brief	Requests the widget to cut.
			******************************************************/
			void cut();

			/**************************************************//*!
			*	@brief	Requests the widget to copy.
			******************************************************/
			void copy();

			/**************************************************//*!
			*	@brief	Requests the widget to paste.
			******************************************************/
			void paste();

			/**************************************************//*!
			*	@brief	Requests the widget to undo.
			******************************************************/
			void undo();

			/**************************************************//*!
			*	@brief	Requests the widget to redo its data.
			******************************************************/
			void redo();

			/**************************************************//*!
			*	@brief	Requests the widget to zoom in.
			******************************************************/
			void zoomIn();

			/**************************************************//*!
			*	@brief	Requests the widget to zoom out.
			******************************************************/
			void zoomOut();

			/**************************************************//*!
			*	@brief	Requests the widget to normalize zoom.
			******************************************************/
			void zoom();

			/**************************************************//*!
			*	@brief	Clones the widget into another view.
			******************************************************/
			Editor *clone(NGM::Widget::ResourceTab *tab) const;

			/**************************************************//*!
			*	@brief	Searches the widget for the indicated data.
			******************************************************/
			void search(unsigned char s, QString data) const;

			/**************************************************//*!
			*	@brief	Sets the window's status contents.
			******************************************************/
			void status(Manager::WindowManager * const windowManager) const;

			/**************************************************//*!
			*	@return	The value of the indicated property.
			******************************************************/
			Variant property(const char* property) const;

			/**************************************************//*!
			*	@return	A list of all possible properties.
			******************************************************/
			QStringList getPropertyList() const;

			/**************************************************//*!
			*	@brief	Sets the indicated property to the
			*			indicated value.
			******************************************************/
			void setProperty(const char* property, Variant &value);

			/**************************************************//*!
			*	@brief	Called after setting default properties.
			*			Metadata should be updated here.
			******************************************************/
			void initialize();

			/**************************************************//*!
			*	@return	Tells the widget that it was saved. The
			*			state should remove its modified flag.
			******************************************************/
			void saved();

			/**************************************************//*!
			*	@brief	Saves this widget's current session
			******************************************************/
			void saveSession(const QString &filename) const;

			/**************************************************//*!
			*	@brief	Saves this widget's current session.
			******************************************************/
			void loadSession(const QString &filename);

		private:

			/**************************************************//*!
			*	@brief	The editable widget.
			******************************************************/
			//QsciScintillaBase *textEdit;

			/**************************************************//*!
			*	@brief	Updates the line font metrics width.
			******************************************************/
			void updateLineLength();

			/**************************************************//*!
			*	@brief	The status label that stores the edit's
			*			character and line lengths.
			******************************************************/
			QLabel *lengthLabel;

			/**************************************************//*!
			*	@brief	The status label that contains the current
			*			line number and character.
			******************************************************/
			QLabel *positionLabel;

			/**************************************************//*!
			*	@brief	The status label that contains the current
			*			number of selected lines and character.
			******************************************************/
			QLabel *selectLabel;

			QComboBox *typeComboBox;

			int lastPosition;

			/*void setFont(const int &style, const char *family, const int &size, const int &weight, const bool &italic, const bool &underline)
			{
				textEdit->SendScintilla(QsciScintilla::SCI_STYLESETFONT, style, family);
				textEdit->SendScintilla(QsciScintilla::SCI_STYLESETSIZE, style, size);
				textEdit->SendScintilla(QsciScintilla::SCI_STYLESETWEIGHT, style, weight);
				textEdit->SendScintilla(QsciScintilla::SCI_STYLESETITALIC, style, italic);
				textEdit->SendScintilla(QsciScintilla::SCI_STYLESETUNDERLINE, style, underline);
			}*/
		};
	}
}

#endif // _NGM_TEXTEDITOR__HPP
