#include "ResourceDialog.hpp"

namespace NGM
{
	namespace Widget
	{
		ResourceDialog::ResourceDialog(ResourceTab *tab, bool clone)
		{
			move(tab, clone);
		}

		void ResourceDialog::move(ResourceTab *tab, bool clone)
		{
			QWidget *widget = tab->currentWidget();
			tab->removeTab(tab->currentIndex());
			splitter->addWidget(widget);
		}
	}
}
