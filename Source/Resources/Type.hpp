#pragma once
#ifndef _NGM_TYPE__HPP
#define _NGM_TYPE__HPP
#include <QString>
#include <QAction>
#include <string>

namespace NGM
{
	namespace Widget
	{
		class ResourceTab;
	}
	namespace Resource
	{
		class Widget;
		class Resource;

		class Type
		{
		public:

			/*! The human readable name. This is used in menus. */
			const QString name;

			/*! The plural name. This is used in tabs and groups. */
			const QString plural;

			/*! An icon. It is loaded by the filename "name". */
			QIcon icon;

			/*! @return The Qt based action for creating this type. */
			QAction *getAction() { return action; }

			/*! @return An usable widget for this type. */
			virtual Widget *widget(NGM::Widget::ResourceTab *parent = 0)
			{
				Q_UNUSED(parent)
				return NULL;
			}

			/*! Sets up the constant data. */
			Type(QString name, QString plural) : name(name), plural(plural) {}

		private:

			/*! An action for toolbar commands. */
			QAction *action;

		};
	}
}

#endif // _NGM_Type__HPP
