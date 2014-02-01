/**
 *  @file ResourceTreeView.cpp
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
#include "ResourceTreeView.hpp"
#include "ResourceGroupItem.hpp"
#include "ResourceItemModel.hpp"
#include <QAbstractProxyModel>
#include <QContextMenuEvent>
#include <QMenu>
#include <cassert>
#include <queue>

#include <QDebug>

NGM::Widget::ResourceTreeView::ResourceTreeView(
	NGM::Model::ResourceItemModel *model, QWidget *parent) :
	QTreeView(parent), _model(model) {}

void NGM::Widget::ResourceTreeView::contextMenuEvent(
	QContextMenuEvent *event)
{
	QAction *action;
	QMenu menu;

	Model::ResourceBaseItem *item;
	QModelIndexList selected = selectedIndexes();
	bool isContent = selected.size() != 0, isGroup = true;
	for (int i = 0; i != selected.size(); ++i)
	{
		item = static_cast<Model::ResourceBaseItem*>(
					static_cast<QAbstractProxyModel*>(model())->mapToSource(
						selected[i]).internalPointer());
		if (!item->toContentItem())
		{
			isContent = false;
		}
		else
		{
			isGroup = false;
		}
	}

	if (isContent)
	{
		action = menu.addAction(tr("Open"));
		action->setEnabled(false);

		action = menu.addAction(tr("Open With..."));
		action->setEnabled(false);
		
		action = menu.addAction(tr("Open With System Default"));
		action->setEnabled(false);

		action = menu.addAction(tr("Open in Explorer"));
		action->setEnabled(false);

		menu.addSeparator();
	}

	if (selected.size() != 0)
	{
		action = menu.addAction(tr("Rename"));
		action->setEnabled(false);
		if (!isContent)
		{
			action->setEnabled(false);
		}

		action = menu.addAction(tr("Delete"));
		action->setEnabled(false);

		menu.addSeparator();
	}

	if (selected.size() == 1)
	{
		action = menu.addAction(isContent ? tr("Insert New...") :
											tr("Add New..."));
		action->setEnabled(false);

		action = menu.addAction(isContent ? tr("Insert Existing...") :
											tr("Add Existing..."));
		action->setEnabled(false);

		if (item->toGroupItem() && item->toGroupItem()->flags() &
				Model::ResourceBaseItem::CreateGroups)
		{
			action = menu.addAction(isContent ? tr("Insert Group...") :
												tr("Add Group..."));
			connect(action, &QAction::triggered,
					 this, &ResourceTreeView::addGroupSelected);
			action->setEnabled(false);
		}

		menu.addSeparator();
	}

	if (selected.size() != 0)
	{
		action = menu.addAction(tr("Cut"));
		action->setEnabled(false);

		action = menu.addAction(tr("Copy"));
		action->setEnabled(false);

		action = menu.addAction(tr("Paste"));
		action->setEnabled(false);

		menu.addSeparator();
	}

	if (isGroup && !_model->sort())
	{
		action = menu.addAction(selected.size() != 0 ? tr("Sort Group") :
													   tr("Sort All"));
		connect(action, &QAction::triggered,
				 this, &ResourceTreeView::sortSelected);
	}

	action = menu.addAction(tr("Sort Automatically"));
	action->setCheckable(true);
	action->setChecked(_model->sort());
	connect(action, &QAction::toggled,
			_model, &Model::ResourceItemModel::setSort);

	if (isGroup)
	{
		menu.addSeparator();

		action = menu.addAction(selected.size() == 0 ? tr("Expand All") :
													   tr("Expand Group"));
		connect(action, &QAction::triggered,
				this, &ResourceTreeView::expandSelected);

		action = menu.addAction(selected.size() == 0 ? tr("Collapse All") :
													   tr("Collapse Group"));
		connect(action, &QAction::triggered,
				this, &ResourceTreeView::collapseSelected);
	}

	menu.exec(event->globalPos());
}

void NGM::Widget::ResourceTreeView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		QModelIndex item = indexAt(event->pos());
		if (!item.isValid())
		{
			this->clearSelection();
		}
	}
	QTreeView::mousePressEvent(event);
}

void NGM::Widget::ResourceTreeView::sortSelected() const
{
	Model::ResourceGroupItem *group;
	QModelIndexList selected = selectedIndexes();
	for (int i = 0; i != selected.size(); ++i)
	{
		group = static_cast<Model::ResourceGroupItem*>(
					static_cast<QAbstractProxyModel*>(model())->mapToSource(
						selected[i]).internalPointer())->toGroupItem();
		group->sort();
	}
}

void NGM::Widget::ResourceTreeView::expandSelected()
{
	QModelIndexList selected = selectedIndexes();
	qDebug() << "?" << (selected.size() == 0);
	if (selected.size() == 0)
	{
		expandAll();
	}
	else
	{
		QModelIndex modelIndex;
		std::queue<QModelIndex> q;
		for (int i = 0; i != selected.size(); ++i)
		{
			expand(selected[i]);
			for (int j = 0; j != model()->rowCount(selected[i]); ++j)
			{
				q.push(model()->index(j, 0, selected[i]));
			}
		}
		while (!q.empty())
		{
			modelIndex = q.front();
			q.pop();

			expand(modelIndex);
			for (int i = 0; i != model()->rowCount(modelIndex); ++i)
			{
				q.push(model()->index(i, 0, modelIndex));
			}
		}
	}
}

void NGM::Widget::ResourceTreeView::collapseSelected()
{
	QModelIndexList selected = selectedIndexes();
	if (selected.size() == 0)
	{
		collapseAll();
	}
	else
	{
		QModelIndex modelIndex;
		std::queue<QModelIndex> q;
		for (int i = 0; i != selected.size(); ++i)
		{
			collapse(selected[i]);
			for (int j = 0; j != model()->rowCount(selected[i]); ++j)
			{
				q.push(model()->index(j, 0, selected[i]));
			}
		}
		while (!q.empty())
		{
			modelIndex = q.front();
			q.pop();

			collapse(modelIndex);
			for (int i = 0; i != model()->rowCount(modelIndex); ++i)
			{
				q.push(model()->index(i, 0, modelIndex));
			}
		}
	}
}

void NGM::Widget::ResourceTreeView::addGroupSelected()
{
	Model::ResourceGroupItem *group = static_cast<Model::ResourceGroupItem*>(
		static_cast<QAbstractProxyModel*>(model())->mapToSource(currentIndex()).
				internalPointer())->toGroupItem();
	Model::ResourceGroupItem *item = new Model::ResourceGroupItem("Group");
	group->insert(item);
	edit(static_cast<QAbstractProxyModel*>(model())->
		 mapFromSource(item->index()));
}
