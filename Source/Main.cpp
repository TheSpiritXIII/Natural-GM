/**
 *  @file Main.hpp
 *	@section License
 *
 *      Copyright (C) 2013 Daniel Hrabovcak
 *
 *      This file is a part of the Natural GM IDE. MIT License.
 *
 *      Permission is hereby granted, free of charge, to any person obtaining a copy
 *		of this software and associated documentation files (the "Software"), to deal
 *		in the Software without restriction, including without limitation the rights
 *		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *		copies of the Software, and to permit persons to whom the Software is
 *		furnished to do so, subject to the following conditions:
 *
 *		The above copyright notice and this permission notice shall be included in
 *		all copies or substantial portions of the Software.
 *
 *		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *		THE SOFTWARE.
**/
#include "Global.hpp"
#ifdef NGM_LOG_TO_FILE
#include "ErrorLogger.hpp"
#endif
#include "WindowManager.hpp"

int main(int argc, char *argv[])
{
#ifdef NGM_LOG_TO_FILE
	qInstallMessageHandler(NGM::Debug::messageHandler);
#endif

	NGM::Manager::WindowManager app(argc, argv);
	app.setApplicationName("Natural GM");

#ifdef NGM_LOG_TO_FILE
	int result = app.exec();
	if (QFile("log.txt").exists())
	{
		QMessageBox::critical(0, "Errors Found!", "Errors were found when "
		"running this program. Please report and send the log file (log.txt) "
		"to the author. Delete the log file to remove this warning.");
	}
	return result;
#else
	return app.exec();
#endif
}
