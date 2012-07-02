#include "stdafx.h"
#include "XCodeEditor.h"
//#include <QDebug>
//#include <QColor>
//#include <QFont>
//#include "Qsci/qsciscintilla.h"
//#include "Qsci/qscistyle.h"

#include <build/cmake/include/debug.h>


XCodeEditor::XCodeEditor(QWidget *parent)
: QsciScintilla(parent)
{  
         qDebug() << __FUNCTION__;
}

XCodeEditor::~XCodeEditor(void)
{ 
         qDebug() << __FUNCTION__;
}

