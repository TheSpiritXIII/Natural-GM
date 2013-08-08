/**
 *  @file SettingManager.hpp
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
#ifndef _NGM_SETTINGSMANAGER__HPP
#define _NGM_SETTINGSMANAGER__HPP
#include "Global.hpp"
#include <QColor>
#include <string>
#include <map>

namespace NGM
{
	namespace Managers
	{
		/**************************************************//*!
		*	@brief	Holds global application settings.
		******************************************************/
		class SettingManager
		{
		public:

			/**************************************************//*!
			*	@brief	The code colors.
			******************************************************/
			enum CodeColor
			{
				FontColor					=	0,
				PaperBackground				=	1,
				EdgeBackground				=	2,
				CaretBackground				=	3,
				CaretForeground				=	4,
				SelectionBackground			=	5,
				SelectionForeground			=	6,
				MarginBackground			=	7,
				MarginForeground			=	8,
				FoldMarginBackground		=	9,
				FoldMarginForeground		=	10,
				MatchedBraceBackground		=	11,
				MatchedBraceForeground		=	12,
				UnmatchedBraceBackground	=	13,
				UnmatchedBraceForeground	=	14,
				MarkerBackground			=	15,
				MarkerForeground			=	16,
				WhitespaceBackground		=	17,
				WhitespaceForeground		=	18,
				IndentationBackground		=	19,
				IndentationForeground		=	20,
				CalltipsBackground			=	21,
				CalltipsForeground			=	22,
				CalltipsHighlight			=	23,
				Reserved1					=	24,
				Reserved2					=	25,
				Reserved3					=	26,
				Reserved4					=	27,
				Reserved5					=	28,
				Reserved6					=	29,
				Reserved7					=	30,
				Reserved8					=	31,
				NormalText					=	32,
				Keywords					=	33,
				Number						=	34,
				Strings						=	35,
				Comments					=	36,
				Constants					=	37,
				BuiltInVariables			=	38,
				Functions					=	39,
				ScriptNames					=	40,
				ResourceNames				=	41,
				Reserved9					=	42,
				Reserved10					=	43,
				Reserved11					=	44,
				Reserved12					=	45,
				Reserved13					=	46,
				Reserved14					=	47,
				Reserved15					=	48
			};

			/**************************************************//*!
			*	@brief	Contains basic settings.
			******************************************************/
			uint32_t settings;

			/**************************************************//*!
			*	@brief	Contains basic color settings
			******************************************************/
			QColor colors[48];
		};
	}
}

#endif // _NGM_SETTINGSMANAGER__HPP
