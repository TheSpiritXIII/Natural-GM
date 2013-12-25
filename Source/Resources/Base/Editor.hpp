/**
 *  @file Editor.hpp
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
#ifndef _NGM_RESOURCE_EDITOR__HPP
#define _NGM_RESOURCE_EDITOR__HPP
#include "../Global.hpp"
#include "WindowManager.hpp"
#include "ResourceTab.hpp"
#include <QString>
#include <QAction>
#include <QWidget>
#include <QEvent>
#include <QMenu>

namespace NGM
{
	namespace Resource
	{
		class Variant;
	}
	namespace Widget
	{
		class ResourceTab;
	}
	namespace Model
	{
		class ResourceProjectItem;
	}
	namespace Resource
	{
		using Widget::ResourceTab;

		/**************************************************//*!
		*	@brief	An editable widget for resource types.
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
				CanCopy		=	0x001,
				CanPaste	=	0x002,
				CanSelect	=	0x004,
				CanUndo		=	0x008,
				CanRedo		=	0x010,
				CanZoomIn	=	0x020,
				CanZoomOut	=	0x040,
				CanPrint	=	0x080,
				IsModified	=	0x100
			};

			/**************************************************//*!
			*	@brief	Creates an editor.
			*	@param	resourceTab This should be the parent of
			*			this editor widget.
			*	@param	item The parent root of the item that is
			*			currently being edited.
			******************************************************/
			Editor(const Model::ResourceProjectItem * const projectItem,
				   Widget::ResourceTab * const tab);

			/**************************************************//*!
			*	@brief	Destroys the widget and all children.
			******************************************************/
			~Editor() {}

			/**************************************************//*!
			*	@brief	Requests the widget to cut.
			******************************************************/
			virtual void cut() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to copy.
			******************************************************/
			virtual void copy() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to paste.
			******************************************************/
			virtual void paste() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to undo.
			******************************************************/
			virtual void undo() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to redo its data.
			******************************************************/
			virtual void redo() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to zoom in.
			******************************************************/
			virtual void zoomIn() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to zoom out.
			******************************************************/
			virtual void zoomOut() = 0;

			/**************************************************//*!
			*	@brief	Requests the widget to normalize zoom.
			******************************************************/
			virtual void zoom() = 0;

			/**************************************************//*!
			*	@brief	Clones the widget into another view.
			******************************************************/
			virtual Editor *clone(NGM::Widget::ResourceTab *tab) const = 0;

			/**************************************************//*!
			*	@brief	Searches the widget for the indicated
			*			string name.
			******************************************************/
			virtual void search(unsigned char s, QString search) const = 0;

			/**************************************************//*!
			*	@brief	Sets the window's status contents.
			******************************************************/
			virtual void status(Manager::WindowManager *const windowManager) const = 0;

			/**************************************************//*!
			*	@brief	Creates a usable menu for this widget,
			*			or nullptr if this widget has no menu.
			******************************************************/
			virtual QMenu *menu() const;

			/**************************************************//*!
			*	@brief	Returns a widget that can edit this
			*			editor's settings or nullptr if the settings has
			*			no preferences widget.
			******************************************************/
			virtual QWidget *preferences() const;

			/**************************************************//*!
			*	@brief	Returns the value of the indicated property.
			******************************************************/
			virtual Variant property(const char* property) const = 0;

			/**************************************************//*!
			*	@brief	Returns a list of all possible properties.
			*
			*	Some editors feature extendible properties. If
			*	it does, then you can add any property regardless
			*	of what is listed. In that case, this list is
			*	simply a hint.
			******************************************************/
			virtual QStringList getPropertyList() const = 0;

			/**************************************************//*!
			*	@brief	Sets the indicated property to the
			*			indicated value.
			*
			*	All variant data must be copied at this step,
			*	as they may go out of scope.
			******************************************************/
			virtual void setProperty(const char* property, Variant &value) = 0;

			/**************************************************//*!
			*	@brief	Called after setting default properties.
			*			Metadata should be updated here.
			******************************************************/
			virtual void initialize() = 0;

			/**************************************************//*!
			*	@return	Tells the widget that it was saved. The
			*			state should remove its modified flag.
			******************************************************/
			virtual void saved() = 0;

			/**************************************************//*!
			*	@brief	Saves this widget's current session
			******************************************************/
			virtual void saveSession(const QString &filename) const = 0;

			/**************************************************//*!
			*	@brief	Saves this widget's current session.
			******************************************************/
			virtual void loadSession(const QString &filename) = 0;

			/**************************************************//*!
			*	@brief	Returns the widget's current state.
			******************************************************/
			inline const uint16_t &getState() const
			{
				return state;
			}

			/**************************************************//*!
			*	@brief	Returns the parent ResourceTabWidget.
			******************************************************/
			inline const Widget::ResourceTab *getResourceTab() const
			{
				return resourceTab;
			}

			/**************************************************//*!
			*	@brief	Returns the root of the edited item.
			*			Useful for loading other resource types.
			******************************************************/
			const Model::ResourceProjectItem * const projectItem;

		protected:

			/**************************************************//*!
			*	@brief	Processes the event for a focus signal.
			******************************************************/
			bool event(QEvent *event);

			/**************************************************//*!
			*	@brief	Processes the event for a focus signal.
			*			All editors should install an event
			*			filter on their children.
			******************************************************/
			bool eventFilter(QObject *, QEvent *event);

			/**************************************************//*!
			 *	@brief Stores the current state.
			******************************************************/
			uint16_t state;

		private:

			/**************************************************//*!
			*	@brief	The parent of this editor.
			******************************************************/
			const Widget::ResourceTab *resourceTab;

			/**************************************************//*!
			*	@brief	When a widget is moved, the parent tab
			*			is required to be updated.
			******************************************************/
			friend void ResourceTab::moveWidget(const int &index,
												ResourceTab *resourceTab);

		signals:

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
			*	@brief	Signals when the widget modification
			*			flag changed.
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
