/**
 *  @file Main.cpp
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
#include "Global.hpp"
#define NGM_FUTURE_IS_HERE
#ifndef NGM_DEBUG
#include "ErrorLogger.hpp"
#endif
#ifdef NGM_FUTURE_IS_HERE
#include "AppManager.hpp"
#else
#include "WindowManager.hpp"
#endif
#include "Variant.hpp"

int main(int argc, char *argv[])
{
#ifndef NGM_DEBUG
	qInstallMessageHandler(NGM::Debug::messageHandler);
#endif
#ifdef NGM_FUTURE_IS_HERE
	NGM::Manager::AppManager app(argc, argv);
	if (app.close())
	{
		return false;
	}
#else
	NGM::Manager::WindowManager app(argc, argv);
	app.setApplicationName("Natural GM");
#endif
	return app.exec();
}
