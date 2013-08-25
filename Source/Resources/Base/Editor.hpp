/**
 *  @file Editor.hpp
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
#ifndef _NGM_RESOURCE_EDITOR__HPP
#define _NGM_RESOURCE_EDITOR__HPP
#include "../Global.hpp"
#include <string>
#include <QString>
#include <QAction>
#include <QEvent>
#include <QWidget>
#include <QMessageBox>
#include <QProgressBar>
#include "ResourceContentItem.hpp"
#include "Project.hpp"
#include "Serializer.hpp"
#include "ResourceTab.hpp"

namespace NGM
{
	namespace Resource
	{
		/**************************************************//*!
		*	@brief	An editable widget for a specific resource.
		******************************************************/
		class Editor : public QWidget
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Flags for status modifiers.
			******************************************************/
			enum Status
			{
				CanCopy		=	0x01,
				CanPaste	=	0x02,
				CanSelect	=	0x04,
				CanUndo		=	0x08,
				CanRedo		=	0x10,
				CanZoomIn	=	0x20,
				CanZoomOut	=	0x40,
				IsModified	=	0x80
			};

			/**************************************************//*!
			*	@brief	Creates a widget with the indicated parent.
			******************************************************/
			Editor(NGM::Widget::ResourceTab * const parent);

			/**************************************************//*!
			*	@brief	Destroys the widget and all of its children.
			******************************************************/
			~Editor() {}

			/**************************************************//*!
			*	@brief	Requests the widget to cut.
			******************************************************/
			virtual void cutRequest() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to copy.
			******************************************************/
			virtual void copyRequest() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to paste.
			******************************************************/
			virtual void pasteRequest() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to undo.
			******************************************************/
			virtual void undoRequest() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to redo its data.
			******************************************************/
			virtual void redoRequest() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to zoom in.
			******************************************************/
			virtual void zoomInRequest() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to zoom out.
			******************************************************/
			virtual void zoomOutRequest() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to normalize zoom.
			******************************************************/
			virtual void zoomRequest() = 0;

			/**************************************************//*!
			*	@brief	Searches the widget for the indicated data.
			******************************************************/
			virtual void searchRequest(unsigned char s, QByteArray *data) = 0;

			/**************************************************//*!
			*	@brief	Sets the window's status contents.
			******************************************************/
			virtual void statusRequest(QLabel *label, QProgressBar *progress) = 0;

			/**************************************************//*!
			*	@return	The value of the indicated property.
			******************************************************/
			virtual QVariant property(const char* property) const = 0;

			/**************************************************//*!
			*	@return	A list of all possible properties.
			******************************************************/
			virtual QStringList	getPropertyList() = 0;

			/**************************************************//*!
			*	@brief	Sets the indicated property to the
			*			indicated value.
			******************************************************/
			virtual void setProperty(const char* property, QVariant value) = 0;

			/**************************************************//*!
			*	@brief	Block's the widget's signals.
			******************************************************/
			virtual void block(const bool &blocked) = 0;

			/**************************************************//*!
			*	@return	Tells the widget that it was saved. The
			*			state should remove its modified flag.
			******************************************************/
			virtual void isSaved() = 0;

			/**************************************************//*!
			*	@return	Processes a focus event for signals.
			******************************************************/
			bool event(QEvent *event);

			/**************************************************//*!
			*	@return	The widget's current state.
			******************************************************/
			const uint8_t getState();

			/**************************************************//*!
			*	@return	The parent ResourceTabWidget.
			******************************************************/
			const NGM::Widget::ResourceTab * const getResourceTabWidget();

		protected:

			/**************************************************//*!
			 *	@brief Stores the current state.
			******************************************************/
			uint8_t state;

		private:

			/**************************************************//*!
			*	@return	The parent ResourceTabWidget.
			******************************************************/
			NGM::Widget::ResourceTab * const resourceTab;

		signals:

			/**************************************************//*!
			*	@brief	Requests to update the status bar.
			******************************************************/
			void updateStatus();

			/**************************************************//*!
			*	@brief	Signals if a copy is available or not.
			******************************************************/
			void canCopy(bool);

			/**************************************************//*!
			*	@brief	Signals if a paste is available or not.
			******************************************************/
			void canPaste(bool);

			/**************************************************//*!
			*	@brief	Signals if a undo is available or not.
			******************************************************/
			void canUndo(bool);

			/**************************************************//*!
			*	@brief	Signals if a redo is available or not.
			******************************************************/
			void canRedo(bool);

			/**************************************************//*!
			*	@brief	Signals if a copy is available or not.
			******************************************************/
			void canSelect(bool);

			/**************************************************//*!
			*	@brief	Signals if a zoom in is available or not.
			******************************************************/
			void canZoomIn(bool);

			/**************************************************//*!
			*	@brief	Signals if a zoom out is available or not.
			******************************************************/
			void canZoomOut(bool);

			/**************************************************//*!
			*	@brief	Signals when the widget was modified.
			******************************************************/
			void isModified(bool);

			/**************************************************//*!
			*	@brief	Emitted when the widget gains focus.
			******************************************************/
			void isFocused(Editor *editor);
		};
	}
}

#endif // _NGM_RESOURCE_EDITOR__HPP
