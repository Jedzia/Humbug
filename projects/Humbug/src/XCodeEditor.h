#ifndef XCODEEDITOR_H
#define XCODEEDITOR_H

#include <QObject>
#include "Qsci/qsciscintilla.h"
//#include "Qsci/qscilexercustom.h"
//class QsciStyle;

class XCodeEditor : public QsciScintilla {
    Q_OBJECT
public:
    XCodeEditor(QWidget *parent = 0);
    ~XCodeEditor(void);

private:

};

#endif // #ifndef XCODEEDITOR_H
