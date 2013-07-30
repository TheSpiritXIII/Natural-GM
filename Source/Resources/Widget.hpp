#pragma once
#ifndef _NGM_RESOURCE_WIDGET__HPP
#define _NGM_RESOURCE_WIDGET__HPP
#include "Global.hpp"
#include <string>
#include <QString>
#include <QAction>
#include <QWidget>
#include <QMessageBox>
#include <QProgressBar>
#include "ResourceContentItem.hpp"
#include "Resources/Project.hpp"
#include "Resources/Serializer.hpp"

namespace NGM
{
	namespace Resource
	{
		/**************************************************//*!
		 *	An editable widget for a specific resource.
		******************************************************/
		class Widget : public QWidget
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			 *	@brief Settings for de/activating toolbar contrals.
			******************************************************/
			enum Settings
			{
				CanCut			=	0b00000001,
				CanCopy			=	0b00000010,
				CanPaste		=	0b00000100,
				CanSearch		=	0b00001000,
				CanClipboard	=	0b00000111
			};

			/**************************************************//*!
			 *	@brief Creates a widget with the indicated parent.
			******************************************************/
			Widget(QWidget *parent = 0) : QWidget(parent) {}

			/**************************************************//*!
			 *	@brief Destroys the widget and all of its children.
			******************************************************/
			~Widget() {}

			/**************************************************//*!
			 *	@brief Requests the widget to cut its data.
			******************************************************/
			virtual void cutRequest() = 0;

			/**************************************************//*!
			 *	@brief Requests the widget to copy its data->
			******************************************************/
			virtual void copyRequest() = 0;

			/**************************************************//*!
			 *	@brief Requests the widget to paste its data.
			******************************************************/
			virtual void pasteRequest() = 0;

			/**************************************************//*!
			 *	@brief Requests the widget to undo its data.
			******************************************************/
			virtual void undoRequest() = 0;

			/**************************************************//*!
			 *	@brief Requests the widget to redo its data.
			******************************************************/
			virtual void redoRequest() = 0;

			/**************************************************//*!
			 *	@brief Searches the widget for the indicated data.
			******************************************************/
			virtual void searchRequest(unsigned char s, QByteArray *data) = 0;

			/**************************************************//*!
			 *	@brief Sets the window's status contents.
			******************************************************/
			virtual void statusRequest(QLabel *label, QProgressBar *progress) = 0;

			/**************************************************//*!
			 *	@return Attempts to close the widget.
			 *	@return True if the widget was closed, false otherwise.
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
			 *	@return The value of the indicated property.
			******************************************************/
			virtual QVariant property(const char* property) = 0;

			/**************************************************//*!
			 *	@return A list of all possible properties.
			******************************************************/
			virtual QStringList	getPropertyList() = 0;

			/**************************************************//*!
			 *	@brief Sets the indicated property to the
			 *		indicated value.
			******************************************************/
			virtual void setProperty(const char* property, QVariant value) = 0;

			/**************************************************//*!
			 *	@return The widget toolbar settings.
			******************************************************/
			virtual uint8_t getSettings() = 0;

		signals:

			/**************************************************//*!
			 *	@brief Requests to update the status bar.
			******************************************************/
			void requestStatusUpdate();
		};
	}
}

#endif // _NGM_RESOURCE_WIDGET__HPP
