#ifndef SELECTIONMARKER_H
#define SELECTIONMARKER_H

//#include <QObject>
#include "Qsci/qsciscintilla.h"

class SelectionMarker //: public QObject
{
    //Q_OBJECT
public:
    SelectionMarker(QsciScintilla *textEdit);
    //SelectionMarker(void);
    ~SelectionMarker(void);

    //! The Selected Text is returned.
    QString getSelectedText(void) const {return selectedText;}

    //! The charcount difference between the selected Text and the parameter is returned.
    int getTextDifference(QString &newText) {return selectedText.count() - newText.count();}
    
    inline int getPositionFrom(void) { return positionFrom; }
    inline int getPositionTo(void) { return positionTo; }

private:
    int lineFrom;
    int indexFrom;
    int lineTo;
    int indexTo;
    int positionFrom;
    int positionTo;
    QString selectedText;
};

#endif
