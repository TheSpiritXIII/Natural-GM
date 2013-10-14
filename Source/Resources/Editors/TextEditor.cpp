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
#include <QHBoxLayout>
#include <QFontMetrics>
#include <QTextStream>
#include <QLabel>
#include <QFile>
#include <QDebug>

namespace NGM
{
	namespace Resource
	{
		TextEditor::TextEditor(const Model::ResourceProjectItem * const item, Widget::ResourceTab * const tab) : Editor(item, tab)
		{
			state = CanPaste | CanZoomIn | CanZoomOut;
			textEdit = new QsciScintilla(this);

			blockSignals(true);
			textEdit->blockSignals(true);

			//textEdit->SendScintilla(QsciScintilla::SCI_SETLEXER, QsciScintillaBase::SCLEX_CPP);


			int mask = textEdit->SendScintilla(QsciScintilla::SCI_GETMODEVENTMASK);
				/*textEdit->SendScintilla(QsciScintilla::SCI_SETMODEVENTMASK, mask | QsciScintilla::SC_MOD_CHANGEFOLD);*/

				textEdit->SendScintilla(QsciScintilla::SCI_SETFOLDFLAGS, QsciScintilla::SC_FOLDFLAG_LINEAFTER_CONTRACTED);

				//textEdit->SendScintilla(QsciScintilla::SCI_SETMARGINTYPEN, 2, (long)QsciScintilla::SC_MARGIN_SYMBOL);*/
				textEdit->SendScintilla(QsciScintilla::SCI_SETMARGINMASKN, 2, QsciScintilla::SC_MASK_FOLDERS);
				textEdit->SendScintilla(QsciScintilla::SCI_SETMARGINSENSITIVEN, 2, 1);


			textEdit->SendScintilla(QsciScintilla::SCI_SETMULTIPLESELECTION, 1);
			textEdit->SendScintilla(QsciScintilla::SCI_SETMULTIPASTE, QsciScintilla::SC_MULTIPASTE_EACH);

#ifdef Q_OS_WIN32
			setFont(0, "Consolas", 10, 0, false, false);
			setFont(QsciScintilla::STYLE_LINENUMBER, "Consolas", 10, 0, false, false);
#else
			setFont(0, "Courier", 10, 0, false, false);
			setFont(QsciScintilla::STYLE_LINENUMBER, "Courier", 10, 0, false, false);
#endif
			textEdit->SendScintilla(QsciScintilla::SCI_SETMARGINWIDTHN, 0, 30);
			textEdit->SendScintilla(QsciScintilla::SCI_SETMARGINTYPEN, 0, QsciScintilla::SC_MARGIN_NUMBER);

			textEdit->SendScintilla(QsciScintilla::SCI_STYLESETBACK, QsciScintilla::STYLE_LINENUMBER, QColor("#cccccc"));

			textEdit->SendScintilla(QsciScintilla::SCI_SETCARETLINEVISIBLE, true);
			textEdit->SendScintilla(QsciScintilla::SCI_SETCARETLINEBACK, QColor("#ffe4e4"));

			textEdit->SendScintilla(QsciScintilla::SCI_SETPROPERTY, "fold", "1");
			textEdit->SendScintilla(QsciScintilla::SCI_MARKERDEFINE, QsciScintilla::SC_MARKNUM_FOLDEROPEN, QsciScintillaBase::SC_MARK_BOXMINUS);
			textEdit->SendScintilla(QsciScintilla::SCI_MARKERDEFINE, QsciScintilla::SC_MARKNUM_FOLDER, QsciScintillaBase::SC_MARK_BOXPLUS);
			textEdit->SendScintilla(QsciScintilla::SCI_MARKERDEFINE, QsciScintilla::SC_MARKNUM_FOLDERSUB, QsciScintillaBase::SC_MARK_VLINE);
			textEdit->SendScintilla(QsciScintilla::SCI_MARKERDEFINE, QsciScintilla::SC_MARKNUM_FOLDERTAIL, QsciScintillaBase::SC_MARK_LCORNER);
			textEdit->SendScintilla(QsciScintilla::SCI_MARKERDEFINE, QsciScintilla::SC_MARKNUM_FOLDEREND, QsciScintillaBase::SC_MARK_BOXPLUSCONNECTED);
			textEdit->SendScintilla(QsciScintilla::SCI_MARKERDEFINE, QsciScintilla::SC_MARKNUM_FOLDEROPENMID, QsciScintillaBase::SC_MARK_BOXMINUSCONNECTED);
			textEdit->SendScintilla(QsciScintilla::SCI_MARKERDEFINE, QsciScintilla::SC_MARKNUM_FOLDERMIDTAIL, QsciScintillaBase::SC_MARK_TCORNER);
			textEdit->SendScintilla(QsciScintilla::SCI_SETMARGINWIDTHN, 2, 14);
			//textEdit->setBraceMatching(QsciScintilla::StrictBraceMatch);

			textEdit->SendScintilla(QsciScintilla::SCI_STYLESETBACK, QsciScintilla::STYLE_BRACELIGHT, QColor(200, 200, 255));
			textEdit->SendScintilla(QsciScintilla::SCI_STYLESETFORE, QsciScintilla::STYLE_BRACELIGHT, Qt::black);
			textEdit->SendScintilla(QsciScintilla::SCI_STYLESETBACK, QsciScintilla::STYLE_BRACEBAD, Qt::red);
			textEdit->SendScintilla(QsciScintilla::SCI_STYLESETFORE, QsciScintilla::STYLE_BRACEBAD, Qt::black);
			textEdit->SendScintilla(QsciScintilla::SCI_SETSELBACK, 1, QColor(51, 153, 255));
			textEdit->SendScintilla(QsciScintilla::SCI_SETCARETLINEBACK, QColor(232, 232, 255));

			QHBoxLayout *layout = new QHBoxLayout(this);
			layout->setMargin(0);
			layout->addWidget(textEdit);

			connect(this, &TextEditor::canPaste, [this](const bool &value)
			{
				state ^= value ? CanPaste : 0;
			});
			connect(this, &TextEditor::canSelect, [this](const bool &value)
			{
				state ^= value ? CanSelect : 0;
			});
			connect(textEdit, &QsciScintillaBase::SCN_MODIFIED, [this](int, int type, const char*, int, int, int, int, int, int, int)
			{
				if (type == QsciScintilla::SC_MOD_INSERTTEXT || QsciScintilla::SC_MOD_DELETETEXT)
				{
					qDebug() << "!Modified: " << !textEdit->SendScintilla(QsciScintilla::SCI_GETMODIFY);
					qDebug() << "!State" << !(state & IsModified);
					if (!textEdit->SendScintilla(QsciScintilla::SCI_GETMODIFY) != !(state & IsModified))
					{
						state ^= IsModified;
						emit isModified(textEdit->SendScintilla(QsciScintilla::SCI_CANUNDO));
					}
					if (!textEdit->SendScintilla(QsciScintilla::SCI_CANUNDO) != !(state & CanUndo))
					{
						state ^= CanUndo;
						emit canUndo(textEdit->SendScintilla(QsciScintilla::SCI_CANUNDO));
					}
					if (!textEdit->SendScintilla(QsciScintilla::SCI_CANREDO) != !(state & CanRedo))
					{
						state ^= CanRedo;
						emit canRedo(textEdit->SendScintilla(QsciScintilla::SCI_CANUNDO));
					}
					lengthLabel->setText("Len: "+QString::number(textEdit->SendScintilla(QsciScintilla::SCI_GETLENGTH)));
					updateLineLength();
				}
			});
			connect(textEdit, &QsciScintillaBase::SCN_UPDATEUI, [this]()
			{
				int position = textEdit->SendScintilla(QsciScintilla::SCI_GETCURRENTPOS);
				if (lastPosition != position)
				{
					lastPosition = position;
					const int line = textEdit->SendScintilla(QsciScintilla::SCI_LINEFROMPOSITION, lastPosition);
					const int index = textEdit->SendScintilla(QsciScintilla::SCI_GETCOLUMN, lastPosition);
					positionLabel->setText("Ln: "+QString::number(line)+"  Col: "+QString::number(index));
				}
			});
			connect(textEdit, &QsciScintillaBase::QSCN_SELCHANGED, [this](const bool& value)
			{
				// NOTE: QScintilla keeps emitting this signal while holding mouse.
				if (!value != !(state & CanCopy))
				{
					state ^= CanCopy;
					emit canCopy(value);
				}
				if (value)
				{
					if (!textEdit->SendScintilla(QsciScintilla::SCI_SELECTIONISRECTANGLE))
					{
						const int selStart = textEdit->SendScintilla(QsciScintilla::SCI_GETSELECTIONSTART);
						const int selEnd = textEdit->SendScintilla(QsciScintilla::SCI_GETSELECTIONEND);
						const int count = selEnd - selStart;
						if (count != 0)
						{
							const int line = 1+textEdit->SendScintilla(QsciScintilla::SCI_LINEFROMPOSITION, selEnd)-
								textEdit->SendScintilla(QsciScintilla::SCI_LINEFROMPOSITION, selStart);
							selectLabel->setText("Sel: "+QString::number(count)+":"+QString::number(line));
						}
					}
				}
				else
				{
					selectLabel->setText("Sel: N/A");
				}
			});

			lengthLabel = new QLabel(this);
			positionLabel = new QLabel("Ln: 0  Col: 0", this);
			selectLabel = new QLabel("Sel: N/A", this);
			typeComboBox = new QComboBox(this);
			typeComboBox->addItem("Plain Text");
		}

		TextEditor::~TextEditor()
		{

		}

		Editor *TextEditor::create(const Model::ResourceProjectItem * const item, Widget::ResourceTab * const tab)
		{
			return new TextEditor(item, tab);
		}

		void TextEditor::cut()
		{
			textEdit->SendScintilla(QsciScintilla::SCI_CUT);
		}

		void TextEditor::copy()
		{
			textEdit->SendScintilla(QsciScintilla::SCI_COPY);
		}

		void TextEditor::paste()
		{
			textEdit->SendScintilla(QsciScintilla::SCI_PASTE);
		}

		void TextEditor::undo()
		{
			textEdit->SendScintilla(QsciScintilla::SCI_UNDO);
		}

		void TextEditor::redo()
		{
			textEdit->SendScintilla(QsciScintilla::SCI_REDO);
		}

		void TextEditor::zoomIn()
		{
			textEdit->SendScintilla(QsciScintilla::SCI_ZOOMIN);
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

		void TextEditor::zoomOut()
		{
			textEdit->SendScintilla(QsciScintilla::SCI_ZOOMOUT);
			int smallest = -textEdit->SendScintilla(QsciScintilla::SCI_STYLEGETSIZE, 0)+2;
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

		void TextEditor::zoom()
		{
			textEdit->SendScintilla(QsciScintilla::SCI_SETZOOM, 0);
			if (~state & CanZoomIn)
			{
				emit canZoomIn(true);
			}
			if (~state & CanZoomOut)
			{
				emit canZoomOut(true);
			}
		}

		void TextEditor::search(uint8_t settings, QString data) const
		{

		}

		void TextEditor::status(Manager::WindowManager * const windowManager) const
		{
			windowManager->addStatusWidget(typeComboBox, 2);
			windowManager->addStatusWidget(positionLabel, 1);
			windowManager->addStatusWidget(selectLabel, 1);
			windowManager->addStatusWidget(lengthLabel, 1);
			typeComboBox->show();
			positionLabel->show();
			selectLabel->show();
			lengthLabel->show();
		}

		Variant TextEditor::property(const char *property) const
		{
			if (strcmp(property, "text") == 0)
			{
				return Variant(reinterpret_cast<char*>(textEdit->SendScintilla(QsciScintilla::SCI_GETCHARACTERPOINTER)));
			}
#ifdef NGM_DEBUG
			qDebug() << "Widget: Unknown property '" << property << "'";
#endif
			return Variant();
		}

		void TextEditor::setProperty(const char *property, Variant &value)
		{
			if (strcmp(property, "text") == 0)
			{
				textEdit->SendScintilla(QsciScintilla::SCI_SETTEXT, 0, reinterpret_cast<long>(value.charPtr()));
			}
		}

		QStringList TextEditor::getPropertyList() const
		{
			return QStringList("text");
		}

		void TextEditor::initialize()
		{
			blockSignals(false);
			textEdit->blockSignals(false);
			textEdit->SendScintilla(QsciScintilla::SCI_SETSAVEPOINT);
			textEdit->SendScintilla(QsciScintilla::SCI_EMPTYUNDOBUFFER);
			lengthLabel->setText("Len: "+QString::number(textEdit->SendScintilla(QsciScintilla::SCI_GETLENGTH)));
			updateLineLength();
			textEdit->installEventFilter(this);
		}

		Editor *TextEditor::clone(Widget::ResourceTab *tab) const
		{
			TextEditor *editor = new TextEditor(projectItem, tab);
			editor->textEdit->SendScintilla(QsciScintilla::SCI_SETDOCPOINTER, textEdit->SendScintilla(QsciScintilla::SCI_GETDOCPOINTER));
			editor->initialize();
			return editor;
		}

		void TextEditor::saveSession(const QString &filename) const
		{
			QFile file(filename);
			file.open(QFile::WriteOnly);
			QTextStream stream(&file);
			stream << textEdit->SendScintilla(QsciScintilla::SCI_GETFIRSTVISIBLELINE);
			long position = textEdit->SendScintilla(QsciScintilla::SCI_CONTRACTEDFOLDNEXT, 0);
			while (position != -1)
			{
				stream << position;
				position = textEdit->SendScintilla(QsciScintilla::SCI_CONTRACTEDFOLDNEXT, 0);
			}
			file.close();
		}

		void TextEditor::loadSession(const QString &filename)
		{
			QFile file(filename);
			file.open(QFile::ReadOnly);
			QTextStream stream(&file);
			long value;
			stream >> value;
			textEdit->SendScintilla(QsciScintilla::SCI_SETFIRSTVISIBLELINE, value);
			while (!stream.atEnd())
			{
				stream >> value;
				textEdit->SendScintilla(QsciScintilla::SCI_TOGGLEFOLD, value);
			}
			file.close();
		}

		void TextEditor::saved()
		{
			textEdit->SendScintilla(QsciScintilla::SCI_SETSAVEPOINT);
			state &= ~IsModified;
		}

		void TextEditor::updateLineLength()
		{
			int lines = textEdit->SendScintilla(QsciScintilla::SCI_GETLINECOUNT);
			if (lines > 9999)
			{
				textEdit->SendScintilla(QsciScintilla::SCI_SETMARGINWIDTHN, 0, textEdit->SendScintilla(QsciScintilla::SCI_STYLEGETSIZE, 0)*6);
			}
			else if (lines > 999)
			{
				textEdit->SendScintilla(QsciScintilla::SCI_SETMARGINWIDTHN, 0, textEdit->SendScintilla(QsciScintilla::SCI_STYLEGETSIZE, 0)*5);
			}
			else if (lines > 99)
			{
				textEdit->SendScintilla(QsciScintilla::SCI_SETMARGINWIDTHN, 0, textEdit->SendScintilla(QsciScintilla::SCI_STYLEGETSIZE, 0)*4);
			}
			else
			{
				textEdit->SendScintilla(QsciScintilla::SCI_SETMARGINWIDTHN, 0, textEdit->SendScintilla(QsciScintilla::SCI_STYLEGETSIZE, 0)*3);
			}
		}
	}
}
