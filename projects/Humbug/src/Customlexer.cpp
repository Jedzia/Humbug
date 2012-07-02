#include "stdafx.h"
#include <QDebug>
#include <QColor>
#include <QFont>
#include "Qsci/qsciscintilla.h"
#include "Qsci/qscistyle.h"
#include "Customlexer.h"

#include <build/cmake/include/debug.h>


Customlexer::Customlexer(QObject *parent)
: QsciLexerCustom(parent)
{  
         qDebug() << __FUNCTION__;
}

Customlexer::~Customlexer(void)
{ 
         qDebug() << __FUNCTION__;
}

const char* Customlexer::language() const
{
    return "AsciiDoc";
}

QString Customlexer::description(int style) const
{
    switch(style){
        case Default:
            return "Default";
        case Comment:
            return "Comment";
    }

    return QString();
}


void Customlexer::styleText(int start, int end)
{
    QString source;
    int i;

    qDebug() << __FUNCTION__
        << "start =" << start
        << " end =" << end;

    if (!editor())
        return;

    //editor()->SendScintilla(QsciScintilla::SCI_SETBUFFEREDDRAW, 0);

    //if ((end - start) < 1)
    //    return;

    int pos = 0;
    int dlen = editor()->SendScintilla(QsciScintilla::SCI_GETLENGTH);
    int caret = editor()->SendScintilla(QsciScintilla::SCI_GETCURRENTPOS);
    int clen = caret - start;
    char *orig_context = new char[clen + 1];

    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, caret, orig_context);

    source = QString(orig_context);
    delete []orig_context;

    //qDebug() << "source =" << source;
    QStringList list = source.split("\n");
    for (i = 0; i < list.size(); i++) {
        QString line = list.at(i);
        int len = line.size();
        int style;
        //qDebug() << "line =" << line;
         
        if (line.startsWith("//")) {
            style = Comment;
        } else {
            style = Default;
        }
        qDebug() << "Styling " << len << "bytes " << description(style);
        
            editor()->SendScintilla(QsciScintilla::SCI_AUTOCSETCHOOSESINGLE, style);
    //editor()->SendScintilla(QsciScintilla::SCI_AUTOCSETSEPARATOR, acSeparator);

        //setFont(defaultFont(style));
        //setStyling(len, getStyle(style));
        // newline character was consumed in split so...
        //setStyling(1, getStyle(Default));

        //setStyling(0, getStyle(Comment));
    }
    return;

    /*startStyling(start, 0x1f);
    QStringList list = source.split("\n");
    for (i = 0; i < list.size(); i++) {
        QString line = list.at(i);
        int len = line.size();
        int style;
        qDebug() << "line =" << line;

        if (line.startsWith("//")) {
            style = Comment;
        } else {
            style = Default;
        }
        qDebug() << "Styling " << len << "bytes " << description(style);
        setStyling(len, getStyle(style));
        // newline character was consumed in split so...
        setStyling(1, getStyle(Default));
    }*/
}


QColor Customlexer::defaultColor(int style)
{
switch(style){
        case Default:
            return QColor(0xe0, 0x0, 0x0);
        case Comment:
            return QColor(0x0, 0xe0, 0x0);
    }
    return QsciLexer::defaultColor(style);
}

QFont  Customlexer::defaultFont(int style)
{
    /*switch(style){
        case Default:
    return QFont("Courier New", 16);
        case Comment:
    return QFont("Courier New", 8);
    }*/
    return QFont("Courier New", 10);
}

QColor Customlexer::defaultPaper(int style)
{
    return QsciLexer::defaultPaper(style);
}



QsciStyle Customlexer::getStyle(int style)
{
            return QsciStyle(style);

    if (style < MaxStyle) {
        return QsciStyle(style, description(style), defaultColor(style),
            defaultPaper(style), defaultFont(style));
    } else {
        return QsciStyle(style);
    }
}
