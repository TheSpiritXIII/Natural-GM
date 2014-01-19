/**
 *  @file Global.hpp
 *	@section License
 *
 *      Copyright (C) 2013-2014 Daniel Hrabovcak
 *
 *      This file is part of the Natural GM IDE.
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
#ifndef NGM__GLOBAL__HPP
#define NGM__GLOBAL__HPP
#include <QString>
#include <cstdint>

#ifdef QT_DEBUG
#define NGM_DEBUG
#include <QDebug>
#endif

namespace NGM
{
	const uint16_t		NGM_BUILD_NUMBER			=	0;
	const QString		NGM_APPLICATION_NAME		=	QStringLiteral("Natural GM 0.1.0");
	const QString		NGM_APPLICATION_KEY			=	QStringLiteral("Natural-GM-Application");
	const QString		NGM_DEFAULT_THEME			=	QStringLiteral("Silk Icons");
	const int			NGM_TABBAR_RESIZE_TIMEOUT	=	2000;
}

#endif // NGM__GLOBAL__HPP
