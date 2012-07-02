#include "stdafx.h"
#include "CodeEditor.h"
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

//#include <QFont>
//#include "Qsci/qsciscintilla.h"
//#include "Qsci/qscistyle.h"

#include <build/cmake/include/debug.h>


CodeEditor::CodeEditor(QWidget *parent)
: QsciScintilla(parent)
{  
    qDebug() << __FUNCTION__;
}

CodeEditor::~CodeEditor(void)
{ 
    qDebug() << __FUNCTION__;
}

void
CodeEditor::paintEvent(QPaintEvent *e)
{ 
    //Surface *sw = Surface::Allocate();
    /*QPaintEngine * paintEngine = this->paintEngine();
    if(paintEngine)
    {
    QPainter *painter = paintEngine->painter();

    //QPainter painter(this);
    painter->setPen(Qt::blue);
    painter->setFont(QFont("Arial", 30));
    painter->drawText(rect(), Qt::AlignCenter, "Qt");
    }*/

    QsciScintilla::paintEvent(e);

    /*QPainter painter(this->viewport());
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(), Qt::AlignCenter, "Qt");*/

}
