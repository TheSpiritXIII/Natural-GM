/**
 *  @file ResourceDialog.hpp
 *	@section License
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
#pragma once
#ifndef _NGM_RESOURCEDIALOG__HPP
#define _NGM_RESOURCEDIALOG__HPP
#include <QDialog>
#include "ResourceSplitter.hpp"

namespace NGM
{
	namespace Model
	{
		class ResourceBaseItem;
	}
	namespace Widget
	{
		class ResourceTab;

		/**************************************************//*!
		*	@brief	Displays resources in a single dialog,
		*			without toolbars or menubars.
		******************************************************/
		class ResourceDialog : public QDialog
		{
			Q_OBJECT

		public:

			/**************************************************//*!
			*	@brief	Creates a dialog by opening the indicated
			*			item.
			******************************************************/
			//ResourcDialog(Model::ResourceBaseItem *item);

			/**************************************************//*!
			*	@brief	Creates a dialog by moving the current tab
			*			of the indicated ResourceTab to here.
			******************************************************/
			ResourceDialog(ResourceTab *tab, bool clone);

			/**************************************************//*!
			*	@brief	Moves the current tab of the indicated
			*			ResourceTab to this dialog.
			******************************************************/
			void move(ResourceTab *tab, bool clone);

			/**************************************************//*!
			*	@brief	Opens the indicated item.
			******************************************************/
			//open(Model::ResourceBaseItem *item);

		private:

			/**************************************************//*!
			*	@brief	Contains all opened resources.
			******************************************************/
			ResourceSplitter *splitter;
		};
	}
}

#endif // _NGM_RESOURCEDIALOG__HPP
