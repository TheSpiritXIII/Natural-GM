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
//#include "TabDisplayWidget.hpp"
//#include <QStylePainter>
//#include <QStyleOptionTabWidgetFrameV2>
//#include <QTabBar>

//NGM::Widget::TabDisplayWidget::TabDisplayWidget(QWidget *parent) :
//  QWidget(parent)
//{
//	_tabBar	= createTabBar();
//}

//QTabBar *NGM::Widget::TabDisplayWidget::tabBar() const
//{
//	return _tabBar;
//}

//void NGM::Widget::TabDisplayWidget::setWidget(QWidget *widget)
//{
//	_widget	= widget;
//	_widget->setParent(this);
//}

//QWidget *NGM::Widget::TabDisplayWidget::widget() const
//{
//	return _widget;
//}

//void NGM::Widget::TabDisplayWidget::paintEvent(QPaintEvent*)
//{

//	QStylePainter painter(this);
//	QStyleOptionTabWidgetFrameV2 option;
//	option.initFrom(this);
//	option.rect = _paneRect;
//	option.lineWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, 0, this);
//	option.rightCornerWidgetSize = QSize(0, 0);
//	option.leftCornerWidgetSize = QSize(0, 0);
//	option.shape = QTabBar::RoundedNorth;
//	option.tabBarSize = _tabBar->sizeHint();
//	QRect tabRect = _tabBar->geometry();
//	QRect selectedTabRect = tabBar()->tabRect(_tabBar->currentIndex());
//	option.tabBarRect = tabRect;
//	selectedTabRect.moveTopLeft(selectedTabRect.topLeft() + tabRect.topLeft());
//	option.selectedTabRect = selectedTabRect;
//	painter.drawPrimitive(QStyle::PE_FrameTabWidget, option);

//	_paneRect = style()->subElementRect(QStyle::SE_TabWidgetTabPane, &option, this);
//	QRect contentsRect = style()->subElementRect(QStyle::SE_TabWidgetTabContents, &option, this);
//	_tabBar->setGeometry(tabRect);
//	_widget->setGeometry(contentsRect);
//}

//QSize NGM::Widget::TabDisplayWidget::sizeHint() const
//{
//	return QSize(100, 100);
//	/*Q_D(const QTabWidget);
//	QSize lc(0, 0), rc(0, 0);
//	QStyleOption opt(0);
//	opt.init(this);
//	opt.state = QStyle::State_None;
//	if (d->leftCornerWidget)
//	lc = d->leftCornerWidget->sizeHint();
//	if(d->rightCornerWidget)
//	rc = d->rightCornerWidget->sizeHint();
//	if (!d->dirty) {
//	QTabWidget *that = (QTabWidget*)this;
//	that->setUpLayout(true);
//	}
//	QSize s(d->stack->sizeHint());
//	QSize t(d->tabs->sizeHint());
//	if(usesScrollButtons())
//	t = t.boundedTo(QSize(200,200));
//	else
//	t = t.boundedTo(QApplication::desktop()->size());
//	QSize sz = basicSize(d->pos == North || d->pos == South, lc, rc, s, t);
//	return style()->sizeFromContents(QStyle::CT_TabWidget, &opt, sz, this)
//	.expandedTo(QApplication::globalStrut());*/
//}

//QSize NGM::Widget::TabDisplayWidget::minimumSizeHint() const
//{
//	return QSize(100, 100);
//}

//QTabBar *NGM::Widget::TabDisplayWidget::createTabBar()
//{
//	return new QTabBar(this);
//}

//void NGM::Widget::TabDisplayWidget::initStyleOption(
//  QStyleOptionTabWidgetFrame *option) const
//{

//}

//void NGM::Widget::TabDisplayWidget::setUpLayout(bool check)
//{
//	if (check && !_dirty)
//	{
//		return;
//	}

//	if (!visible)
//	{
//		_dirty = true;
//		return;
//	}
//}
