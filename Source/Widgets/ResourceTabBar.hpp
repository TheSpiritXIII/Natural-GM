#pragma once
#ifndef _NGM_RESOURCETABBAR__HPP
#define _NGM_RESOURCETABBAR__HPP
#include <QTabBar>
#include <cstdint>

namespace NGM
{
	namespace Widget
	{
		class ResourceTabBar : public QTabBar
		{
		public:

			/**************************************************//*!
			*	@brief	Creates a tab bar with the indicated parent.
			******************************************************/
			ResourceTabBar(QWidget *parent = 0);

		protected:

			/**************************************************//*!
			*	@brief	Stores mouse positions (for dragging).
			******************************************************/
			void mousePressEvent(QMouseEvent *);

			/**************************************************//*!
			*	@brief	Detaches the current tab, if possible.
			******************************************************/
			void mouseMoveEvent(QMouseEvent *);

			/**************************************************//*!
			*	@brief	Adds a tab, if a dab is detached.
			******************************************************/
			void dragEnterEvent(QDragEnterEvent *event);

			/**************************************************//*!
			*	@brief	Sets event as accepted.
			******************************************************/
			void dropEvent(QDropEvent *event);

			/**************************************************//*!
			*	@brief	Moves the currently attached tab.
			******************************************************/
			void dragMoveEvent(QDragMoveEvent *event);

			/**************************************************//*!
			*	@brief	Detaches the current tab.
			******************************************************/
			void dragLeaveEvent(QDragLeaveEvent *event);

		private:

			/**************************************************//*!
			*	@brief	States for dragging.
			******************************************************/
			enum State
			{
				Dragging	=	0x01,
				EndPoint	=	0x02
			};

			/**************************************************//*!
			*	@brief	Signifies the currently clicked position.
			******************************************************/
			static int dragLeftPos;

			/**************************************************//*!
			*	@see	State
			******************************************************/
			static bool dragging;

			/**************************************************//*!
			*	@brief	The currently clicked index number.
			******************************************************/
			static int clickIndex;

			/**************************************************//*!
			*	@brief	Caches the currently dragged widget.
			******************************************************/
			static QWidget *dragWidget;

			/**************************************************//*!
			*	@brief	Caches the currently dragged text.
			******************************************************/
			static QString dragText;
		};
	}
}

#endif // _NGM_RESOURCETABBAR__HPP
