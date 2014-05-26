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
#include <QMap>
#include <QIcon>
#include <QImage>
#include <QVector>
#include <QPixmap>
#include "Variant.hpp"

namespace NGM
{
	namespace API
	{
		struct SerialObject;
		struct SerialImage;
		struct SerialAnimation;
		struct SerialBlob;
		struct SerialPixmap;
		struct SerialIcon;
		struct SerialVariant;

		/**************************************************//*!
		*  @brief  An abstract data type.
		*
		* This class is never used directly. Instead,
		* inherited class should be cast from this class and
		* used instead, using the identifier to confirm that
		* the cast is valid.
		******************************************************/
		struct SerialData
		{
			/**************************************************//*!
			*  @brief  Returns the identifier id of this class.
			******************************************************/
			uint32_t identifier() const;

			/**************************************************//*!
			*  @brief  Provides a safe cast to a SerialObject.
			******************************************************/
			virtual SerialObject *toObject();

			/**************************************************//*!
			*  @brief  Provides a safe cast to a SerialImage.
			******************************************************/
			virtual SerialImage *toImage();

			/**************************************************//*!
			*  @brief  Provides a safe cast to a SerialAnimation.
			******************************************************/
			virtual SerialAnimation *toAnimation();

			/**************************************************//*!
			*  @brief  Provides a safe cast to a SerialBlob.
			******************************************************/
			virtual SerialBlob *toBlob();

			/**************************************************//*!
			*  @brief  Provides a safe cast to a SerialPixmap.
			******************************************************/
			virtual SerialPixmap *toPixmap();

			/**************************************************//*!
			*  @brief  Provides a safe cast to a SerialIcon.
			******************************************************/
			virtual SerialIcon *toIcon();

			/**************************************************//*!
			*  @brief  Provides a safe cast to a SerialVariant.
			******************************************************/
			virtual SerialVariant *toVariant();

		protected:

			/**************************************************//*!
			*  @brief  Creates a class by setting an identifier
			*          value for it.
			*  @see    SerialID
			*
			* As a convention, identifiers should use their first
			* two bits as a plugin identifier and the last two
			* for the actual type identifier. It is important
			* for these to be unique, as they are used by plugins
			* for validating casts.
			******************************************************/
			SerialData(uint32_t identifier);

		private:
			uint32_t _identifier;
		};

		/**************************************************//*!
		*  @brief  Stores children.
		******************************************************/
		struct SerialObject : SerialData
		{
			/**************************************************//*!
			*  @brief  Creates an empty object.
			******************************************************/
			SerialObject();

			/**************************************************//*!
			*  @brief  Returns this.
			******************************************************/
			SerialObject *toObject();

			/**************************************************//*!
			*  @brief  Maps data to attribute names.
			******************************************************/
			QMap<QString, SerialData*> children;

			/**************************************************//*!
			*  @brief  Returns the data identifier.
			******************************************************/
			static uint32_t id();
		};

		/**************************************************//*!
		*  @brief  Stores a single image.
		******************************************************/
		struct SerialImage : SerialData
		{
			/**************************************************//*!
			*  @brief  Creates an empty object.
			******************************************************/
			SerialImage();

			/**************************************************//*!
			*  @brief  Returns this.
			******************************************************/
			SerialImage *toImage();

			/**************************************************//*!
			*  @brief  Contains an image.
			******************************************************/
			QImage image;

			/**************************************************//*!
			*  @brief  Returns the data identifier.
			******************************************************/
			static uint32_t id();
		};

		/**************************************************//*!
		*  @brief  Stores a group of images.
		******************************************************/
		struct SerialAnimation : SerialData
		{
			/**************************************************//*!
			*  @brief  Creates an empty object.
			******************************************************/
			SerialAnimation();

			/**************************************************//*!
			*  @brief  Returns this.
			******************************************************/
			SerialAnimation *toAnimation();

			/**************************************************//*!
			*  @brief  Contains images.
			******************************************************/
			QVector<QImage> images;

			/**************************************************//*!
			*  @brief  Returns the data identifier.
			******************************************************/
			static uint32_t id();
		};

		/**************************************************//*!
		*  @brief  Stores a blob of information.
		******************************************************/
		struct SerialBlob : SerialData
		{
			/**************************************************//*!
			*  @brief  Creates an empty object.
			******************************************************/
			SerialBlob();

			/**************************************************//*!
			*  @brief  Returns this.
			******************************************************/
			SerialBlob *toBlob();

			/**************************************************//*!
			*  @brief  Contains data.
			******************************************************/
			char *data;

			/**************************************************//*!
			*  @brief  Returns the data identifier.
			******************************************************/
			static uint32_t id();
		};

		/**************************************************//*!
		*  @brief  Stores a pixmap.
		******************************************************/
		struct SerialPixmap : SerialData
		{
			/**************************************************//*!
			*  @brief  Creates an empty object.
			******************************************************/
			SerialPixmap();

			/**************************************************//*!
			*  @brief  Returns this.
			******************************************************/
			SerialPixmap *toPixmap();

			/**************************************************//*!
			*  @brief  Contains a pixmap.
			******************************************************/
			QPixmap pixmap;

			/**************************************************//*!
			*  @brief  Returns the data identifier.
			******************************************************/
			static uint32_t id();
		};

		/**************************************************//*!
		*  @brief  Stores an icon.
		******************************************************/
		struct SerialIcon : SerialData
		{
			/**************************************************//*!
			*  @brief  Creates an empty object.
			******************************************************/
			SerialIcon();

			/**************************************************//*!
			*  @brief  Returns this.
			******************************************************/
			SerialIcon *toIcon();

			/**************************************************//*!
			*  @brief  Contains an icon.
			******************************************************/
			QIcon icon;

			/**************************************************//*!
			*  @brief  Returns the data identifier.
			******************************************************/
			static uint32_t id();
		};

		/**************************************************//*!
		*  @brief  Stores a variant..
		******************************************************/
		struct SerialVariant : SerialData
		{
			/**************************************************//*!
			*  @brief  Creates an empty object.
			******************************************************/
			SerialVariant();

			/**************************************************//*!
			*  @brief  Returns this.
			******************************************************/
			SerialVariant *toVariant();

			/**************************************************//*!
			*  @brief  Contains a variant.
			******************************************************/
			Variant variant;

			/**************************************************//*!
			*  @brief  Returns the data identifier.
			******************************************************/
			static uint32_t id();
		};
	}
}
