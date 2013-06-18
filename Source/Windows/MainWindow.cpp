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

const auto DockMovable = QDockWidget::DockWidgetMovable;
const auto DockClosable = QDockWidget::DockWidgetClosable;
const auto DockFeatures = DockMovable | DockClosable;
namespace NGM
{
	MainWindow::MainWindow(Manager::WindowManager *data, QWidget *parent) :
		QMainWindow(parent), data(data), active(false)
	{
		/*docks[DockHierarchy] = new QDockWidget(tr("Heirarchy"), this);
		docks[DockHierarchy]->setFeatures(DockFeatures);
		addDockWidget(Qt::LeftDockWidgetArea, docks[DockHierarchy]);

		docks[DockProperties] = new QDockWidget(tr("Properties"), this);
		docks[DockProperties]->setFeatures(DockFeatures);
		tabifyDockWidget(docks[DockHierarchy], docks[DockProperties]);
		docks[DockHierarchy]->raise();

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

		docks[DockHierarchy]->close();
		docks[DockProperties]->close();
		docks[DockActions]->close();
		docks[DockSearch]->close();
		docks[DockOutput]->close();
		docks[DockMessages]->close();*/

		updateTitle();

		QWidget *widget = new QWidget();
		QVBoxLayout *layout = new QVBoxLayout(widget);
		setCentralWidget(widget);
		QTreeView *view = new QTreeView(this);
		layout->addWidget(view);

		QPushButton *button = new QPushButton("Yolo");
		layout->addWidget(button);

		data->hierarchy = new Model::BasicModel("name");
		item = new Model::BasicItem("Test");
		data->hierarchy->append(item);
		Model::BasicItem *item3 = new Model::BasicItem("Test24");
		data->hierarchy->append(item3);
		item3->append(new Model::BasicItem("Test43"));

		view->setModel(data->hierarchy);
		view->setHeaderHidden(true);
		view->setSelectionBehavior(QAbstractItemView::SelectItems);

		QStandardItemModel *mod = new QStandardItemModel();
		item2 = new QStandardItem("Hello");
		mod->appendRow(item2);
		//view->setModel(mod);

		connect(button, &QPushButton::pressed, [this] ()
		{
			//this->item->append(new Model::BasicItem("Other!"));
			this->item->append(new Model::BasicItem("Other!"));
			this->item2->appendRow(new QStandardItem("Othero!"));
		});

		active = true;
	}

	void MainWindow::updateTitle()
	{
		if (windowFilePath().length() != 0)
		{
			auto modified = [this] () { return isWindowModified() ? "*": ""; };
			setWindowTitle(windowFilePath() + modified() + " - Natural GM");
		}
		else
		{
			setWindowTitle("Natural GM");
		}
	}
}
