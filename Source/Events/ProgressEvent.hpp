/**
 *  @file ProgressTextEvent.cpp
 *	@section License
 *
 *      Copyright (C) 2013-2014 Daniel Hrabovcak
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
#ifndef NGM__PROGRESSTEXTEVENT__HPP
#define NGM__PROGRESSTEXTEVENT__HPP
#include <QEvent>
#include <QString>

namespace NGM
{
	namespace Event
	{
		/**************************************************//*!
		*	@brief	An an event that tells the application to
		*			display text in the window status bar.
		******************************************************/
		class ProgressTextEvent : public QEvent
		{
		public:

			/**************************************************//*!
			*	@brief	The unique identifier for this event
			*			type.
			******************************************************/
			static const QEvent::Type id = static_cast<QEvent::Type>(
						QEvent::User + 1001);

			/**************************************************//*!
			*	@brief	Sets the event's text. This is what the
			*			label is set to.
			******************************************************/
			ProgressTextEvent(const QString &text);

			/**************************************************//*!
			*	@brief	Returns the stored text.
			******************************************************/
			inline QString getText() const
			{
				return _text;
			}

		private:

			/**************************************************//*!
			*	@brief	Contains the pending text.
			******************************************************/
			QString _text;
		};

		/**************************************************//*!
		*	@brief	An an event that tells the application to
		*			set the value of the progress bar that
		*			is displayed on the status bar.
		******************************************************/
		class ProgressValueEvent : public QEvent
		{
		public:

			/**************************************************//*!
			*	@brief	The unique identifier for this event
			*			type.
			******************************************************/
			static const QEvent::Type id = static_cast<QEvent::Type>(
						QEvent::User + 1002);

			/**************************************************//*!
			*	@brief	Sets the event's progress value. This is
			*			what the progress value is set to.
			******************************************************/
			ProgressValueEvent(int value);

			/**************************************************//*!
			*	@brief	Returns the stored value.
			******************************************************/
			inline int getValue() const
			{
				return _value;
			}

		private:

			/**************************************************//*!
			*	@brief	Contains the pending value.
			******************************************************/
			int _value;
		};

		/**************************************************//*!
		*	@brief	An an event that tells the application to
		*			set the max value of the progress bar
		*			that is displayed on the status bar.
		******************************************************/
		class ProgressMaxEvent : public QEvent
		{
		public:

			/**************************************************//*!
			*	@brief	The unique identifier for this event
			*			type.
			******************************************************/
			static const QEvent::Type id = static_cast<QEvent::Type>(
						QEvent::User + 1003);

			/**************************************************//*!
			*	@brief	Sets the event's progress value. This is
			*			what the progress max value is set to.
			******************************************************/
			ProgressMaxEvent(int value);

			/**************************************************//*!
			*	@brief	Returns the stored value.
			******************************************************/
			inline int getValue() const
			{
				return _value;
			}

		private:

			/**************************************************//*!
			*	@brief	Contains the pending max value.
			******************************************************/
			int _value;
		};
	}
}

#endif // NGM__PROGRESSTEXTEVENT__HPP
