#ifndef CUSTOMLEXER_H
#define CUSTOMLEXER_H

#include <QObject>
//#include "Qsci/qsciscintilla.h"
#include "Qsci/qscilexercustom.h"
class QsciStyle;

class Customlexer : public QsciLexerCustom {
    //Q_OBJECT
public:
    enum {
        Default = 0,
        Comment = 1,
        MaxStyle
    };

    Customlexer(QObject *parent = 0);
    ~Customlexer(void);

    const char *language() const;
    QString description(int) const;
    void styleText(int start, int end);
    QColor defaultColor(int);
    QFont  defaultFont(int);
    QColor defaultPaper(int);

private:
    QsciStyle getStyle(int);

};

#endif // #ifndef CUSTOMLEXER_H
