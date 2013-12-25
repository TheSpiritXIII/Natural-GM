#include "ResourceDialog.hpp"

namespace NGM
{
	namespace Widget
	{
		ResourceDialog::ResourceDialog(const int &index, ResourceSplitter *splitter,
			const uint8_t settings, Manager::WindowManager *windowManager, QWidget *parent) :
			QDialog(parent)
		{
			_splitter = new ResourceSplitter(windowManager, this);
			splitter->movePage(index, _splitter);
		}
	}
}
