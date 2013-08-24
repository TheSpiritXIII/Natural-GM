#include "TextWidget.hpp"
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
#include <QFontMetrics>

namespace NGM
{
	namespace Resource
	{
		TextWidget::TextWidget(NGM::Widget::ResourceTab *parent) : Widget(parent)
		{
			state = CanPaste | CanZoomIn | CanZoomOut;

			textEdit = new QsciScintilla(this);

#ifdef Q_OS_WIN32
			QFont font("Consolas", 10);
#else
			QFont font("Courier", 10);
#endif
			textEdit->setFont(font);
			textEdit->setMarginsFont(font);

			textEdit->setMarginWidth(0, QFontMetrics(font).width("__") + 8);
			textEdit->setMarginLineNumbers(0, true);
			textEdit->setMarginsBackgroundColor(QColor("#cccccc"));

			textEdit->setCaretLineVisible(true);
			textEdit->setCaretLineBackgroundColor(QColor("#ffe4e4"));

			textEdit->setFolding(QsciScintilla::BoxedTreeFoldStyle);
			textEdit->setBraceMatching(QsciScintilla::StrictBraceMatch);
			textEdit->setModified(false);

			textEdit->setMatchedBraceBackgroundColor(QColor(200, 200, 255));
			textEdit->setMatchedBraceForegroundColor(Qt::black);
			textEdit->setUnmatchedBraceBackgroundColor(Qt::red);
			textEdit->setUnmatchedBraceForegroundColor(Qt::black);
			textEdit->setSelectionBackgroundColor(QColor(51, 153, 255));
			textEdit->setCaretLineBackgroundColor(QColor(232, 232, 255));

			QHBoxLayout *layout = new QHBoxLayout(this);
			layout->setMargin(0);
			layout->addWidget(textEdit);

			connect(textEdit, &QsciScintilla::copyAvailable, [this](const bool &value)
			{
				state ^= value ? CanCopy : 0;
				emit canCopy(value);
			});
			connect(this, &TextWidget::canPaste, [this](const bool &value)
			{
				state ^= value ? CanPaste : 0;
			});
			connect(this, &TextWidget::canUndo, [this](const bool &)
			{
				state ^= CanUndo;
			});
			connect(this, &TextWidget::canSelect, [this](const bool &value)
			{
				state ^= value ? CanSelect : 0;
			});
			connect(textEdit, &QsciScintilla::modificationChanged, [this](const bool &value)
			{
				qDebug() << state;
				qDebug() << "Mofied?" << value << ":" << static_cast<bool>(state & IsModified);
				if (value != static_cast<bool>(state & IsModified))
				{
					state ^= IsModified;
					emit isModified(value);
				}
				if (textEdit->isUndoAvailable() != static_cast<bool>(state & CanUndo))
				{
					emit canUndo(textEdit->isUndoAvailable());
				}
				if (textEdit->isRedoAvailable() != static_cast<bool>(state & CanRedo))
				{
					emit canRedo(textEdit->isRedoAvailable());
				}
			});
			connect(textEdit, &QsciScintilla::linesChanged, [this]()
			{
				if (this->textEdit->lines() > 9999)
				{
					this->textEdit->setMarginWidth(0, QFontMetrics(this->textEdit->font()).width("_____")+8);
				}
				else if (this->textEdit->lines() > 999)
				{
					this->textEdit->setMarginWidth(0, QFontMetrics(this->textEdit->font()).width("____")+8);
				}
				else if (this->textEdit->lines() > 99)
				{
					this->textEdit->setMarginWidth(0, QFontMetrics(this->textEdit->font()).width("___")+8);
				}
				else
				{
					this->textEdit->setMarginWidth(0, QFontMetrics(this->textEdit->font()).width("__")+8);
				}
			});
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

		void TextWidget::zoomInRequest()
		{
			textEdit->zoomIn();
			if (textEdit->font().pointSize() == 8)
			{
				emit canZoomIn(false);
			}
			if (~state & CanZoomOut)
			{
				emit canZoomOut(true);
			}
		}

		void TextWidget::zoomOutRequest()
		{
			textEdit->zoomOut();
			if (textEdit->font().pointSize() == 72)
			{
				emit canZoomOut(false);
			}
			if (~state & CanZoomIn)
			{
				emit canZoomIn(true);
			}
		}

		void TextWidget::zoomRequest()
		{
			textEdit->zoomTo(0);
			if (~state & CanZoomIn)
			{
				emit canZoomIn(true);
			}
			if (~state & CanZoomOut)
			{
				emit canZoomOut(true);
			}
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
				return textEdit->text();
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
				textEdit->setText(value.toString());
			}
		}

		QStringList TextWidget::getPropertyList()
		{
			return QStringList("text");
		}

		void TextWidget::block(const bool &blocked)
		{
			blockSignals(blocked);
			textEdit->blockSignals(blocked);
		}

		void TextWidget::isSaved()
		{
			textEdit->setModified(false);
			state &= ~IsModified;
		}
	}
}
