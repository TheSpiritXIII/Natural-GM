/**
 *  @file TextEditor.cpp
 *	@section License
 *
 *      Copyright (C) 2013 Daniel Hrabovcak
 *
 *      This file is a part of the Natural GM IDE. MIT License.
 *
 *      Permission is hereby granted, free of charge, to any person obtaining a copy
 *		of this software and associated documentation files (the "Software"), to deal
 *		in the Software without restriction, including without limitation the rights
 *		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *		copies of the Software, and to permit persons to whom the Software is
 *		furnished to do so, subject to the following conditions:
 *
 *		The above copyright notice and this permission notice shall be included in
 *		all copies or substantial portions of the Software.
 *
 *		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *		THE SOFTWARE.
**/
#include "TextEditor.hpp"
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
#include <QFontMetrics>

namespace NGM
{
	namespace Resource
	{
		TextEditor::TextEditor(NGM::Widget::ResourceTab *parent) : Editor(parent)
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
			connect(this, &TextEditor::canPaste, [this](const bool &value)
			{
				state ^= value ? CanPaste : 0;
			});
			connect(this, &TextEditor::canUndo, [this](const bool &)
			{
				state ^= CanUndo;
			});
			connect(this, &TextEditor::canSelect, [this](const bool &value)
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
			connect(textEdit, &QsciScintilla::linesChanged, this, &TextEditor::updateLineLength);
		}

		TextEditor::~TextEditor()
		{

		}

		void TextEditor::cutRequest()
		{
			textEdit->cut();
		}

		void TextEditor::copyRequest()
		{
			textEdit->copy();
		}

		void TextEditor::pasteRequest()
		{
			textEdit->paste();
		}

		void TextEditor::undoRequest()
		{
			textEdit->undo();
		}

		void TextEditor::redoRequest()
		{
			textEdit->redo();
		}

		void TextEditor::zoomInRequest()
		{
			textEdit->zoomIn();
			if (textEdit->SendScintilla(QsciScintilla::SCI_GETZOOM, 0) == 20)
			{
				state &= ~CanZoomIn;
				emit canZoomIn(false);
			}
			if (~state & CanZoomOut)
			{
				emit canZoomOut(true);
			}
		}

		void TextEditor::zoomOutRequest()
		{
			textEdit->zoomOut();
			int smallest = -textEdit->font().pointSize()+2;
			int current = textEdit->SendScintilla(QsciScintilla::SCI_GETZOOM, 0);
			if (smallest > -10 ? current == smallest : current)
			{
				state &= ~CanZoomOut;
				emit canZoomOut(false);
			}
			if (~state & CanZoomIn)
			{
				state &= CanZoomIn;
				emit canZoomIn(true);
			}
		}

		void TextEditor::zoomRequest()
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

		void TextEditor::searchRequest(uint8_t settings, QByteArray *data)
		{

		}

		void TextEditor::statusRequest(QLabel *label, QProgressBar *progress)
		{
			progress->setVisible(false);
			label->setVisible(true);
			label->setText("Hello World.");
		}

		QVariant TextEditor::property(const char *property) const
		{
			if (strcmp(property, "text") == 0)
			{
				return textEdit->text();
			}
#ifdef NGM_DEBUG
			qDebug() << "Widget: Unknown property '" << property << "'";
#endif
			return QVariant();
		}

		void TextEditor::setProperty(const char *property, QVariant value)
		{
			if (strcmp(property, "text") == 0)
			{
				textEdit->setText(value.toString());
			}
		}

		QStringList TextEditor::getPropertyList()
		{
			return QStringList("text");
		}

		void TextEditor::block(const bool &blocked)
		{
			blockSignals(blocked);
			textEdit->blockSignals(blocked);
			updateLineLength();
		}

		void TextEditor::isSaved()
		{
			textEdit->setModified(false);
			state &= ~IsModified;
		}

		void TextEditor::updateLineLength()
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
		}
	}
}
