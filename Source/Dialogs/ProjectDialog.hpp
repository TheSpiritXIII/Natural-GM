/*#pragma once
#ifndef _NGM_PROJECTDIALOG__HPP
#define _NGM_PROJECTDIALOG__HPP
#include "Project.h"
#include <QLabel>
#include <QDialog>
#include <QLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QListWidget>
#include <QTreeWidget>
#include <QPushButton>
#include <QTreeWidgetItem>
#include "Settings.h"
#include "BasicModel.h"
#include <vector>

namespace NGM
{
	namespace Dialogs
	{
		class ProjectDialog : public QDialog
		{
			Q_OBJECT

		public:

			ProjectDialog(std::vector<Projects*> &projects, unsigned int amount, Settings *settings, Model::BasicModel *model, QWidget *parent = 0);
			~ProjectDialog();

		private slots:
			void cancel();
			void browse();
			void choose();
			void updateList(QTreeWidgetItem *current, QTreeWidgetItem *previous);
			void updateDescription(int row);

		private:
			Settings *settings;
			unsigned char amount, current;
			QLabel *description;
			QListWidget *projectList;
			QTreeWidget *projectTree;
			QLineEdit *directoryEdit, *projectEdit;
			NGM::Resource::Project projects[64];
			QCheckBox *dirUseCheck, *dirAddCheck, *dirDefaultCheck;
			Model::BasicModel *model;
		};
	}
}

#endif // _NGM_NGMPROJECTDIALOG__HPP*/
