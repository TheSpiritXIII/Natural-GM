#include "TextWidget.hpp"
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
#include <QFontMetrics>

namespace NGM
{
	namespace Resource
	{
		TextWidget::TextWidget(QWidget *parent) : Widget(parent), state(0)
		{
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
			connect(this, &TextWidget::canUndo, [this](const bool &value)
			{
				state ^= value ? CanUndo : 0;
			});
			connect(this, &TextWidget::canRedo, [this](const bool &value)
			{
				state ^= value ? CanRedo : 0;
			});
			connect(this, &TextWidget::canSelect, [this](const bool &value)
			{
				state ^= value ? CanSelect : 0;
			});
			connect(textEdit, &QsciScintilla::modificationChanged, [this](const bool &value)
			{
				state ^= value ? IsModified : 0;
				emit canUndo(textEdit->isUndoAvailable());
				emit canRedo(textEdit->isRedoAvailable());
				emit isModified(value);
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

			emit canPaste(true);
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

		uint8_t TextWidget::getState()
		{
			return state;//settings	& (textEdit->canPaste() ? 0 : Settings::CanPaste);
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
	}
}
