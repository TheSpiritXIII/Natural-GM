#include "TextWidget.hpp"
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>

namespace NGM
{
	namespace Resource
	{
		TextWidget::TextWidget(QWidget *parent) : Widget(parent)
		{
			textEdit = new QTextEdit(this);
			QHBoxLayout *layout = new QHBoxLayout(this);
			layout->setMargin(0);
			layout->addWidget(textEdit);
			textEdit->setAcceptRichText(false);
			textEdit->setFrameStyle(QFrame::NoFrame);
			this->connect(textEdit, &QTextEdit::textChanged, this, &TextWidget::requestStatusUpdate);
		}

		TextWidget::~TextWidget()
		{

		}

		void TextWidget::cutRequest()
		{
			textEdit->cut();
		}

		void TextWidget::copyRequest()
		{
			textEdit->copy();
		}

		void TextWidget::pasteRequest()
		{
			textEdit->paste();
		}

		void TextWidget::undoRequest()
		{
			textEdit->undo();
		}

		void TextWidget::redoRequest()
		{
			textEdit->redo();
		}

		uint8_t TextWidget::getSettings()
		{
			return 0;//settings	& (textEdit->canPaste() ? 0 : Settings::CanPaste);
		}

		void TextWidget::searchRequest(uint8_t settings, QByteArray *data)
		{

		}

		void TextWidget::statusRequest(QLabel *label, QProgressBar *progress)
		{
			progress->setVisible(false);
			label->setVisible(true);
			label->setText("Hello World.");
		}

		QVariant TextWidget::property(const char *property)
		{
			qDebug() << "Length: " << strlen(property);
			qDebug() << "Actual: " << strlen("text");
			if (strcmp(property, "text") == 0)
			{
				return textEdit->toPlainText();
			}
#ifdef NGM_DEBUG
			qDebug() << "Widget: Unknown property '" << property << "'";
#endif
			return QVariant();
		}

		void TextWidget::setProperty(const char *property, QVariant value)
		{
			qDebug() << "Length: " << strlen(property);
			qDebug() << "Actual: " << strlen("text");
			if (strcmp(property, "text") == 0)
			{
				//qDebug() << "True!" <<
				textEdit->setPlainText(value.toString());
			}
		}

		QStringList TextWidget::getPropertyList()
		{
			return QStringList("text");
		}
	}
}
