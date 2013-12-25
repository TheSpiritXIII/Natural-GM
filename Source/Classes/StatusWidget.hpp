// I don't know what this is for.
#ifndef STATUSWIDGET_HPP
#define STATUSWIDGET_HPP
#include <QStatusBar>

namespace NGM
{
	namespace Widget
	{
		class StatusWidget
		{
			QStatusBar *statusBar;
			inline void addWidget(QWidget *widget)
			{
				statusBar->addWidget(widget);
			}

		};
	}
}

#endif // STATUSWIDGET_HPP
