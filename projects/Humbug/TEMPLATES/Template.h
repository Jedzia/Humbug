#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QObject>
//#include "Qsci/qsciscintilla.h"
#include "Qsci/qscilexercustom.h"
class QsciStyle;

class Template : public QsciLexerCustom {
    //Q_OBJECT
public:
    enum {
        Default = 0,
        Comment = 1,
        MaxStyle
    };

    Template(QObject *parent = 0);
    ~Template(void);

    const char *language() const;
    QString description(int) const;
    void styleText(int start, int end);
    QColor defaultColor(int);
    QFont  defaultFont(int);
    QColor defaultPaper(int);

private:
    QsciStyle getStyle(int);

};

#endif // TEMPLATE_H
