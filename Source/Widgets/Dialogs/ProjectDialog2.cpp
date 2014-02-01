/**
 *  @file ProjectDialog.hpp
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
#include "ProjectDialog2.hpp"
#include "ProjectWidget.hpp"
#include "AppManager.hpp"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QBoxLayout>
#include <QToolButton>
#include <QPushButton>
#include <QScrollArea>
#include <QRadioButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QDirIterator>
#include <QStringBuilder>
#ifndef NGM_PORTABLE
#include <QStandardPaths>
#endif

NGM::Dialog::ProjectDialog2::ProjectDialog2(const Manager::AppManager *manager,
	ProjectPointer *project, QString *location, QString *templater,
	ProjectPreferences *preferences, QWidget *parent) :
	QDialog(parent, Qt::Window), _project(project), _location(location),
	_template(templater), _preferences(preferences),
	_defaultDirectory(manager->settingManager()->defaultDirectory())
{
	setMinimumSize(854, 480);
	setWindowTitle(tr("Create a Project"));
	QVBoxLayout *layout = new QVBoxLayout(this);

	_projectWidget = new Widget::ProjectWidget(manager, this);
	connect(_projectWidget, &Widget::ProjectWidget::projectChanged,
			this, &ProjectDialog2::projectChanged);

	QWidget *headerWidget = new QWidget(this);
	QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
	headerLayout->setMargin(0);

	QLabel *chooseLabel = new QLabel(tr("Choose a template:"), this);
	chooseLabel->setTextFormat(Qt::PlainText);
	QFont font = chooseLabel->font();
	font.setBold(true);
	chooseLabel->setFont(font);

	QLineEdit *searchEdit = new QLineEdit(this);
	searchEdit->setPlaceholderText(tr("Search..."));
	searchEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	connect(searchEdit, &QLineEdit::textChanged, _projectWidget,
			&Widget::ProjectWidget::setSearch);

	_listViewButton = new QToolButton(this);
	_listViewButton->setText(tr("List"));
	_listViewButton->setToolTip(_listViewButton->text());
	_listViewButton->setIcon(manager->iconManager()->
							 genericIcons[Manager::IconManager::ListView]);
	_listViewButton->setCheckable(true);
	_listViewButton->setAutoRaise(true);
	_listViewButton->setChecked(~manager->settingManager()->
		projectPreferences & Manager::SettingManager::IconMode);
	connect(_listViewButton, &QToolButton::toggled,
			this, &ProjectDialog2::listButtonPressed);

	_iconViewButton = new QToolButton(this);
	_iconViewButton->setText(tr("Icons"));
	_iconViewButton->setToolTip(_iconViewButton->text());
	_iconViewButton->setIcon(manager->iconManager()->
							 genericIcons[Manager::IconManager::IconView]);
	_iconViewButton->setCheckable(true);
	_iconViewButton->setAutoRaise(true);
	connect(_iconViewButton, &QToolButton::toggled,
			this, &ProjectDialog2::iconButtonPressed);
	_iconViewButton->setChecked(manager->settingManager()->
		projectPreferences & Manager::SettingManager::IconMode);

	QWidget *chooseWidget = new QWidget(this);
	QHBoxLayout *chooseLayout = new QHBoxLayout(chooseWidget);
	chooseLayout->setMargin(0);
	chooseLayout->addWidget(chooseLabel);
	chooseLayout->addWidget(searchEdit);

	QComboBox *orderBox = new QComboBox(this);
	orderBox->addItem(tr("Ascending"));
	orderBox->addItem(tr("Descending"));
	void (QComboBox::*comboIndex)(int) = &QComboBox::currentIndexChanged;
	connect(orderBox, comboIndex, this, &ProjectDialog2::sortChanged);
	orderBox->setCurrentIndex(manager->settingManager()->
		projectPreferences & Manager::SettingManager::Descending);

	QWidget *displayWidget = new QWidget(this);
	QHBoxLayout *displayLayout = new QHBoxLayout(displayWidget);
	displayLayout->setMargin(0);
	displayLayout->addWidget(new QLabel(tr("Display:"), this), 0);
	displayLayout->addWidget(_listViewButton);
	displayLayout->addWidget(_iconViewButton);
	displayLayout->addWidget(orderBox, 2);

	QWidget *showWidget = new QWidget(this);
	QHBoxLayout *showLayout = new QHBoxLayout(showWidget);
	showLayout->setMargin(0);

	_displayFilesButton = new QToolButton(this);
	_displayFilesButton->setText(tr("Display Files"));
	_displayFilesButton->setAutoRaise(true);
	_displayFilesButton->setCheckable(true);
	connect(_displayFilesButton, &QToolButton::toggled,
			this, &ProjectDialog2::displayFiles);

	_displayProjectsButton = new QToolButton(this);
	_displayProjectsButton->setText(tr("Display Projects"));
	_displayProjectsButton->setAutoRaise(true);
	_displayProjectsButton->setCheckable(true);
	connect(_displayProjectsButton, &QToolButton::toggled,
			this, &ProjectDialog2::displayProjects);

	_displayFilesButton->setChecked(manager->settingManager()->
		projectPreferences & Manager::SettingManager::ShowFiles);
	_displayProjectsButton->setChecked(manager->settingManager()->
		projectPreferences & Manager::SettingManager::ShowGroups);

	showLayout->addStretch();
	showLayout->addWidget(_displayFilesButton);
	showLayout->addWidget(_displayProjectsButton);

	headerLayout->addWidget(chooseWidget, 1);
	headerLayout->addWidget(displayWidget, 1);
	headerLayout->addWidget(showWidget, 1);

	QWidget *contentWidget = new QWidget(this);
	QHBoxLayout *contentLayout = new QHBoxLayout(contentWidget);
	contentLayout->setMargin(0);

	QWidget *descriptionWidget = new QWidget(this);
	QVBoxLayout *descriptionLayout = new QVBoxLayout(descriptionWidget);
	descriptionLayout->setMargin(0);

	QLabel *descriptionLabel = new QLabel(tr("Description:"), this);
	descriptionLabel->setTextFormat(Qt::PlainText);
	descriptionLabel->setFont(font);

	_projectLabel = new QLabel(this);
	_projectLabel->setTextFormat(Qt::PlainText);
	_projectLabel->setWordWrap(true);

	QLabel *extensionLabel = new QLabel(tr("Extensions:"), this);
	extensionLabel->setTextFormat(Qt::PlainText);
	extensionLabel->setFont(font);

	_extensionsLabel = new QLabel(this);
	_extensionsLabel->setTextFormat(Qt::PlainText);
	_extensionsLabel->setWordWrap(true);

	QLabel *templateLabel = new QLabel(tr("Templates:"), this);
	templateLabel->setTextFormat(Qt::PlainText);
	templateLabel->setFont(font);

	QWidget *templateWidget = new QWidget(this);
	QVBoxLayout *templateLayout = new QVBoxLayout(templateWidget);
	templateLayout->setMargin(0);

	QWidget *radioWidget = new QWidget(this);
	_radioLayout = new QVBoxLayout(radioWidget);
	_radioLayout->setMargin(0);

	QRadioButton *radioButton = new QRadioButton(tr("Empty Project/File"), this);
	radioButton->setChecked(true);
	_templateList.append(radioButton);
	_templateList.append(new QRadioButton(this));
	_templates = 2;

	_radioLayout->addWidget(radioButton);
	_radioLayout->addWidget(_templateList.back());

	templateLayout->addWidget(radioWidget);
	templateLayout->addStretch();

	QScrollArea *templateArea = new QScrollArea(this);
	templateArea->setFrameStyle(QFrame::NoFrame);
	templateArea->setWidgetResizable(true);
	templateArea->setWidget(templateWidget);

	descriptionLayout->addWidget(descriptionLabel);
	descriptionLayout->addWidget(_projectLabel);
	descriptionLayout->addWidget(extensionLabel);
	descriptionLayout->addWidget(_extensionsLabel);
	descriptionLayout->addWidget(templateLabel);
	descriptionLayout->addWidget(templateArea);

	contentLayout->addWidget(_projectWidget, 2);
	contentLayout->addWidget(descriptionWidget, 1);

	QWidget *directoryWidget = new QWidget(this);
	QHBoxLayout *directoryLayout = new QHBoxLayout(directoryWidget);
	directoryLayout->setMargin(0);

	QLabel *directoryLabel = new QLabel(tr("Directory:"), this);
	directoryLabel->setTextFormat(Qt::PlainText);

	_dirEdit = new QLineEdit(this);
	_dirEdit->setReadOnly(true);

	QPushButton *browseButton = new QPushButton(tr("Browse"), this);
	connect(browseButton, &QPushButton::pressed,
			this, &ProjectDialog2::getDirectory);

	_defaultCheck = new QCheckBox(tr("Set as default"), this);
	_defaultCheck->setToolTip(tr("If checked, then this directory is "
		"stored and set as the default next time you create a "
		"project/file."));

	if (!_defaultDirectory.isEmpty())
	{
		_dirEdit->setText(_defaultDirectory);
		_defaultCheck->setChecked(true);
	}

	directoryLayout->addWidget(directoryLabel);
	directoryLayout->addWidget(_dirEdit, 2);
	directoryLayout->addWidget(browseButton);
	directoryLayout->addWidget(_defaultCheck);

	QLabel *projectLabel = new QLabel(tr("Name:"), this);
	projectLabel->setTextFormat(Qt::PlainText);

	_projectEdit = new QLineEdit(tr("Project"), this);

	_addCheck = new QCheckBox(tr("Add new directory"), this);
	_addCheck->setToolTip(tr("If checked, an extra directory is that "
		"stores the project, with the same name as the project."));

	QPushButton *chooseButton = new QPushButton(tr("Choose..."), this);
	chooseButton->setDefault(true);
	chooseButton->setFocus();
	connect(chooseButton, &QPushButton::pressed, this,
			&ProjectDialog2::choosePressed);

	QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);
	connect(cancelButton, &QPushButton::pressed, this,
			&ProjectDialog2::cancelPressed);

	QWidget *footerWidget = new QWidget(this);
	QHBoxLayout *footerLayout = new QHBoxLayout(footerWidget);
	footerLayout->setMargin(0);

	footerLayout->addWidget(projectLabel);
	footerLayout->addWidget(_projectEdit);
	footerLayout->addWidget(_addCheck);
	footerLayout->addWidget(chooseButton);
	footerLayout->addWidget(cancelButton);

	layout->addWidget(headerWidget);
	layout->addWidget(contentWidget);
	layout->addWidget(directoryWidget);
	layout->addWidget(footerWidget);

	projectChanged(_projectWidget->currentProject());
}

void NGM::Dialog::ProjectDialog2::listButtonPressed(bool checked)
{
	if (checked)
	{
		_iconViewButton->setChecked(false);
		_projectWidget->setIconMode(false);
	}
	else
	{
		_iconViewButton->setChecked(true);
	}
}

void NGM::Dialog::ProjectDialog2::iconButtonPressed(bool checked)
{
	if (checked)
	{
		_listViewButton->setChecked(false);
		_projectWidget->setIconMode(true);
	}
	else
	{
		_listViewButton->setChecked(true);
	}
}

void NGM::Dialog::ProjectDialog2::displayFiles(bool checked)
{
	if (checked == false)
	{
		if (!_displayProjectsButton->isChecked())
		{
			_projectWidget->setDisplay(Model::Display::Both);
		}
		else
		{
			_projectWidget->setDisplay(Model::Display::Groups);
		}
	}
	else
	{
		if (_displayProjectsButton->isChecked())
		{
			_displayProjectsButton->setChecked(false);
		}
		else
		{
			_projectWidget->setDisplay(Model::Display::Files);
		}
	}
}

void NGM::Dialog::ProjectDialog2::displayProjects(bool checked)
{
	if (checked == false)
	{
		if (!_displayFilesButton->isChecked())
		{
			_projectWidget->setDisplay(Model::Display::Both);
		}
		else
		{
			_projectWidget->setDisplay(Model::Display::Files);
		}
	}
	else
	{
		if (_displayFilesButton->isChecked())
		{
			_displayFilesButton->setChecked(false);
		}
		else
		{
			_projectWidget->setDisplay(Model::Display::Groups);
		}
	}
}

void NGM::Dialog::ProjectDialog2::projectChanged(
		const Resource::Project *project)
{
	_project->data = project;
	_projectLabel->setText(_project->data->description);
	checkTemplates();

	QString projectData = _projectEdit->text();
	projectData = projectData.left(projectData.indexOf(QChar('.')));
	projectData = project->extensions.makefile(projectData);
	_projectEdit->setText(projectData);

	projectData.clear();
	for (QStringList::const_iterator i =
		 _project->data->extensions.extensions.begin();
		 i != _project->data->extensions.extensions.end(); ++i)
	{
		projectData.append(*i);
		projectData.append(QChar(';'));
	}
	_extensionsLabel->setText(projectData);

	if (_project->data->projectType == Resource::Project::FileType)
	{
		_addCheck->setEnabled(false);
		_addCheck->setChecked(false);
	}
	else
	{
		_addCheck->setEnabled(true);
	}
}

void NGM::Dialog::ProjectDialog2::sortChanged(int type)
{
	_projectWidget->setDescending(static_cast<bool>(type));
}

void NGM::Dialog::ProjectDialog2::checkTemplates()
{
	clearTemplates();
#ifdef NGM_PORTABLE
	QDirIterator dirs(
#else
	QDirIterator dirs(QStandardPaths::writableLocation(
						  QStandardPaths::DataLocation) %
#endif
		QStringLiteral("/templates/") % _project->data->name %
		QStringLiteral("/"), QDir::AllDirs | QDir::NoSymLinks |
		QDir::NoDotAndDotDot);
	while (dirs.hasNext())
	{
		dirs.next();
		QDirIterator subdirs(dirs.filePath(), QDir::Files);
		while (subdirs.hasNext())
		{
			subdirs.next();
			if (_project->data->extensions.isfile(subdirs.fileName()))
			{
				addTemplate(dirs.fileName());
			}
		}
	}
}

void NGM::Dialog::ProjectDialog2::addTemplate(const QString &text)
{
	if (_templateList.size() == _templates)
	{
		QRadioButton *radioButton = new QRadioButton(text, this);
		connect(radioButton, &QRadioButton::pressed,
					this, &ProjectDialog2::setCurrentTemplate);
		_radioLayout->addWidget(radioButton);
		_templateList.append(radioButton);
	}
	else
	{
		_templateList[_templates]->setText(text);
		_templateList[_templates]->setVisible(true);
	}
	++_templates;
}

void NGM::Dialog::ProjectDialog2::clearTemplates()
{
	for (QList<QRadioButton*>::iterator i =  ++_templateList.begin();
		 i != _templateList.end(); ++i)
	{
		(*i)->setVisible(false);
	}
	_templateList.front()->setChecked(true);
	_templates = 1;
}

void NGM::Dialog::ProjectDialog2::choosePressed()
{
	if (_projectEdit->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("You must fill in a file"
			"name."), QMessageBox::Cancel);
		return;
	}

	QDir dir(_dirEdit->text());
	if (!dir.exists())
	{
		QMessageBox::warning(this, tr("Warning"), tr("Selected directory is "
			"invalid or does not exist. Please choose another direcory and try "
			"again."), QMessageBox::Cancel);
		return;
	}

	*_location = _dirEdit->text() % QStringLiteral("/");
	if (_addCheck->isChecked())
	{
		*_location += _projectEdit->text().left(
			_projectEdit->text().indexOf('.')) % QStringLiteral("/");
		dir.setPath(*_location);
		if (dir.exists())
		{
			if (QMessageBox::warning(this, tr("Warning"), tr("The project "
				"directory already exists. This might have undesirable "
				"consequences. Continue?"), QMessageBox::Yes,
				QMessageBox::No) == QMessageBox::No)
			{
				return;
			}
		}
	}
	*_location += _projectEdit->text();
	qDebug() << "YOLO1:" << *_location;

	if (!(*_location).count('.') &&
		!_project->data->extensions.isfile(*_location))
	{

		if (QMessageBox::warning(this, tr("Warning"), tr("The selected file "
			"name does not match the selected project's extension. Continue?"),
			QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
		{
			return;
		}
	}
	if (QFile::exists(*_location))
	{
		if (QMessageBox::warning(this, tr("Warning"), tr("The selected file "
			"already exists. Overwrite?"), QMessageBox::Yes, QMessageBox::No) ==
				QMessageBox::No)
		{
			return;
		}
	}
	/*_preferences = (Manager::SettingManager::
		ShowFiles & _displayFilesButton->isChecked()) |
			(Manager::SettingManager::
		ShowGroups & _displayProjectsButton->isChecked()) |
			(Manager::SettingManager::
		IconMode & _iconViewButton->isChecked()) |
			(Manager::SettingManager::
		AddDirectory & _addCheck->isChecked()) |
			(Manager::SettingManager::
		DefaultDirectory & _defaultCheck->isChecked());*/
	accept();
}

void NGM::Dialog::ProjectDialog2::getDirectory()
{
	QString dir = QFileDialog::getExistingDirectory(this,
		tr("Open Directory"), _dirEdit->text(),
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty())
	{
		_dirEdit->setText(dir);
		if (dir == _defaultDirectory)
		{
			_defaultCheck->setChecked(true);
		}
		else
		{
			_defaultCheck->setChecked(false);
		}
	}
}

void NGM::Dialog::ProjectDialog2::setCurrentTemplate()
{
	QRadioButton *button = qobject_cast<QRadioButton*>(sender());
	if (button != nullptr)
	{
		*_template = button->text();
	}
}

void NGM::Dialog::ProjectDialog2::cancelPressed()
{
	_project->data = nullptr;
	_location->clear();
	_template->clear();
	*_preferences = 0;
	reject();
}
