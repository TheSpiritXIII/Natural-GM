/**
 *  @file ProjectDialog.cpp
 *  @breif description...
 *
 *  @section License
 *
 *      Copyright (C) 2013 Daniel Hrabovcak and Robert B. Colton
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

/*#include "ProjectDialog.h"

#include <QTextEdit>
#include <QDir>
#include <QLabel>
#include <QTreeWidget>
#include <QHeaderView>
#include <QRadioButton>
#include <QFileDialog>
#include <QMessageBox>
#include "BasicItem.h"
#include <QDebug>

namespace NGM
{
	ProjectDialog::ProjectDialog(Resource::Project (&projects)[64], unsigned int amount, Settings *settings, Model::BasicModel *model, QWidget *parent)
		: QDialog(parent, Qt::WindowCloseButtonHint),
		projects(projects), amount(amount), settings(settings), model(model)
	{
		// Set the dialog settings.
		setMinimumSize(800, 480);
		setWindowTitle(tr("Create a Project"));

		QVBoxLayout *mainLayout = new QVBoxLayout(this);

		QWidget *topWidget = new QWidget(this);
		QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
		topLayout->setMargin(0);

		dirDefaultCheck = new QCheckBox(tr("Set as default project type"));

		topLayout->addWidget(new QLabel(tr("<b>Choose a template:</b>")), 1);
		topLayout->addWidget(dirDefaultCheck);
		topLayout->setMargin(0);
		mainLayout->addWidget(topWidget);

		QWidget *projectWidget = new QWidget(this);
		QHBoxLayout *projectLayout = new QHBoxLayout(projectWidget);
		projectLayout->setMargin(0);

		projectTree = new QTreeWidget(this);
		projectTree->setHeaderLabel(tr("Project"));
		projectTree->setRootIsDecorated(false);
		for(size_t i = 0; i < amount; ++i)
		{
			bool exists = false;
			for(int j = 0; j < projectTree->topLevelItemCount(); ++j)
			{
				if (projects[i].type == projectTree->topLevelItem(j)->text(0))
				{
					exists = true;
					break;
				}
			}
			if (!exists)
			{
				QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(projects[i].type));
				item->setIcon(0, QIcon("icons/"+settings->iconTheme+"/project/"+item->text(0)));
				projectTree->addTopLevelItem(item);
			}
		}
		projectTree->setStyleSheet("QTreeWidget::item{padding: 4px;}");
		projectLayout->addWidget(projectTree, 1);

		projectList = new QListWidget(this);
		projectList->setSelectionBehavior(QAbstractItemView::SelectRows);
		projectList->setStyleSheet("QListView::item{padding: 4px;}");
		projectLayout->addWidget(projectList, 1);

		QWidget *descWidget = new QWidget(this);
		QVBoxLayout *descLayout = new QVBoxLayout(descWidget);
		descLayout->setMargin(0);
		descLayout->setAlignment(Qt::AlignTop);

		description = new QLabel(this);
		description->setWordWrap(true);
		descLayout->addWidget(description);

		descLayout->addWidget(new QLabel(tr("<b>Templates:</b> "), this));
		descLayout->addWidget(new QRadioButton(tr("Empty Project"), this));

		projectLayout->addWidget(descWidget, 1);

		QWidget *fileWidget = new QWidget(this);
		QHBoxLayout *fileLayout = new QHBoxLayout(fileWidget);
		fileLayout->setMargin(0);

		fileLayout->addWidget(new QLabel(tr("Directory: "), this));
		directoryEdit = new QLineEdit(settings->directory, this);
		directoryEdit->setReadOnly(true);
		fileLayout->addWidget(directoryEdit, 2);

		QPushButton *browseButton = new QPushButton(tr("Browse"), this);
		connect(browseButton, &QPushButton::pressed, this, &ProjectDialog::browse);
		fileLayout->addWidget(browseButton);

		dirUseCheck = new QCheckBox(tr("Use as default"), this);
		dirUseCheck->setChecked(settings->settings & Settings::UseDirectory);
		fileLayout->addWidget(dirUseCheck);

		QWidget *nameWidget = new QWidget(this);
		QHBoxLayout *nameLayout = new QHBoxLayout(nameWidget);
		nameLayout->setMargin(0);

		nameLayout->addWidget(new QLabel(tr("Project Name: "), this));

		projectEdit = new QLineEdit("Project", this);
		nameLayout->addWidget(projectEdit);

		dirAddCheck = new QCheckBox(tr("Add new directory"), this);
		dirAddCheck->setChecked(settings->settings & Settings::AddDirectory);
		nameLayout->addWidget(dirAddCheck);

		QPushButton *choose = new QPushButton(tr("Choose..."), this);
		connect(choose, &QPushButton::pressed, this, &ProjectDialog::choose);
		nameLayout->addWidget(choose);

		QPushButton *cancel = new QPushButton(tr("Cancel"), this);
		connect(cancel, &QPushButton::clicked, this, &ProjectDialog::cancel);
		nameLayout->addWidget(cancel);

		mainLayout->addWidget(projectWidget);
		mainLayout->addWidget(fileWidget);
		mainLayout->addWidget(nameWidget);

		connect(projectTree, &QTreeWidget::currentItemChanged, this, &ProjectDialog::updateList);
		connect(projectList, &QListWidget::currentRowChanged, this, &ProjectDialog::updateDescription);
		projectTree->setCurrentItem(projectTree->topLevelItem(0));
	}

	ProjectDialog::~ProjectDialog()
	{
	}

	void ProjectDialog::updateList(QTreeWidgetItem *current, QTreeWidgetItem *previous)
	{
		Q_UNUSED(previous);

		// First, erase old list.
		projectList->clear();
		this->current = 255;

		// Then repopulate.
		for(size_t i = 0; i < amount; ++i)
		{
			if (projects[i].type == current->text(0))
			{
				QListWidgetItem *item = new QListWidgetItem(projects[i].name);
				item->setIcon(QIcon("icons/"+settings->iconTheme+"/project/"+item->text()));
				projectList->addItem(item);
				if (this->current == 0xFF)
				{
					this->current = i;
				}
			}
		}

		// Finally set the new current item.
		projectList->setCurrentRow(0);
	}

	void ProjectDialog::updateDescription(int row)
	{
		// Update the text of description label.
		for(size_t i = 0; i < amount; ++i)
		{
			if (projects[i].name == projectList->item(row)->text())
			{
				description->setText(projects[i].desc);
			}
		}
	}

	void ProjectDialog::cancel()
	{
		close();
	}

	void ProjectDialog::browse()
	{
		QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Directory"),
			"", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		if (dir != "")
		{
			directoryEdit->setText(dir);
		}
	}

	void ProjectDialog::choose()
	{
		QString proj = directoryEdit->text()+"/";
		if (settings->settings & Settings::AddDirectory)
		{
			proj += projectEdit->text()+"/";
		}
		QDir dir(proj);
		if (dir.exists(proj))
		{
			QMessageBox message;
			message.setText(tr("The selected project directory already exists. "
			"Contents may be overwritten. Would you like to continue?"));
			message.addButton(QMessageBox::Ok);
			message.addButton(QMessageBox::Reset);
			message.addButton(QMessageBox::Abort);
			message.setDefaultButton(QMessageBox::Ok);
			message.exec();
		}
		bool made = dir.mkpath(proj);
		if (!made)
		{
			QMessageBox message;
			message.setText(tr("Error creating directory. Directory is invalid."));
			message.addButton(QMessageBox::Ok);
			message.exec();
			return;
		}
		Model::ResourceItem *item = projects[current].serializer->loadFile(proj + projectEdit->text() + projects[current].extension);
		qDebug() << item;
		model->append(item);
		close();
	}
}
*/
