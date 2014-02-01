/**
 *  @file HierarchyDockWidget.hpp
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
#include "HierarchyDockWidget.hpp"
#include "ResourceItemModel.hpp"
#include "SortRootProxyModel.hpp"
#include "ResourceTreeView.hpp"
#include "AppManager.hpp"
#include <QVBoxLayout>
#include <QLineEdit>

#include <queue>
using std::queue;

NGM::Widget::HierarchyDockWidget::HierarchyDockWidget(
		Manager::AppManager *manager, const QString &title, QWidget *parent,
		Qt::WindowFlags flags) : DockWidget(title, parent, flags)
{
	QWidget *baseWidget = new QWidget(this);
	QVBoxLayout *layout = new QVBoxLayout(baseWidget);
	layout->setMargin(0);
	layout->setSpacing(0);

	model = new Model::SortRootProxyModel(this);

	_filterEdit = new QLineEdit(baseWidget);
	_filterEdit->setPlaceholderText(tr("Filter..."));
	connect(_filterEdit, &QLineEdit::textChanged,
			model, &Model::SortRootProxyModel::setFilterFixedString);

	_treeView = new ResourceTreeView(manager->model(), baseWidget);
	_treeView->setAcceptDrops(true);
	_treeView->setHeaderHidden(true);
	_treeView->setUniformRowHeights(true);
	_treeView->setDropIndicatorShown(true);
	_treeView->setDragEnabled(true);
	_treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	_treeView->setDragDropMode(QAbstractItemView::InternalMove);
	model->setSourceModel(manager->model());
	model->setDynamicSortFilter(true);
	_treeView->setModel(model);
	model->setSourceView(_treeView);

	layout->addWidget(_filterEdit);
	layout->addWidget(_treeView);
	setWidget(baseWidget);
}

void NGM::Widget::HierarchyDockWidget::expandRoot(const int &row)
{
	queue<QModelIndex> q;
	q.push(model->index(row, 0));
	QModelIndex index;
	while (!q.empty())
	{
		index = q.front();
		_treeView->expand(index);
		q.pop();

		for (int i = 0; i != model->rowCount(index); ++i)
		{
			q.push(model->index(i, 0, index));
		}
	}
}

void NGM::Widget::HierarchyDockWidget::collapseRoot(const int &row)
{
	queue<QModelIndex> q;
	q.push(model->index(row, 0));
	QModelIndex index;
	while (!q.empty())
	{
		index = q.front();
		_treeView->collapse(index);
		q.pop();

		for (int i = 0; i != model->rowCount(index); ++i)
		{
			q.push(model->index(i, 0, index));
		}
	}
}

void NGM::Widget::HierarchyDockWidget::expandRow(const int &row)
{
	_treeView->expand(model->index(row, 0));
}

void NGM::Widget::HierarchyDockWidget::collapseRow(const int &row)
{
	_treeView->collapse(model->index(row, 0));
}
