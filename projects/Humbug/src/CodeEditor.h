#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QObject>
#include "Qsci/qsciscintilla.h"
//#include "Qsci/qscilexercustom.h"
//class QsciStyle;

class CodeEditor : public QsciScintilla {
    Q_OBJECT
public:
    CodeEditor(QWidget *parent = 0);
    ~CodeEditor(void);

    //! Recolours the document between the \a start and \a end positions.
    //! \a start defaults to the start of the document and \a end defaults to
    //! the end of the document.
    virtual void recolor(int start = 0, int end = -1) {
        QsciScintilla::recolor(start, end);
    }

    //! Re-implemented to handle the context menu.
    virtual void contextMenuEvent(QContextMenuEvent *e) {
        QsciScintilla::contextMenuEvent(e);
    }

    //! Re-implemented to paint the viewport.
    virtual void paintEvent(QPaintEvent *e);

private:

};

#endif // #ifndef CODEEDITOR_H
