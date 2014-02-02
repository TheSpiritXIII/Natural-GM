/**
 *  @file ResourceItemModel.hpp
 *  @section License
 *
 *      Copyright (C) 2013-2014 Daniel Hrabovcak
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
#ifndef NGM__RESOURCEITEMMODEL__HPP
#define NGM__RESOURCEITEMMODEL__HPP
#include <QAbstractItemModel>
#include "ResourceProjectItem.hpp"

// TODO: File URL support for models and framework for projects.
// TODO: Add icon manager support (this will remove deprecated items).
// TODO: Add fix project deprecated settings.

namespace NGM
{
	namespace Manager
	{
		class ActionManager;
	}
	namespace Model
	{
		/**************************************************//*!
		*	@brief	A Qt based model that stores resources.
		******************************************************/
		class ResourceItemModel : public QAbstractItemModel
		{
			Q_OBJECT

		public:

			/// DEPRECATED
			ResourceItemModel(const Manager::ActionManager *actionManager,
							  QObject *parent = 0,
							  QString headerText = QString());

			/*
			ResourceItemModel(const Manager::IconManager *iconManager,
							  const QString &headerText = QString(),
							  QObject *parent = 0);
			*/

			/**************************************************//*!
			*	@brief	Destroys the root item and its children.
			******************************************************/
			~ResourceItemModel();

			/**************************************************//*!
			*	@brief	Returns whether or not items are being
			*			sorted internally within the model.
			******************************************************/
			inline bool sort() const
			{
				return _sort;
			}

			/**************************************************//*!
			*	@brief	Sets whether or not to sort items.
			*	@see	sort()
			******************************************************/
			void setSort(bool yes);

			/**************************************************//*!
			*	@brief	Returns the data at the indicated index
			*			depending on the indicated role. Only
			*			the display and decoration roles are
			*			supported.
			******************************************************/
			QVariant data(const QModelIndex &index, int role) const;

			/**************************************************//*!
			*	@brief	Returns the item flags. By default, most
			*			items are selectable, except the root.
			*			Flags change relative to the index's
			*			project settings.
			******************************************************/
			Qt::ItemFlags flags(const QModelIndex &index) const;

			/**************************************************//*!
			*	@brief	Returns the header data. Only the display
			*			role is suppored and returns the root's
			*			display text. Orientation does not
			*			matter.
			******************************************************/
			QVariant headerData(Qt::Orientation,
								int role = Qt::DisplayRole) const;

			/**************************************************//*!
			*	@brief	Returns the item index at the indicated
			*			row position and parent.
			******************************************************/
			QModelIndex index(int row, int, const QModelIndex &parent =
					QModelIndex()) const;

			/**************************************************//*!
			*	@brief	Returns the parent at the indicated
			*			index.
			******************************************************/
			QModelIndex parent(const QModelIndex &index) const;

			/**************************************************//*!
			*	@brief	Sets the item data. Only the EditRole can
			*			be modified.
			******************************************************/
			bool setData(const QModelIndex & index, const QVariant & value,
						 int role = Qt::EditRole);

			/**************************************************//*!
			*	@brief	Returns the child count of the indicated
			*			parent.
			******************************************************/
			int rowCount(const QModelIndex &parent = QModelIndex()) const;

			/**************************************************//*!
			*	@brief	Always returns 1 (required for subclass).
			******************************************************/
			int columnCount(const QModelIndex &parent = QModelIndex()) const;

			/**************************************************//*!
			*	@brief	Returns support for Copy and Move.
			******************************************************/
			Qt::DropActions supportedDragActions() const;

			/**************************************************//*!
			*	@brief	Returns support for Copy and Move.
			******************************************************/
			Qt::DropActions supportedDropActions() const;

			/**************************************************//*!
			*	@brief	Returns support for internal model
			*			move.
			******************************************************/
			QStringList mimeTypes() const;

			/**************************************************//*!
			*	@brief	Creates a mime data for both internal
			*			moves and file URLs copy.
			******************************************************/
			QMimeData *mimeData(const QModelIndexList &indexes) const;

			/**************************************************//*!
			*	@brief	Either moves an internal item, or
			*			requests a project to copy a file.
			******************************************************/
			bool dropMimeData(const QMimeData * data, Qt::DropAction action,
							  int row, int column, const QModelIndex & parent);

			/**************************************************//*!
			*	@brief	Inserts an item into the root.
			*	@see	ResourceGroupItem::insert()
			******************************************************/
			inline void insert(ResourceProjectItem *item)
			{
				_root->insert(item);
			}

		protected:

			friend class ResourceGroupItem;

			inline void beginInsert(QModelIndex parent, int first, int last)
			{
				beginInsertRows(parent, first, last);
			}

			inline void endInsert()
			{
				endInsertRows();
			}

			inline void beginRemove(QModelIndex parent, int first, int last)
			{
				beginRemoveRows(parent, first, last);
			}

			inline void endRemove()
			{
				endRemoveRows();
			}

			inline void beginMove(const QModelIndex &sourceParent,
				int sourceFirst, int sourceLast,
				const QModelIndex &destinationParent, int destinationChild)
			{
				beginMoveRows(sourceParent, sourceFirst, sourceLast,
							  destinationParent, destinationChild);
			}

			inline void endMove()
			{
				endMoveRows();
			}

		private:

			/// DEPRECATED
			const Manager::ActionManager *actionManager;

			// const Manager::IconManager *iconManager;

			/**************************************************//*!
			*	@brief	Stores the last internally created mime,
			*			for verifying drops.
			******************************************************/
			static QMimeData *internalMime;

			/**************************************************//*!
			*	@brief	The internal root item.
			******************************************************/
			NGM::Model::ResourceGroupItem *_root;

			/**************************************************//*!
			*	@brief	Decides whether or not to sort items as
			*			they are inserted.
			******************************************************/
			bool _sort;
		};
	}
}


#endif // NGM__RESOURCEITEMMODEL__HPP
