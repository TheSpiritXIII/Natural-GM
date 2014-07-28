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

namespace NGM
{
	namespace Manager
	{
		/**************************************************//*!
		*  @brief  Loads generic and plugin requested icons.
		*
		* Icons are generally loaded in 3 different places.
		* First and foremost, each icon is loaded from the
		* same basic location, in the "Icons" directory.
		*
		* From that directory, there are several other ones,
		* which denote themes. Extension and Resource icons
		* are able to use a "Common" theme, which is used
		* when a requested icon is not found in the current
		* theme. Generic and Core icons do not use this
		* theme.
		*
		* Inside each theme directory, there are Core (for
		* action icons), Generic (for generic icons),
		* Extension (for extension icons) and Resource (for
		* resource icons) directories. This class is
		* responsible for loading all generic icons and the
		* core icons that are context specific.
		******************************************************/
		struct IconManager
		{
			/**************************************************//*!
			*  @brief  Contains a list of generic icons.
			******************************************************/
			enum GenericIcon : uint8_t
			{
				NewFile         = 0,
				OpenFile        = 1,
				GroupOpen       = 2,
				GroupClosed     = 3,
				Accept	        = 4,
				Reject          = 5,
				Modify          = 6,
				Warning	        = 7,
				Critical        = 8,
				Add             = 9,
				Delete          = 10,
				Move            = 11,
				Pencil          = 12,
				PaintBrush      = 13,
				PaintCan        = 14,
				Palette         = 15,
				ArrowUp         = 16,
				ArrowDown       = 17,
				ArrowLeft       = 18,
				ArrowRight      = 19,
				User            = 20,
				Home            = 21,
				Globe           = 22,
				Computer        = 23,
				Pin             = 24,
				Unpin           = 25,
				Attach          = 26,
				Music           = 27,
				Timer           = 28,
				VolumeUp        = 29,
				VolumeDown      = 30,
				Mute            = 31,
				Microphone      = 32,
				Reload          = 33,
				Lock            = 34,
				Unlock          = 35,
				Background      = 36,
				Image           = 37,
				Model           = 38,
				Path            = 39,
				Font            = 40,
				Message         = 41,
				Help            = 42,
				Play            = 43,
				Stop            = 44,
				Pause           = 45,
				Rewind          = 46,
				FastFoward      = 47,
				SkipEnd         = 48,
				SkipStart       = 49,
				Repeat          = 50,
				Equalizer       = 51,
				IconView        = 52,
				ListView        = 53,
				GridView        = 54,
				Shader          = 55,
				Script          = 56,
				Breakpoint      = 57,
				Switch          = 58,
				Union           = 59,
				Intersection    = 60,
				Difference      = 61,
				Visible         = 62,
				Invisible       = 63,
				MoveForeward    = 64,
				MoveBackward    = 65,
				MoveFront       = 66,
				MoveBack        = 67,
				FlipVertical    = 68,
				FlipHorizontal  = 69,
				RotateClockwise = 70,
				RotateCounter   = 71,
				AlignTop        = 72,
				AlignBottom     = 73,
				AlignMiddle     = 74,
				AlignLeft       = 75,
				AlignRight      = 76,
				AlignCenter     = 77,
				Table           = 78,
				TextCenter      = 79,
				TextLeft        = 80,
				TextRight       = 81,
				TextJustify     = 82,
				TextBold        = 83,
				TextItalic      = 84,
				TextUnderline   = 85,
				TextStrike      = 86,
				TextListBullets = 87,
				TextListNumbers = 88,
				TextSubScript   = 89,
				TextSuperScript = 90
			};

			/**************************************************//*!
			*  @brief  Contains a list of core action icons.
			******************************************************/
			enum CoreIcon : size_t
			{
				Save        = 0,
				SaveAs      = 1,
				SaveAll     = 2,
				Close       = 3,
				CloseAll    = 4,
				Print       = 5,
				Undo        = 6,
				Redo        = 7,
				Cut         = 8,
				Copy        = 9,
				Paste       = 10,
				SelectAll   = 11,
				ZoomIn      = 12,
				ZoomOut     = 13,
				Zoom        = 14,
				FindReplace = 15
			};

			/**************************************************//*!
			*  @brief  Returns the current icon theme.
			******************************************************/
			QString theme() const;

			/**************************************************//*!
			*  @brief  Returns the list of available generic
			*          icons.
			*  @note   This is not a list of loaded icons, but
			*          the number of total icons possible.
			******************************************************/
			uint8_t genericIconCount() const;

			/**************************************************//*!
			*  @brief  Returns the requested generic icon.
			******************************************************/
			const QIcon &genericIcon(GenericIcon icon) const;

			/**************************************************//*!
			*  @brief  Returns the list of available generic
			*          icons.
			*  @note   This is not a list of loaded icons, but
			*          the number of total icons possible.
			******************************************************/
			uint8_t coreIconCount() const;

			/**************************************************//*!
			*  @brief  Returns the requested core action icon.
			******************************************************/
			const QIcon &coreIcon(CoreIcon icon) const;

			/**************************************************//*!
			*  @brief  Returns an icon with the give name,
			*          loading it if it does not exist.
			*
			* This is the best way to load icons that are not
			* offered in the generic icon list, but that might be
			* used across multiple plugins. The Extensions icon
			* directory is checked for loading the icon.
			*
			* Since it is usually unlikely that the icon will
			* exist in the current theme, it is best to install
			* icons inside the user's "Common" theme.
			******************************************************/
			const QIcon &extensionIcon(const QString &name);

			/**************************************************//*!
			*  @brief  Returns a pixmap signifying transparency.
			*
			* The transparency pixmap should be used as a tiled
			* display where there is no content, for example, an
			* empty map editor or image.
			******************************************************/
			const QPixmap &transparencyPixmap() const;

			/**************************************************//*!
			*  @brief  Reloads all icons with the indicated
			*          theme and sets the theme.
			*
			* This function should not be called, except by the
			* application manager. When the application manager
			* calls this function, it also calls a signal to
			* signify that icons have been reloaded.
			******************************************************/
			void reloadIcons(const QString &theme);

		private:
			struct IconManagerPrivate;
			IconManagerPrivate *_impl;
		};
	}
}
