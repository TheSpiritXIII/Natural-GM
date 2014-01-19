/**
 *  @file ProjectWidget.cpp
 *	@section License
 *
 *      Copyright (C) 2014 Daniel Hrabovcak
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
#include "ProjectWidget.hpp"
#include "ProjectItemModel.hpp"
#include "ProjectFilterProxyModel.hpp"
#include "SizableItemDelegate.hpp"
#include "AppManager.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTreeView>
#include <QListView>
using NGM::Model::ProjectItemModel;
using NGM::Model::ProjectSetItemModel;
using NGM::Model::ProjectSetModelItem;
using NGM::Model::ProjectFilterProxyModel;

NGM::Widget::ProjectWidget::ProjectWidget(const Manager::AppManager *manager,
	QWidget *parent, const QStringList categoryFilter) : QWidget(parent)
{
	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->setMargin(0);

	_categoryView = new QTreeView(this);
	_categoryView->setObjectName("ProjectCategoryView");
	_categoryView->setIconSize(QSize(32, 32));
	_categoryView->setUniformRowHeights(true);
	_projectSetModel = new ProjectSetItemModel(this);

	QVector<QVector<Resource::Project*>> v;
	manager->projectManager()->projectsByCategories(&v, categoryFilter);

	int location;
	QString category;
	for (int i = 0; i != v.size(); ++i)
	{
		location = v[i].at(0)->category.indexOf(QChar('-'));
		if (location != -1)
		{
			category = v[i].at(0)->category.left(location);
			for (int j = 0; j != _projectSetModel->childCount(); ++j)
			{
				if (_projectSetModel->child(j)->text() == category)
				{
					// Category exists.
					_projectSetModel->child(j)->addChild(new
						ProjectSetModelItem(v[i].at(0)->category.right(
						v[i].at(0)->category.size() - location - 1), v[i]));
					category.clear();
					break;
				}
			}
			if (!category.isEmpty())
			{
				// Category does not exist, but requires one.
				ProjectSetModelItem *parent =
						new ProjectSetModelItem(category);
				parent->addChild(new ProjectSetModelItem(v[i].at(0)->
					category.right(v[i].at(0)->category.size() -
								   location - 1), v[i]));
				_projectSetModel->addChild(parent);
			}
		}
		else
		{
			// Project type is not in a category.
			_projectSetModel->addChild(new ProjectSetModelItem
									   (v[i].at(0)->category, v[i]));
		}
	}

	_projectSetFilter = new ProjectFilterProxyModel(this);
	_projectSetFilter->setSourceModel(_projectSetModel);
	_categoryView->setModel(_projectSetFilter);
	_categoryView->setSortingEnabled(true);
	_categoryView->expandAll();
	connect(_categoryView->selectionModel(),
			&QItemSelectionModel::currentChanged,
			this, &ProjectWidget::categoryClicked);

	_projectView = new QListView(this);
	_projectView->setObjectName("Project_projectView");
	_projectView->setIconSize(QSize(48, 48));
	_projectView->setUniformItemSizes(true);
	_projectModel = new ProjectItemModel(this);
	_projectFilter = new QSortFilterProxyModel(this);
	_projectFilter->setSourceModel(_projectModel);
	_projectFilter->sort(0);
	_projectView->setModel(_projectFilter);
	connect(_projectView->selectionModel(),
			&QItemSelectionModel::currentChanged,
			this, &ProjectWidget::projectClicked);

	QWidget *categoryWidget = new QWidget(this);
	QVBoxLayout *categoryLayout = new QVBoxLayout(categoryWidget);
	categoryLayout->setMargin(0);
	categoryLayout->setSpacing(0);

	QLineEdit *filterEdit = new QLineEdit(this);
	filterEdit->setObjectName("ProjectCategoryFilter");
	filterEdit->setPlaceholderText(tr("Filter..."));
	connect(filterEdit, &QLineEdit::textChanged, _projectSetFilter,
			&ProjectFilterProxyModel::setFilterFixedString);

	categoryLayout->addWidget(_categoryView);
	categoryLayout->addWidget(filterEdit);
	layout->addWidget(categoryWidget);

	layout->addWidget(_projectView);

	_categoryView->setCurrentIndex(_projectSetFilter->index(0,
		_projectSetModel->hasRecent() ? 1 : 0, QModelIndex()));
}

const NGM::Resource::Project *NGM::Widget::ProjectWidget::currentProject() const
{
	return static_cast<Resource::Project*>(_projectFilter->mapToSource(
		_projectView->currentIndex()).internalPointer());
}

void NGM::Widget::ProjectWidget::setSearch(const QString &search)
{
	_projectSetModel->setSearch(search);
	_projectSetFilter->invalidate();
	_categoryView->expandAll();
}

void NGM::Widget::ProjectWidget::setDisplay(const Model::Display display)
{
	_projectSetModel->setDisplay(display);
	_projectSetFilter->invalidate();
	_categoryView->expandAll();
	QModelIndex top = _projectSetFilter->index(0, 0);
	_categoryView->setCurrentIndex(top);
	categoryClicked(top, QModelIndex());
}

void NGM::Widget::ProjectWidget::setIconMode(bool iconMode)
{
	if (iconMode)
	{
		_projectView->setViewMode(QListView::IconMode);
		_projectView->setItemDelegate(
					new Delegate::SizableItemDelegate(QSize(96, 96), this));
		_projectView->setGridSize(QSize(96, 96));
		_projectView->setResizeMode(QListView::Adjust);
		_projectView->setWordWrap(true);
	}
	else
	{
		_projectView->setViewMode(QListView::ListMode);
		_projectView->setItemDelegate(new QStyledItemDelegate(this));
		_projectView->setGridSize(QSize());
		_projectView->setWordWrap(false);
	}
}

void NGM::Widget::ProjectWidget::setDescending(bool set)
{
	_projectFilter->sort(0, set == true ? Qt::DescendingOrder :
										  Qt::AscendingOrder);
}

void NGM::Widget::ProjectWidget::categoryClicked(const QModelIndex &index,
											const QModelIndex&)
{
	if (index.isValid())
	{
		_projectSetModel->setItemModel(
					_projectSetFilter->mapToSource(index), _projectModel);
		_projectView->setCurrentIndex(_projectFilter->index(0, 0));
		emit projectChanged(currentProject());
	}
}

void NGM::Widget::ProjectWidget::projectClicked(const QModelIndex &index,
										   const QModelIndex &)
{
	emit projectChanged(static_cast<Resource::Project*>
						(_projectFilter->mapToSource(index).internalPointer()));
}
