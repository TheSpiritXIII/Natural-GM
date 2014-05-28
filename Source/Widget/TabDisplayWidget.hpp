///*-
// *  Copyright (c) 2014 Daniel Hrabovcak
// *
// *  This program is free software: you can redistribute it and/or modify it
// *  under the terms of the GNU Lesser General Public License as published by the
// *  Free Software Foundation, either version 3 of the License, or (at your
// *  option) any later version.
// *
// *  This program is distributed in the hope that it will be useful, but WITHOUT
// *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// *  for more details.
//**/
//#pragma once
//#include <QWidget>

//class QTabBar;
//struct QStyleOptionTabWidgetFrame;

//namespace NGM
//{
//	namespace Widget
//	{
//		/**************************************************//*!
//		*  @brief  Contains a single content widget and a
//		*          tab-bar.
//		******************************************************/
//		class TabDisplayWidget : public QWidget
//		{
//			Q_OBJECT

//		public:

//			/**************************************************//*!
//			*  @brief  Creates a display widget with a parent.
//			******************************************************/
//			TabDisplayWidget(QWidget *parent = 0);

//			/**************************************************//*!
//			*  @brief  Returns the tab-bar.
//			******************************************************/
//			QTabBar *tabBar() const;

//			/**************************************************//*!
//			*  @brief  Sets the display content widget.
//			******************************************************/
//			void setWidget(QWidget *widget);

//			/**************************************************//*!
//			*  @brief  Returns the display content widget.
//			******************************************************/
//			QWidget *widget() const;

//		protected:

//			/**************************************************//*!
//			*  @brief  Paints the tab widget pane.
//			******************************************************/
//			virtual void paintEvent(QPaintEvent *);

//			/**************************************************//*!
//			*  @brief  Returns the preferred size.
//			******************************************************/
//			virtual QSize sizeHint() const;

//			/**************************************************//*!
//			*  @brief  Returns the preferred minimum size.
//			******************************************************/
//			virtual QSize minimumSizeHint() const;

//			/**************************************************//*!
//			*  @brief  Sets the tab bar.
//			*
//			* This function should be overwritten by subclasses
//			* that use a different QTabBar. This function is only
//			* called during the constructor.
//			******************************************************/
//			virtual QTabBar *createTabBar();

//			/**************************************************//*!
//			*  @brief  Initialize option with the values from
//			*          this widget.
//			*
//			* This method is useful for subclasses when they need
//			* a QStyleOptionTabWidgetFrame, but don't want to
//			* fill in all the information themselves.
//			******************************************************/
//			void initStyleOption(QStyleOptionTabWidgetFrame *option) const;

//		private:
//			void setUpLayout(bool check);
//			QWidget *_widget;
//			QTabBar *_tabBar;
//			QRect _paneRect;
//			bool _dirty;
//		};
//	}
//}
