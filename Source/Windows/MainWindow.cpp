/**
 *  @file MainWindow.cpp
 *  @brief Declares a window class which controls properties.
 *
 *  @section License
 *
 *      Copyright (C) 2013 Daniel Hrabovcak
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
#include "MainWindow.hpp"
#include "WindowManager.hpp"
#include "ResourceSplitter.hpp"
#include <QDebug>
#include <QStandardItem>
#include <QStandardItemModel>
#include "../Models/BasicModel.hpp"
#include "../Models/BasicItem.hpp"
#include "ResourceProjectItem.hpp"
#include "ResourceItemModel.hpp"
#include <QStatusBar>

const auto DockMovable = QDockWidget::DockWidgetMovable;
const auto DockClosable = QDockWidget::DockWidgetClosable;
const auto DockFeatures = DockMovable | DockClosable;
namespace NGM
{
	MainWindow::MainWindow(Manager::WindowManager *data, QWidget *parent) :
		QMainWindow(parent), data(data), active(false)
	{
		setMinimumSize(640, 480);
		resize(800, 600);
		docks[DockHeirarchy] = new QDockWidget(tr("Heirarchy"), this);
		docks[DockHeirarchy]->setFeatures(DockFeatures);
		addDockWidget(Qt::LeftDockWidgetArea, docks[DockHeirarchy]);

		docks[DockProperties] = new QDockWidget(tr("Properties"), this);
		docks[DockProperties]->setFeatures(DockFeatures);
		tabifyDockWidget(docks[DockHeirarchy], docks[DockProperties]);
		docks[DockHeirarchy]->raise();

		docks[DockActions] = new QDockWidget(tr("Actions"), this);
		addDockWidget(Qt::RightDockWidgetArea, docks[DockActions]);

		docks[DockSearch] = new QDockWidget(tr("Search"), this);
		docks[DockSearch]->setFeatures(DockFeatures);
		tabifyDockWidget(docks[DockActions], docks[DockSearch]);
		docks[DockActions]->raise();

		docks[DockOutput] = new QDockWidget(tr("Output"), this);
		docks[DockOutput]->setFeatures(DockFeatures);
		addDockWidget(Qt::BottomDockWidgetArea, docks[DockOutput]);

		docks[DockMessages] = new QDockWidget(tr("Messages"), this);
		docks[DockMessages]->setFeatures(DockFeatures);
		tabifyDockWidget(docks[DockOutput], docks[DockMessages]);
		docks[DockOutput]->raise();

		docks[DockActions]->hide();
		docks[DockProperties]->hide();
		docks[DockSearch]->hide();
		docks[DockOutput]->hide();
		docks[DockMessages]->hide();

		active = true;

		resourceSplitter = new Widget::ResourceSplitter(data, this);
		//resourceSplitter->updateWindowFilePath = &MainWindow::setWindowFilePath;
		//resourceSplitter->updateWindowModified = &MainWindow::setWindowModified;
		setCentralWidget(resourceSplitter);

		//CALL_MEMBER_FN(*resourceSplitter, resourceSplitter->updateWindowFilePath)("Testing.");
		//(resourceSplitter->*updateWindowFilePath)("TESTING!");

		connect(docks[DockHeirarchy], &QDockWidget::visibilityChanged, this, &MainWindow::heirarchyVisibilityChanged);

		QStatusBar *status = new QStatusBar(this);
		setStatusBar(status);
		status->showMessage("Ready.");

		statusLabel = new QLabel(this);
		statusProgress = new QProgressBar(this);
		statusProgress->setTextVisible(false);

		status->addPermanentWidget(statusLabel, 3);
		status->addPermanentWidget(statusProgress, 1);
	}

	void MainWindow::updateTitle()
	{
		if (windowFilePath().length() != 0)
		{
			setWindowTitle(windowFilePath() + " - Natural GM");
		}
		else
		{
			setWindowTitle("Natural GM");
		}
	}

	void MainWindow::heirarchyOpenItem(const QModelIndex &index)
	{
		Model::ResourceBaseItem *item = reinterpret_cast<Model::ResourceBaseItem*>(index.internalPointer());
		resourceSplitter->resourceOpen(item);
	}

	void MainWindow::heirarchyVisibilityChanged(bool visible)
	{
		if (visible)
		{
			qDebug() << "Visible.";
			heirarchyView = new QTreeView(this);
			heirarchyView->setAlternatingRowColors(true);
			docks[DockHeirarchy]->setWidget(heirarchyView);
			heirarchyView->setModel(data->heirarchy);
			heirarchyView->setHeaderHidden(true);
			heirarchyView->setSelectionBehavior(QAbstractItemView::SelectItems);
			heirarchyView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
			heirarchyView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
			connect(heirarchyView, &QTreeView::doubleClicked, this, &MainWindow::heirarchyOpenItem);
			heirarchyView->setUniformRowHeights(true);
		}
		else
		{
			if (heirarchyView)
			{
				heirarchyView->deleteLater();
				heirarchyView = NULL;
			}
		}
	}

	void MainWindow::heirarchySetItem(const QString &name)
	{

	}
}
