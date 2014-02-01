/**
 *  @file PriorityStatusBar.hpp
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
#ifndef NGM__PRIORITYSTATUSBAR__HPP
#define NGM__PRIORITYSTATUSBAR__HPP
#include <QStatusBar>

class QLabel;
class QProgressBar;

/*struct WidgetStretch
{
	QWidget *widget;
	int stretch;
};

typedef QList<WidgetStretch*> WidgetStretchList;*/

namespace NGM
{
	namespace Widget
	{
		/**************************************************//*!
		*	@brief	A status bar with an internal progress
		*			bar and text label, visible when there is
		*			an important message.
		******************************************************/
		class StatusBar : public QStatusBar
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Creates a status bar with the indicated
			*			parent by also setting a progress bar and
			*			label.
			******************************************************/
			StatusBar(QWidget *parent = 0);

			/**************************************************//*!
			*	@brief	Sets the label and progress bar to
			*			visible. All other widgets are removed.
			*	@param	max The maximum value of progress.
			******************************************************/
			void setProgressShow(int max);

			/**************************************************//*!
			*	@brief	Sets the value of the progress bar.
			******************************************************/
			void setProgressValue(int value);

			/**************************************************//*!
			*	@brief	Sets the text of the progress label.
			******************************************************/
			void setProgressText(const QString &text);

			/**************************************************//*!
			*	@brief	Removes the progress bar and display text
			*			denoting that the status bar is able to
			*			set widgets.
			******************************************************/
			void setReady();

			/**************************************************//*!
			*	@brief	Adds the indicated widgets with stretches
			*			to the status bar. If the progress bar is
			*			visible, then this has no effect.
			******************************************************/
			void setWidgets();//const WidgetStretchList &widgetStretchList);

		private:

			/**************************************************//*!
			*	@brief	The internal label. This is to the right
			*			of the progress bar.
			******************************************************/
			QLabel *_label;

			/**************************************************//*!
			*	@brief	The internal progress bar. This is to
			*			the left of the label.
			******************************************************/
			QProgressBar *_progress;
		};
	}
}

#endif // NGM__PRIORITYSTATUSBAR__HPP
