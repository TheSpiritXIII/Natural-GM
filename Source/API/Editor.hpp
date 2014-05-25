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
#include <cstdint>

class QWidget;

namespace NGM
{
	namespace Context
	{
		struct EditContext;
	}
	namespace Manager
	{
		struct GlobalManager;
	}
	namespace API
	{
		struct Factory;

		/**************************************************//*!
		*  @brief  Stores and handles widgets.
		******************************************************/
		struct Editor final
		{
			/**************************************************//*!
			*  @brief  Bit flags for the status of a widget.
			******************************************************/
			enum StatusFlags
			{
				CanCopyCut   = 0b0000000000000001, /*<! Enables copy and cut. */
				CanPaste	 = 0b0000000000000010, /*!< Enables paste. */
				CanSelect    = 0b0000000000000100, /*!< Enables selecting */
				CanUndo	     = 0b0000000000001000, /*!< Enables undo. */
				CanRedo	     = 0b0000000000010000, /*!< Enables redo. */
				CanZoomIn    = 0b0000000000100000, /*!< Enables zooming in and
														zoom control. */
				CanZoomOut   = 0b0000000001000000, /*!< Enables zooming out and
														zoom control. */
				CanZoom      = 0b0000000001100000, /*!< Enables zooming. */
				IsModified   = 0b0000000010000000, /*!< Enables saving. */
				CanPrint     = 0b0000000100000000, /*!< Enables printing. */
			};

			/**************************************************//*!
			*  @see    StatusFlags
			******************************************************/
			typedef uint16_t Status;

			/**************************************************//*!
			*  @brief  Returns the editor factory.
			******************************************************/
			const Factory *factory() const;

			/**************************************************//*!
			*  @brief  Returns the editor widget.
			******************************************************/
			QWidget *widget() const;

			/**************************************************//*!
			*  @brief  Returns the status of the editor widget.
			******************************************************/
			Status status() const;

			/**************************************************//*!
			*  @brief  Connects the editor with the give context
			*          and the tools at the indicated location.
			******************************************************/
			void connect(Context::EditContext *context,
			  const QWidget *location);

			/**************************************************//*!
			*  @brief  Disconnects the editor with the give
			*          context and tools at the indicated
			*          location.
			******************************************************/
			void disconnect(Context::EditContext *context,
			  const QWidget *location);

		protected:
			Editor(Factory *factory, const Manager::GlobalManager *manager);
			friend class Factory;
		private:
			Factory *_factory;
			QWidget * const _widget;
		};
	}
}
