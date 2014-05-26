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
#include "Serializer.hpp"

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
		struct Serializer;

		/**************************************************//*!
		*  @brief  Loads projects using serializers.
		******************************************************/
		struct Loader
		{
			/**************************************************//*!
			*  @brief  Creates a loader with a serializer.
			******************************************************/
			Loader(Serializer *serializer);

			/**************************************************//*!
			*  @brief  Adds another serializer to the loader.
			******************************************************/
			void addSerializer(Serializer *serializer);

			/**************************************************//*!
			*  @brief  Creates the project file structure.
			******************************************************/
			void projectCreate(Model::ResourceProjectItem *item) const;

			/**************************************************//*!
			*  @brief  Saves the given project item.
			******************************************************/
			void projectSave(Model::ResourceProjectItem *item) const;

			/**************************************************//*!
			*  @brief  Loads the given project item.
			******************************************************/
			void projectLoad(Model::ResourceProjectItem *item) const;

			/**************************************************//*!
			*  @brief  Performs an optimized project load.
			******************************************************/
			void projectReload(Model::ResourceProjectItem *item) const;

			/**************************************************//*!
			*  @brief  Returns true if the indicated filename
			*          is allowed to be dropped in the given
			*          item, false otherwise.
			******************************************************/
			bool fileAllowed(const QString &filename,
			  const Model::ResourceBaseItem *item) const;

			/**************************************************//*!
			*  @brief  Adds the indicated file to the given item.
			*
			* This function should only be called after
			* validating the file with fileAllowed().
			******************************************************/
			void fileDropped(const QString &filename,
			  Model::ResourceBaseItem *item) const;

			/**************************************************//*!
			*  @brief  Returns true if the indicated item from
			*          is allowed to be dropped into the given
			*          item to, false otherwise.
			******************************************************/
			bool itemAllowed(const Model::ResourceBaseItem *from,
			  const Model::ResourceGroupItem *to) const;

			/**************************************************//*!
			*  @brief  Adds the item from into the item to.
			*
			* This function should only be called after
			* validating the file with itemAllowed().
			******************************************************/
			void itemDropped(const Model::ResourceBaseItem *from,
			  Model::ResourceGroupItem *to) const;

			/**************************************************//*!
			*  @brief  Called after an item is renamed.
			******************************************************/
			void itemRenamed(const QString &oldName,
			  const Model::ResourceBaseItem *item) const;

			/**************************************************//*!
			*  @brief  Called after an item is deleted.
			******************************************************/
			void itemDeleted(const Model::ResourceBaseItem *item) const;

			/**************************************************//*!
			*  @brief  Adds resource types to the given list,
			*          that can be added by the user to the given
			*          item.
			******************************************************/
			void itemAddRequested(QList<TypeDisplay> *typeList,
			  const Model::ResourceGroupItem *item) const;

		private:
			QVector<Serializer*> _serializers;
		};
	}
}
