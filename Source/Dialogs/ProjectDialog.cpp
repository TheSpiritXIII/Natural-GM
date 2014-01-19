/**
 *  @file ProjectDialog.cpp
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
#include "../Global.hpp"
#include "Resource.hpp"
#include "Project.hpp"
#include "MainWindow.hpp"
#include "ProjectDialog.hpp"
#include "WindowManager.hpp"
#include "ActionManager.hpp"
#include "ProjectManager.hpp"
#include "ResourceProjectItem.hpp"
#include <QApplication>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QScrollArea>
#include <QDebug>
using std::pair;

namespace NGM
{
	namespace Dialog
	{
		ProjectDialog::ProjectDialog(Manager::ProjectManager *projectManager,
									 Manager::SettingManager *settingManager,
									 Manager::WindowManager *windowManager,
									 const bool& files, QWidget *parent) :
			QDialog(parent, Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint),
			windowManager(windowManager), projectManager(projectManager),
			settingManager(settingManager)
		{
			// Set the dialog properties.
			setMinimumSize(800, 480);
			setWindowTitle(tr("Create a Project"));

			QVBoxLayout *mainLayout = new QVBoxLayout(this);

			QWidget *topWidget = new QWidget(this);
			QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
			topLayout->setMargin(0);

			dirDefaultCheck = new QCheckBox(tr("Set as default project type"));
			dirDefaultCheck->setToolTip(tr("If checked, then this project type is stored "
			"and set as the default next time you create a project."));

			topLayout->addWidget(new QLabel(tr("<b>Choose a template:</b>")), 1);
			topLayout->addWidget(dirDefaultCheck);
			topLayout->setMargin(0);
			mainLayout->addWidget(topWidget);

			QWidget *projectWidget = new QWidget(this);
			QHBoxLayout *projectLayout = new QHBoxLayout(projectWidget);
			projectLayout->setMargin(0);

			projectTree = new QTreeWidget(this);
			projectTree->setHeaderLabel(tr("Project"));

			bool exists;
			settings |= files ? Files : 0;
			const std::multimap<const QString, Resource::Project*> l = files ? projectManager->getFileProjectList() : projectManager->getProjectList();

			// Populate the project category tree.
			for(auto& i : l)
			{
				exists = 0;
				QString root = i.second->category.left(i.second->category.indexOf('-'));
				QString sublevel = i.second->category.right(i.second->category.size()-i.second->category.indexOf('-')-1);
				for(int j = 0; j < projectTree->topLevelItemCount(); ++j)
				{
					if (root == projectTree->topLevelItem(j)->text(0))
					{
						if (i.second->category.indexOf('-') != -1)
						{
							for(int k = 0; k < projectTree->topLevelItem(j)->childCount(); ++k)
							{

								if (sublevel == projectTree->topLevelItem(j)->child(k)->text(0))
								{
									exists = true;
									break;
								}
							}
							if (!exists)
							{
								if (i.second->category.indexOf('-') != -1)
								{
									QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(sublevel));
									projectTree->topLevelItem(j)->addChild(item);
									exists = true;
								}
								break;
							}
						}
						else
						{
							exists = true;
						}
						break;
					}
				}
				if (!exists)
				{
					QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(root));
					if (i.second->category.indexOf('-') != -1)
					{
						item->addChild(new QTreeWidgetItem(QStringList(sublevel)));
					}
					QString location = windowManager->actionManager.getTheme()+"/project/"+item->text(0);
					if (location.size() != 0)
					{
						item->setIcon(0, QIcon(location));
					}
					projectTree->addTopLevelItem(item);
				}
			}

			projectTree->expandAll();
			projectTree->setStyleSheet("QTreeWidget::item{padding: 4px;}");
			projectLayout->addWidget(projectTree, 1);

			projectList = new QListWidget(this);
			projectList->setSelectionBehavior(QAbstractItemView::SelectRows);
			projectList->setStyleSheet("QListView::item{padding: 4px;}");
			projectLayout->addWidget(projectList, 1);

			QWidget *descWidget = new QWidget(this);
			QVBoxLayout *descLayout = new QVBoxLayout(descWidget);
			descLayout->setAlignment(Qt::AlignTop);

			QScrollArea *scrollArea = new QScrollArea(this);
			scrollArea->setFrameStyle(QFrame::NoFrame);
			scrollArea->setWidgetResizable(true);

			description = new QLabel(this);
			description->setWordWrap(true);
			description->setAlignment(Qt::AlignTop);
			descLayout->addWidget(description);

			descLayout->addWidget(new QLabel(tr("<b>Templates:</b> "), this));
			descLayout->addWidget(new QRadioButton(tr("Empty Project"), this));
			scrollArea->setWidget(descWidget);

			projectLayout->addWidget(scrollArea, 1);

			QWidget *fileWidget = new QWidget(this);
			QHBoxLayout *fileLayout = new QHBoxLayout(fileWidget);
			fileLayout->setMargin(0);

			fileLayout->addWidget(new QLabel(tr("Directory: "), this));
			directoryEdit = new QLineEdit(settingManager->oldDirectory, this);
			directoryEdit->setReadOnly(true);
			fileLayout->addWidget(directoryEdit, 2);

			browseButton = new QPushButton(tr("Browse"), this);
			connect(browseButton, &QPushButton::pressed, this, &ProjectDialog::browseRequest);
			fileLayout->addWidget(browseButton);

			dirUseCheck = new QCheckBox(tr("Use as default"), this);
			dirUseCheck->setChecked(settingManager->settings & Manager::SettingManager::UseDirectory);
			dirUseCheck->setToolTip(tr("If checked, then this directory is stored "
			"and set as the default next time you create a project/file."));
			fileLayout->addWidget(dirUseCheck);

			QWidget *nameWidget = new QWidget(this);
			QHBoxLayout *nameLayout = new QHBoxLayout(nameWidget);
			nameLayout->setMargin(0);

			if (~settings & Files)
			{
				nameLayout->addWidget(new QLabel(tr("Project Name: "), this));
			}
			else
			{
				nameLayout->addWidget(new QLabel(tr("File Name: "), this));
			}

			projectEdit = new QLineEdit("Project", this);
			nameLayout->addWidget(projectEdit);

			if (~settings & Files)
			{
				dirAddCheck = new QCheckBox(tr("Add new directory"), this);
				dirAddCheck->setChecked(settingManager->settings & Manager::SettingManager::AddDirectory);
				dirAddCheck->setToolTip(tr("If checked, then an extra directory is created "
				"before the project directory and named the same as the project."));
				nameLayout->addWidget(dirAddCheck);
			}

			dirTempCheck = new QCheckBox(tr("Create as temporary"));
			dirTempCheck->setToolTip(tr("Allows you to create a temporary project "
			"that allows you to work but doesn't require a save."));
			nameLayout->addWidget(dirTempCheck);
			connect(dirTempCheck, &QCheckBox::toggled, [this](bool checked)
			{
				projectEdit->setEnabled(!checked);
				directoryEdit->setEnabled(!checked);
				dirAddCheck->setEnabled(!checked);
				dirUseCheck->setEnabled(!checked);
				browseButton->setEnabled(!checked);
			});

			QPushButton *choose = new QPushButton(tr("Choose..."), this);
			connect(choose, &QPushButton::pressed, this, &ProjectDialog::chooseRequest);
			nameLayout->addWidget(choose);
			choose->setDefault(true);
			choose->setFocus();

			QPushButton *cancel = new QPushButton(tr("Cancel"), this);
			connect(cancel, &QPushButton::clicked, this, &ProjectDialog::cancelRequest);
			nameLayout->addWidget(cancel);

			mainLayout->addWidget(projectWidget);
			mainLayout->addWidget(fileWidget);
			mainLayout->addWidget(nameWidget);

			connect(projectTree, &QTreeWidget::currentItemChanged, this, &ProjectDialog::updateList);
			connect(projectList, &QListWidget::currentTextChanged, this, &ProjectDialog::updateDescription);
			projectTree->setCurrentItem(projectTree->topLevelItem(0));
		}

		ProjectDialog::~ProjectDialog()
		{
			// Inherit behavior.
		}

		void ProjectDialog::updateList(QTreeWidgetItem *current, QTreeWidgetItem*)
		{
			// First, erase old list.
			projectList->blockSignals(true);
			projectList->clear();

			// Get the name of the category.
			bool root = true;
			QString full = current->text(0);
			if (current->parent() != NULL)
			{
				root = false;
				full = current->parent()->text(0)+"-"+full;
			}

			cache = settings & Files ? projectManager->getFileProjectCategory(full, root) : projectManager->getProjectCategory(full, root);
			for (auto& i : cache)
			{
				projectList->addItem(new QListWidgetItem(i.first, projectList));
			}

			// Finally set the new current item.
			if (cache.size() != 0)
			{
				projectList->blockSignals(false);
				projectList->setCurrentRow(0);
			}
		}

		void ProjectDialog::updateDescription(QString text)
		{
			description->setText("<b>"+tr("Description")+": </b>"+cache.find(text)->second->description);
		}

		void ProjectDialog::cancelRequest()
		{
			close();
		}

		void ProjectDialog::browseRequest()
		{
			settings |= Wait;
			QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Directory"),
				QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
			if (dir != "")
			{
				directoryEdit->setText(dir);
			}
			settings &= ~Wait;
		}

		void ProjectDialog::chooseRequest()
		{
			QString proj = directoryEdit->text()+"/";
			if (settingManager->settings & Manager::SettingManager::AddDirectory)
			{
				proj += projectEdit->text()+"/";
			}
			QDir dir(proj);
			if (dir.exists(proj))
			{
				settings |= Wait;
				qDebug() << settings;
				qDebug() << (settings & Wait);
				QMessageBox message(this);
				message.setText(tr("The selected project directory already exists. "
				"Contents may be overwritten. Would you like to continue?"));
				message.addButton(QMessageBox::Yes);
				message.addButton(QMessageBox::No);
				message.addButton(QMessageBox::Cancel);
				message.setDefaultButton(QMessageBox::Ok);
				if (message.exec() == QMessageBox::Cancel)
				{
					settings &= ~Wait;
					return;
				}
			}
			bool made = dir.mkpath(proj);
			if (!made)
			{
				settings |= Wait;
				QMessageBox message(this);
				message.setText(tr("Error creating directory. Directory is invalid."));
				message.addButton(QMessageBox::Ok);
				message.exec();
				settings &= ~Wait;
				return;
			}
			Resource::Project *project = cache.find(projectList->currentItem()->text())->second;
			QString location = dir.absolutePath()+QChar('/')+projectEdit->text();
			Resource::Resource *resource = new Resource::Resource(project->type, location, Resource::Resource::IsFilename);
			Model::ResourceProjectItem *item = new Model::ResourceProjectItem(resource, project, projectEdit->text(), 0);
			windowManager->addProject(item);
			close();

			NGM::MainWindow *window = qobject_cast<NGM::MainWindow*>(QApplication::activeWindow());
			if (window)
			{
				//window->heirarchyOpenProject(item);
			}
		}

		void ProjectDialog::changeEvent(QEvent *event)
		{
			if (event->type() == QEvent::ActivationChange)
			{
				qDebug() << settings;
				if (isActiveWindow() || settings & Wait)
				{
					setWindowOpacity(1.0);
				}
				else
				{
					setWindowOpacity(0.5);
				}
			}
			QDialog::changeEvent(event);
		}
	}
}
