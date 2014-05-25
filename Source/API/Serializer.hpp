/*-
 *  Copyright (c) 2013 - 2014 Daniel Hrabovcak
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
#include <QString>

namespace NGM
{
	namespace Model
	{
		struct ResourceBaseItem;
		struct ResourceGroupItem;
		struct ResourceProjectItem;
	}
	namespace API
	{
		struct TypeDisplay
		{
			QString typeName;
			QString displayName;
		};

		/**************************************************//*!
		*  @brief  Handles project items.
		******************************************************/
		struct Serializer
		{
			/**************************************************//*!
			*  @brief  Creates the project file structure.
			******************************************************/
			virtual void projectCreate(
			  Model::ResourceProjectItem *item) const = 0;

			/**************************************************//*!
			*  @brief  Saves the given project item.
			******************************************************/
			virtual void projectSave(
			  Model::ResourceProjectItem *item) const = 0;

			/**************************************************//*!
			*  @brief  Loads the given project item.
			******************************************************/
			virtual void projectLoad(
			  Model::ResourceProjectItem *item) const = 0;

			/**************************************************//*!
			*  @brief  Performs an optimized project load.
			*
			* Ideally, this function should be optimized by
			* keeping resources that have already loaded, but
			* have not changed. By default, this function does
			* a call to projectCreate(), followed by a call to
			* projectLoad().
			******************************************************/
			virtual void projectReload(Model::ResourceProjectItem *item) const;

			/**************************************************//*!
			*  @brief  Returns true if the indicated filename
			*          is allowed to be dropped in the given
			*          item, false otherwise.
			*
			* By default, this function always returns false.
			******************************************************/
			virtual bool fileAllowed(const QString &filename,
			  const Model::ResourceBaseItem *item) const;

			/**************************************************//*!
			*  @brief  Adds the indicated file to the given item.
			*
			* This function is guaranteed to be called after a
			* validation using fileAllowed().
			******************************************************/
			virtual void fileDropped(const QString &filename,
			  Model::ResourceBaseItem *item) const;

			/**************************************************//*!
			*  @brief  Returns true if the indicated item from
			*          is allowed to be dropped into the given
			*          item to, false otherwise.
			*
			* By default, this function always returns false.
			******************************************************/
			virtual bool itemAllowed(const Model::ResourceBaseItem *from,
			  const Model::ResourceGroupItem *to) const;

			/**************************************************//*!
			*  @brief  Adds the item from into the item to.
			*
			* This function is guaranteed to be called after a
			* validation using itemAllowed().
			******************************************************/
			virtual void itemDropped(const Model::ResourceBaseItem *from,
			  Model::ResourceGroupItem *to) const;

			/**************************************************//*!
			*  @brief  Called after an item is renamed.
			*
			* This function is mainly intended for project types
			* that are required to change references, or require
			* other actions after a resource is renamed.
			******************************************************/
			virtual void itemRenamed(const QString &oldName,
			  const Model::ResourceBaseItem *item) const;

			/**************************************************//*!
			*  @brief  Called after an item is deleted.
			*
			* This function is mainly intended for project types
			* that are required to change references, or require
			* other actions after a resource is deleted.
			******************************************************/
			virtual void itemDeleted(const Model::ResourceBaseItem *item) const;

			/**************************************************//*!
			*  @brief  Adds resource types to the given list,
			*          that can be added by the user to the given
			*          item.
			*
			* This function is mainly intended for project types
			* that are required to change references, or require
			* other actions after a resource is deleted.
			******************************************************/
			virtual void itemAddRequested(QList<TypeDisplay> *typeList,
			  const Model::ResourceGroupItem *item) const = 0;
		};
	}
}
