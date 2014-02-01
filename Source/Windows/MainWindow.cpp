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
#include "ResourceProjectItem.hpp"
#include "ResourceItemModel.hpp"
#include <QStatusBar>
#include <QItemDelegate>
#include <QCloseEvent>
#include <QMenu>
#include "Factory.hpp"
#include <QSignalMapper>
#include "Editor.hpp"

const auto DockMovable = QDockWidget::DockWidgetMovable;
const auto DockClosable = QDockWidget::DockWidgetClosable;
const auto DockFeatures = DockMovable | DockClosable;
namespace NGM
{
	MainWindow::MainWindow(Manager::WindowManager *data, QWidget *parent) :
		QMainWindow(parent), data(data), statusLabel(nullptr), statusProgressBar(nullptr)
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

		resourceSplitter = new Widget::ResourceSplitter(data, this);
		//resourceSplitter->updateWindowFilePath = &MainWindow::setWindowFilePath;
		//resourceSplitter->updateWindowModified = &MainWindow::setWindowModified;
		setCentralWidget(resourceSplitter);

		//CALL_MEMBER_FN(*resourceSplitter, resourceSplitter->updateWindowFilePath)("Testing.");
		//(resourceSplitter->*updateWindowFilePath)("TESTING!");

		connect(docks[DockHeirarchy], &QDockWidget::visibilityChanged, this, &MainWindow::heirarchyVisibilityChanged);

		QStatusBar *status = new QStatusBar(this);
		setStatusBar(status);
		//status->showMessage("Ready.");
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
		if (!item->toGroupItem())
		{
			if (item->toContentItem() && item->toContentItem()->content->type)
			{
				resourceSplitter->resourceOpen(item);
			}
		}
	}

	void MainWindow::heirarchyVisibilityChanged(bool visible)
	{
		if (visible)
		{
			qDebug() << "Visible.";
			heirarchyView = new QTreeView(this);
			heirarchyView->setUniformRowHeights(true);
			docks[DockHeirarchy]->setWidget(heirarchyView);
			heirarchyView->setModel(data->heirarchy);

			heirarchyView->setHeaderHidden(true);
			heirarchyView->setSelectionBehavior(QAbstractItemView::SelectItems);
			heirarchyView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
			heirarchyView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
			connect(heirarchyView, &QTreeView::doubleClicked, this, &MainWindow::heirarchyOpenItem);

			heirarchyView->setContextMenuPolicy(Qt::CustomContextMenu);
			connect(heirarchyView, &QTreeView::customContextMenuRequested,
				this, &MainWindow::heirarchyContextMenuRequested);
		}
		else
		{
			if (heirarchyView)
			{
				heirarchyView->deleteLater();
				heirarchyView = nullptr;
			}
		}
	}

	void MainWindow::closeEvent(QCloseEvent *event)
	{
		// Destroys this window, if possible.
		data->closeWindow(this);

		// Event is ignored. Only the Window Manager can destroy.
		event->ignore();
	}

	void MainWindow::heirarchyContextMenuRequested(const QPoint &point)
	{
		if (data->heirarchy->hasChildren() != 0)
		{
			QModelIndex index = heirarchyView->indexAt(point);
			if (index.isValid())
			{
				QMenu menu;
				Map<QAction*, int> actionFile, actionType;
				selectedItem = reinterpret_cast<Model::ResourceBaseItem*>(heirarchyView->currentIndex().internalPointer());
				Model::ResourceProjectItem *projectItem = selectedItem->toProjectItem();
				if (projectItem != nullptr)
				{
					//menu.addAction("Set as Active");
					menu.addAction("Close Project");
				}
				else if (selectedItem->toContentItem())
				{
					const Resource::Type *type = selectedItem->toContentItem()->content->type;
					qDebug() << "MADE IT THIS FAR";
					qDebug() << (selectedItem->toContentItem()->content->settings & Resource::Content::IsSystemPath);
					qDebug() << (!type || (type && type->name != QStringLiteral("file")));
					if ((selectedItem->toContentItem()->content->settings & Resource::Content::IsSystemPath) &&
						(!type || (type && type->name != QStringLiteral("file"))))
					{
						int c = 0;
						for (auto &i : data->projectManager.fileType()->queue())
						{
							actionFile.insert(Pair<QAction*, int>(menu.addAction("Open with "+i->name), c++));
						}
					}
				}
				QAction *result = menu.exec(heirarchyView->mapToGlobal(point));
				Map<QAction*, int>::iterator i = actionFile.find(result);
				qDebug() << result;
				if (i != actionFile.end())
				{
					qDebug() << "FOUND";
					openFileEditor(i->second);
				}
			}
		}
	}

	void MainWindow::initStatusMessage()
	{
		if (statusLabel == nullptr)
		{
			statusLabel = new QLabel(this);
			statusLabel->setTextFormat(Qt::PlainText);
			statusProgressBar = new QProgressBar(this);
		}
	}

	void MainWindow::destroyStatusMessage()
	{
		delete statusLabel;
		statusLabel = nullptr;
		delete statusProgressBar;
		statusProgressBar = nullptr;
	}

	void MainWindow::openFileEditor(int index)
	{
		int c = 0;
		for (auto &i : data->projectManager.fileType()->queue())
		{
			if (c++ == index)
			{
				resourceSplitter->resourceAddEditor(selectedItem, i,
					data->projectManager.fileSerializer(), true);
				break;
			}
		}
	}
}
