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
#include <QVector>
#include <QString>

struct QAction;

namespace NGM
{
	namespace Manager
	{
		struct PluginMan;
	}
	namespace API
	{
		struct Factory;
		struct SerialData;
		struct Serializer;
		struct Project;

		/**
		 * @brief  Stores plugin data.
		 *
		 * Plugins are used to extend core features and come in three flavors:
		 * Projects, extensions (which extend existing projects) and finally
		 * editors. In addition, plugins may also contain other functionality,
		 * which can be executed by other plugins.
		 */
		struct Plugin
		{
			/**
			 * @brief  Defines extension meta-data value types.
			 */
			enum ExtensionData
			{
				ProjectName, //!< The name of the project it is extending.
				Category     //!< The category of the project it is extending.
			};

			/**
			 * @brief  Defines action location hints.
			 */
			enum class ActionLocation
			{
				None   = 0, //!< The action does not appear.
				Plugin = 1, //!< The action appears under the plugin name.
				//Custom = 2, //!< The action has a custom location name.
				File   = 3, //!< The action is under the file location.
				Edit   = 4, //!< The action is under the edit location.
				Help   = 5  //!< The action is under the help location.
			};

			/**
			 * @brief  The unique identifier value for this plugin.
			 *
			 * Plugins may use this value for referencing other plugins as
			 * dependencies. As such, it is important that this value is truely
			 * unique among different plugins and so it is recommended for
			 * plugin developers to check the plugin database against values.
			 */
			const uint32_t uuid;

			/**
			 * @brief  The priority value of this plugin.
			 *
			 * This number is used by the plugin loader. By default, plugins
			 * have a priority of 50, and typically range between 0 and 100.
			 * A plugin must have a low priority value if it is depended on by
			 * other plugins, or a high priority value if it depends on other
			 * plugins.
			 */
			const float priority;

			/**
			 * @brief  Executes the given command with the given parameters.
			 *
			 * Other plugins may use this for accessing this plugin's
			 * functionality. Thus, it is recommended for the plugin's internal
			 * actions to call this function, or for this function to call an
			 * action's function.
			 *
			 * By default and on error, this function should return nullptr.
			 */
			virtual SerialData *execute(const char *command,
				SerialData *params) const;

			/**
			 * @brief  Returns true if the plugin is currently attached, false
			 *         otherwise.
			 *
			 * A plugin is considered attached after the plugin manager requests
			 * the plugin to allocate its data and begin performing actions. If
			 * the plugin is not attached, then it should perform any actions.
			 */
			inline bool isAttached() const
			{
				return _attached;
			}

			/**
			 * @brief  Returns true if the plugin can currently be detached,
			 *         false otherwise.
			 *
			 * When a plugin is requested to be reinstalled, uninstalled or
			 * updated then this function is used to check whether it is
			 * possible to. It might not be possible, such if the plugin is
			 * currently performing a task.
			 *
			 * By default, this function returns 'true'.
			 */
			virtual bool canDetach() const;

			/**
			 * @brief  Returns true if the priority of this plugin is lower or
			 *         equal to the other plugin.
			 *
			 * This function is used for loading plugins. We use this to sort
			 * the plugins in the order they want to be loaded.
			 */
			inline bool operator <(const Plugin &other) const
			{
				return uuid < other.uuid;
			}

		protected:

			/**
			 * @brief  Creates a plugin with the given identifier and priority
			 *         values.
			 *
			 * Plugins should _not_ allocate or initialize their data here.
			 * Instead, they should use onAttach() and onDetach() instead of the
			 * constructors and destructors respectfully.
			 */
			Plugin(uint32_t uuid, float priority = 50.0f);

			/**
			 * @brief  Allocates all data for the plugin.
			 *
			 * Plugins should override this method to initialize data, rather
			 * than using the constructor.
			 */
			virtual void onAttach();

			/**
			 * @brief  Deallocates all data for the plugin.
			 *
			 * Plugins should override this method to deallocate data, rather
			 * than using the destructor.
			 */
			virtual void onDetach();

			/**
			 * @brief  Initializes all factories.
			 *
			 * Plugins should override this function if they want to support
			 * editor factories. Factories are responsible for creating editors.
			 */
			virtual void initializeFactories(
				QVector<Factory*> &factories) const;

			/**
			 * @brief  Initializes all projects.
			 * @see    extensionData()
			 *
			 * Plugins should override this function if they want to support
			 * projects. Projects are responsible for adding support for
			 * specific file types.
			 */
			virtual void initializeProjects(QVector<Project*> &projects) const;

			/**
			 * @brief  Initializes all extensions.
			 * @see    extensionData()
			 *
			 * Plugins should override this function if they want to support
			 * extensions. Extensions are responsible for extending an existing
			 * file or project type.
			 */
			virtual void initializeExtensions(
				QVector<Serializer*> &extensions) const;

			/**
			 * @brief  Returns the indicated extension meta-data of the given
			 *         extension index.
			 *
			 * Plugins must override this function if they initialize any
			 * extensions. Any extension with no meta-data attached will be
			 * ignored. Both the project name and category has to match for the
			 * extension to be attached.
			 */
			virtual QString extensionData(size_t index,
				ExtensionData type) const;

			/**
			 * @brief  Initializes all actions.
			 * @see    actionMenuLocation()
			 *
			 * Plugins should override this function if they want to support
			 * actions. Actions consist of
			 */
			virtual void initializeActions(QVector<QAction*> &actions) const;

			/**
			 * @brief  Returns the location in the menu of the given action
			 *         index.
			 *
			 * Plugins can optionally override function if they want actions to
			 * be placed in the window menu bar.
			 */
			virtual ActionLocation actionMenuLocation(size_t index) const;

			/**
			 * @brief  Returns the location in the tool-bar of the given action
			 *         index.
			 *
			 * Plugins can optionally override function if they want actions to
			 * be placed in the window tool-bar.
			 */
			virtual ActionLocation actionToolLocation(size_t index) const;

		private:
			friend class PluginMan;
			QVector<Factory*> _factories;
			QVector<Project*> _projects;
			QVector<Serializer*> _extensions;
			QVector<QAction*> _actions;
			bool _attached;
		};
	}
}
