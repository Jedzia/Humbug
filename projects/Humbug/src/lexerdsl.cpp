#include "stdafx.h"
#include "lexerdsl.h"
#include "qpid/RangeSet.h"

#include <QDebug>
#include <QString>

#include <build/cmake/include/debug.h>

using namespace qpid;

LexerDSL::LexerDSL(QObject *parent) : QsciLexerCustom(parent)
, positionFrom(0), positionTo(0)//, sel(0)
{
    qDebug() << __FUNCTION__;
}

LexerDSL::~LexerDSL()
{
    qDebug() << __FUNCTION__;
}

void LexerDSL::setEditor(QsciScintilla *editor)
{
    QsciLexerCustom::setEditor(editor);
    connect(editor, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

void LexerDSL::markSelection( void) 
{ 
    if (!editor())
        return;

    SelectionMarker sel(editor());

    qDebug() << "!!!markSelection!!! ";
    QString content = editor()->text();

    // hier den select text im document suchen wie unten
    // und das rangeset setzen

    QString searchword = sel.getSelectedText();
    if (searchword.isNull() || searchword.isEmpty())
        return;
    //QString searchword("MainWindow");
    QRegExp rx("(" + searchword +")");
    QStringList slist;
    int spos = 0;

    while ((spos = rx.indexIn(content, spos)) != -1) {
        QString yyy;
        yyy.setNum(spos);
        slist <<  "position:" + yyy + "-" + rx.cap(1);
        spos += rx.matchedLength();

        markedLines.addRange(Range<int>(spos-searchword.length(),spos));
        //startStyling(spos-searchword.length());
        //setStyling(searchword.length(), DefineValue);
    }

    qDebug() << "Matches: =" << slist;



    //LineSet rset();
//    markedLines.addRange(Range<int>(sel.getPositionFrom(),sel.getPositionTo()));

    this->editor()->recolor();

    return;
    int pos = 0;
    /*int dlen = editor()->SendScintilla(QsciScintilla::SCI_GETLENGTH);
    int caret = editor()->SendScintilla(QsciScintilla::SCI_GETCURRENTPOS);
    int clen = caret - start;
    char *orig_context = new char[dlen+1];

    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, 0, dlen, orig_context);

    QString sourcestring = QString(orig_context);
    delete[] orig_context;*/
    QString sourcestring = editor()->text();

    //QRegExp regex("MainWindow");
    /*const QRegExp regex("(\\d+)");
    //int matches = sourcestring.indexOf(regex, 0);
    int matches = regex.indexIn(sourcestring);
    QString s1 = regex.cap(0);
    QString s2 = regex.cap(1);
    QString s3 = regex.cap(2);
    QString s4 = regex.cap(3);

    qDebug() << "s1 =" << s1;
    qDebug() << "s2 =" << s2;
    qDebug() << "s3 =" << s3;
    qDebug() << "s4 =" << s4;*/

    //QRegExp rx("(\\d+)");

    return;

    QStringList list = sourcestring.split("\n");
    //qDebug() << "source =" << source;
    for (int linenr = 0; linenr < list.size(); linenr++)
    {
    }

    QStringList result;
    result = list.filter("Main");
    //qDebug() << "result =" << result << endl;


    //QString x = result[0];


}

/*void LexerDSL::setSelection( shared_ptr<SelectionMarker> smarker) 
{ 

    //bool b = markedLines->contains(5);

    //positionFrom = smarker.getPositionFrom();
    //positionTo = smarker.getPositionTo();
    //sel = smarker;
    //this->editor()->SendScintilla(QsciScintilla::SCN_UPDATEUI);
    //this->editor()->modificationAttempted();
    //emit this->editor()->textChanged();

    // recolor. repaint the text.
    this->editor()->recolor();
    return;
    const QString a("a");
    this->editor()->insertAt(a,0,0);
    this->editor()->undo();
    //this->editor()->update();
}*/

QString LexerDSL::description(int style) const
{
    switch (style)
    {
    case Default:
        return tr("Default");
    case Define:
        return tr("Define");
    case DefineValue:
        return tr("Defined Value");
    case Keyword:
        return tr("Keyword");
    case Entry:
        return tr("Entry");
    case Brace:
        return tr("Brace");
    case Error:
        return tr("Error");
    }

    return QString();
}

QColor LexerDSL::defaultColor(int style) const
{
    switch (style)
    {
    case Default:
        return Qt::black;
    case Define:
        return Qt::darkGray;
    case DefineValue:
        return Qt::darkGreen;
    case Keyword:
        return Qt::darkBlue;
    case Entry:
        return Qt::blue;
    case Brace:
        return Qt::darkRed;
    case Error:
        return Qt::red;
    }

    return QsciLexer::defaultColor(style);
}

void LexerDSL::textChanged(void)
{
    if (!editor())
        return;
    qDebug() << "TEXTCHANGED ";
    QString content = editor()->text();

}

void LexerDSL::styleText(int start, int end)
{
    //qDebug() << __FUNCTION__;

    if (!editor())
        return;
    //QString moep("Hehehe hahah");
    //const int eee=1;
    //this->editor()->annotate(5, &moep, 2);
    qDebug() << "style " << start << " - " << end;
    if(end <= start)
        return;


    int lns = this->editor()->lines();
    int k = 0, style = Default;
    for (int j = start; j < end; j++)
    {
        int cline, cindex, linelength;
        this->editor()->lineIndexFromPosition(j, &cline, &cindex);
        linelength = this->editor()->lineLength(cline);
        int position = this->editor()->positionFromLineIndex(cline, cindex);

        if(markedLines.contains(j))
        {
            startStyling(j);
            setStyling(1, DefineValue);
        }
        /*continue;
        if(sel)
        {
            if(j==sel->getPositionFrom())
            {
                int sellength = sel->getPositionTo() - sel->getPositionFrom();
                //startStyling(j);
                //setStyling(sellength, DefineValue);
            }
        }

        int chr = getCharAt(j);
        if (chr == 'e')
        {
            //startStyling(j);
            //setStyling(1, Error);
        }
        else    if (chr == 'a')
        {
            //startStyling(j);
            //setStyling(1, Entry);
        }
        else
        {
            //startStyling(j);
            //setStyling(1, Default);
        }*/

    }
    //qDebug() << "lines" << lns << endl;

    return;
    int i, line, ch;
    int keywordStart, textStart;

    while (start < end)
    {
        // skip EOLs
        while (start < end && isEOL(getCharAt(start)))
            start++;

        line = getLineAt(start);

        ch = getCharAt(start);

        // check for define
        if (ch == '#')
        {
            // color as define to the empty space
            i = start+1;
            while (i < end && isWordChar(getCharAt(i)))
                ++i;

            startStyling(start);
            setStyling(i-start, Define);
            start = i;

            // color as define value to the end of the line
            i = getEOLfrom(line);
            startStyling(start);
            setStyling(i-start, DefineValue);
            start = i;
            continue;
        }

        // check for entry
        if (isWordChar(ch))
        {
            //qDebug() << "entry";
            // color as entry name to the end of the line
            i = getEOLfrom(line);
            startStyling(start);
            setStyling(i-start, Entry);
            start = i;
            continue;
        }

        // else, colorize dsl markup
        {
            int eolpos = getEOLfrom(line);
            bool isTag = false;

            while (start < eolpos)
            {
                ch = getCharAt(start);

                if (ch == 'e')
                {
                    // xxxxx style brace

                    startStyling(start);
                    setStyling(1, Error);
                    startStyling(start+1);
                    setStyling(1, Default);
                    break;
                }

                if (ch == '[')
                {
                    // check if it's a tag
                    int pos = start;
                    while (++pos < eolpos)
                    {
                        int ch1 = getCharAt(pos);

                        if (ch1 == '[')
                            break;

                        if (ch1 == ']')
                        {
                            // style brace
                            startStyling(start);
                            setStyling(1, Brace);
                            // style tag
                            startStyling(start+1);
                            setStyling(pos-start-1, Keyword);
                            // style brace
                            startStyling(pos);
                            setStyling(1, Brace);

                            start = pos;
                            break;
                        }

                    }

                } // if

                // inbetween tags
                start++;

            } // while

            // if tag is not closed: error
            //      if (isTag)
            //      {
            //        startStyling(keywordStart);
            //        setStyling(end-keywordStart, Error);
            //        return;
            //      }


        } // DSL markup

    }

}
