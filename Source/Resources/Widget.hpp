/**
 *  @file Widget.hpp
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
#ifndef _NGM_RESOURCE_WIDGET__HPP
#define _NGM_RESOURCE_WIDGET__HPP
#include "../Global.hpp"
#include <string>
#include <QString>
#include <QAction>
#include <QEvent>
#include <QWidget>
#include <QMessageBox>
#include <QProgressBar>
#include "ResourceContentItem.hpp"
#include "../Resources/Project.hpp"
#include "../Resources/Serializer.hpp"

namespace NGM
{
	namespace Resource
	{
		/**************************************************//*!
		*	@brief	An editable widget for a specific resource.
		******************************************************/
		class Widget : public QWidget
		{
			Q_OBJECT

		public:

			enum Settings
			{
				CanCopy		=	0x01, //0b00000001,
				CanPaste	=	0x02, //0b00000010,
				CanSelect	=	0x04, //0b00000100,
				CanUndo		=	0x08, //0b00001000,
				CanRedo		=	0x10, //0b00010000,
				IsModified	=	0x20  //0b00100000
			};

			/**************************************************//*!
			*	@brief	Creates a widget with the indicated parent.
			******************************************************/
			Widget(QWidget *parent = 0) : QWidget(parent) {}

			/**************************************************//*!
			*	@brief	Destroys the widget and all of its children.
			******************************************************/
			~Widget() {}

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
			*	@brief	Searches the widget for the indicated data.
			******************************************************/
			virtual void searchRequest(unsigned char s, QByteArray *data) = 0;

			/**************************************************//*!
			*	@brief	Sets the window's status contents.
			******************************************************/
			virtual void statusRequest(QLabel *label, QProgressBar *progress) = 0;

			/**************************************************//*!
			*	@return	True if the widget was closed, false otherwise.
			******************************************************/
			virtual bool closeResource(Resource *resource)
			{
				QMessageBox message;
				//message.setText("The resource '"+resource->name+"'' has been modified.");
				message.setInformativeText("Do you want to save your changes?");
				message.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
				message.setDefaultButton(QMessageBox::Save);
				switch (message.exec())
				{
				case QMessageBox::Save:
					//saveResource(resource);
					return true;
				case QMessageBox::Discard:
					return true;
				default:
					return false;
				}
			}

			/**************************************************//*!
			*	@return	The value of the indicated property.
			******************************************************/
			virtual QVariant property(const char* property) = 0;

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
			*	@return	The widget's current state.
			******************************************************/
			virtual uint8_t getState() = 0;

			/**************************************************//*!
			*	@return	Processes a focus event for signals.
			******************************************************/
			bool event(QEvent *event)
			{
				if (event->type() == QEvent::FocusIn || event->type() == QEvent::Show)
				{
					emit isFocused(this);
					return true;
				}
				return QWidget::event(event);
			}

			virtual void block(const bool &blocked) = 0;

		signals:

			/**************************************************//*!
			*	@brief	Requests to update the status bar.
			******************************************************/
			void updateStatus();

			/**************************************************//*!
			*	@brief	Tells if it can copy or not.
			******************************************************/
			void canCopy(bool);

			/**************************************************//*!
			*	@brief	Tells if it can paste or not.
			******************************************************/
			void canPaste(bool);

			/**************************************************//*!
			*	@brief	Tells if it can undo or not.
			******************************************************/
			void canUndo(bool);

			/**************************************************//*!
			*	@brief	Tells if it can redo or not.
			******************************************************/
			void canRedo(bool);

			/**************************************************//*!
			*	@brief	Tells if it can select or not.
			******************************************************/
			void canSelect(bool);

			/**************************************************//*!
			*	@brief	Tells if it is modified or not.
			******************************************************/
			void isModified(bool);

			/**************************************************//*!
			*	@brief	Emitted when the widget gains focus.
			******************************************************/
			void isFocused(Widget *widget);
		};
	}
}

#endif // _NGM_RESOURCE_WIDGET__HPP
