/*-
 *  Copyright (c) 2014 Daniel Hrabovcak
 *
 *  This program is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or (at your
 *  option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 *  for more details.
**/
#pragma once
#include "Editor.hpp"
#include <QString>
#include <QMap>

namespace NGM
{
	namespace API
	{
		struct ToolContext;

		/**************************************************//*!
		*  @brief  A factory for editor widgets and their
		*          respective sub-widgets.
		*
		* The class has a variety of different applications.
		* Mostly, this class manages the way that editors
		* interact against common actions. Thus, it is
		* important to subclass all protected member
		* functions.
		*
		* Tools are also saved between locations. Ideally,
		* this location is a window, where it would also be
		* displayed. It is only recommended for these
		* locations to access their tools.
		******************************************************/
		struct Factory
		{
			/**************************************************//*!
			*  @brief  Initializes the factory by setting meta
			*          data.
			******************************************************/
			Factory(const QString &name, const QString &type,
			  bool clonable = false);

			/**************************************************//*!
			*  @brief  Creates and returns an editor.
			******************************************************/
			Editor *createEditor(const Manager::GlobalManager *manager);

			/**************************************************//*!
			*  @brief  Returns the tools owned by the given
			*          location, creating one if it does not
			*          exist.
			*
			* An application manager must be passed if a tool
			* does not already exist in the given location,
			* otherwise nullptr is returned.
			******************************************************/
			ToolContext *editorTools(const QWidget *location,
			  Manager::GlobalManager *manager = nullptr);

			/**************************************************//*!
			*  @brief  The name of the editor.
			*
			* If possible, this name should not be generic. When
			* a user is editing and wants to choose a certain
			* editor of the current type, this name is displayed
			* to differentiate other editors of the same type.
			******************************************************/
			const QString name;

			/**************************************************//*!
			*  @brief  The name of the type of editor.
			*
			* This editor is grouped with names of other editors
			* that share the same type. For this reason, it is
			* important that the type is named accordingly.
			******************************************************/
			const QString type;

			/**************************************************//*!
			*  @brief  Determines whether the editor is capable
			*          of making duplicate clones of itself.
			******************************************************/
			const bool clonable;

		protected:

			/**************************************************//*!
			*  @brief  Allocates and returns an editor widget.
			*
			* Widgets may use and store the application manager
			* to obtain icons and other resources.
			******************************************************/
			virtual QWidget *createWidget(Editor *editor,
				const Manager::GlobalManager *manager) const = 0;

			/**************************************************//*!
			*  @brief  Returns a clone of the indicated widget.
			*
			* The returned clone should update when the original
			* widget is updated and vice-versa. The widget should
			* be the same type as the one created in
			* createWidget(). By default, this function returns a
			* nullptr, so it must be reimplemented if clonable is
			* true.
			******************************************************/
			virtual QWidget *duplicateWidget(QWidget *widget,
				const Manager::GlobalManager *manager) const;

			/**************************************************//*!
			*  @brief  Allocates and returns a collection of
			*          editor compatible tools, or nullotr, if
			*          the editor does not support tools.
			******************************************************/
			virtual ToolContext *createTools(
			  const Manager::GlobalManager *manager) const;

			/**************************************************//*!
			*  @brief  Returns the status of the indicated editor
			*          widget.
			*
			* This function is used to disable or enable editor
			* based actions by using the given flags. By default,
			* this functions returns 0, disabling all actions.
			******************************************************/
			virtual Editor::Status status(const QWidget *widget) const = 0;

			/**************************************************//*!
			*  @brief  Connecting signals and slots with the
			*          context and tools.
			*
			* By default, this function connects nothing, for
			* read only widgets that do not support any tools.
			******************************************************/
			virtual void connect(const QWidget *widget,
			  ToolContext *editorTool, Context::EditContext *context) const;

			/**************************************************//*!
			*  @brief  Disconnectis signals and slots with the
			*          context and tools.
			*
			* By default, this function disconnects nothing, for
			* read only widgets that do not support any tools.
			******************************************************/
			virtual void disconnect(const QWidget *widget,
			  ToolContext *editorTool, Context::EditContext *context) const;

			/**************************************************//*!
			*  @brief  Executes the given command to the
			*          indicated widget.
			*
			* Plugins may use this for extending, or modifying
			* the capabilities of editors.
			******************************************************/
			virtual SerialData *execute(QWidget *editor, const char *command,
			  SerialData *params) const;

			friend class Editor;

		private:
			QMap<const QWidget*, ToolContext*> _tools;
		};
	}
}
