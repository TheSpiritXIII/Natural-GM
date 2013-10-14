#include <QVBoxLayout>
#include <QStackedLayout>
#include <QGridLayout>
#include <QToolBar>
#include <QDialog>

namespace NGM
{
	namespace Widget
	{
		class PreferencesDialog : public QDialog
		{
		public:
		
			PreferencesDialog(QWidget *parent = 0)
			{
				QVBoxLayout *layout = new QHBoxLayout(this);
				
				QToolBar *toolBar = new QToolBar(this);
				
				QWidget *content = new QWidget(this);
				stack = new QStackedLayout(content);
				
				QWidget *generalWidget = new QWidget(this);
				QGridLayout *general = new QGridLayout(this);
				
				stack->addWidget(general);
				stack->addWidget(new QWidget(this));
				
				layout->addWidget(toolBar);
				layout->addWidget(content);
			}
			
		private:
			
			enum Content
			{
				Editors			=	0x01,
				Compilers	=	0x02
			}
			uint8_t loaded;
			QStackedLayout *stack;
			
			void loadEditorSettings()
			{
				stack->setCurrentIndex(0)
				if (!(loaded & Editors))
				{
					loaded &= Editors;
				}
			}
			void loadCompilerSettings();
		}
	}
}