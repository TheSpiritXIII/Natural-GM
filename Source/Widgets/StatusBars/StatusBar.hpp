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
		*	@brief	Sends queued messages to StatusBar.
		******************************************************/
		class StatusBarMessenger : public QObject
		{
			Q_OBJECT

		public:

			StatusBarMessenger() {}

		signals:

			/**************************************************//*!
			*	@brief	Sets the label text. This is added to the
			*			slo
			******************************************************/
			void setText(const QString &text) const;

			/**************************************************//*!
			*	@brief	Sets the progress value.
			******************************************************/
			void setProgress(int value) const;
		};

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
			*	@brief	Sets the label and progress bar to
			*			visible. All other widgets are removed.
			*	@param	min The minimum value of progress.
			*	@param	max The maximum value of progress.
			******************************************************/
			void setProgressLabel(int min, int max);

			/**************************************************//*!
			*	@brief	Adds the indicated widgets with stretches
			*			to the status bar. If the progress bar is
			*			visible, then this has no effect.
			******************************************************/
			//setWidgets(const WidgetStretchList &widgetStretchList);

			StatusBarMessenger *messenger();

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

			/**************************************************//*!
			*	@brief	Responsible for sending messages.
			******************************************************/
			StatusBarMessenger _messenger;
		};
	}
}

#endif // NGM__PRIORITYSTATUSBAR__HPP
