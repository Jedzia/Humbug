#ifndef LEXERDSL_H
#define LEXERDSL_H
//#define QSCINTILLA_EXPORT __declspec(dllimport)
//QSCINTILLA_DLL

#include <Qsci/qscilexercustom.h>
#include <Qsci/qsciscintilla.h>
#include <boost/smart_ptr.hpp>

//#include <boost/cstdint.hpp>
//using boost::uint32_t;
#include "qpid/RangeSet.h"

#include "SelectionMarker.h"

#define DSL_DEFAULT       0
#define DSL_DEFINE        1
#define DSL_DEFINE_VALUE  2
#define DSL_TAG           3
#define DSL_ENTRY         4
#define DSL_BRACE         5
#define DSL_ERROR         6

using namespace boost;
using namespace qpid;

class LexerDSL : public QsciLexerCustom
{
    Q_OBJECT
public:
    enum {
      Default = 0,
      Define = 1,
      DefineValue = 2,
      Keyword = 3,
      Entry = 4,
      Brace = 5,
      Error = 6
    };

    LexerDSL(QObject *parent=0);
    //virtual ~LexerDSL() {}
     ~LexerDSL();

    //! Returns the name of the language.
    virtual const char *language() const { return "dsl"; }

    virtual QString description(int style) const;

    virtual QColor defaultColor(int style) const;

    virtual void styleText(int start, int end);

    //! set the editor for this lexer.
    virtual void setEditor(QsciScintilla *editor);

    //void setSelection( shared_ptr<SelectionMarker> smarker);
    void markSelection( void);

    int positionFrom;
    int positionTo;

public slots:

        void textChanged( void);


private:
    inline int getCharAt(int pos)
    { return editor()->SendScintilla(QsciScintilla::SCI_GETCHARAT, pos); }

    inline int getLineAt(int pos)
    { return editor()->SendScintilla(QsciScintilla::SCI_LINEFROMPOSITION, pos); }

    inline int getEOLfrom(int line)
    { return editor()->SendScintilla(QsciScintilla::SCI_GETLINEENDPOSITION, line); }

    inline bool isWordChar(int ch) const
    { return (ch && ch != ' ' && ch != '\t' && ch != '\r' && ch != '\n'); }

    inline bool isEOL(int ch) const
    { return (ch == '\r' || ch == '\n'); }


    //shared_ptr<SelectionMarker> sel;
    typedef RangeSet<int> LineSet;
    LineSet markedLines;
};

#endif // LEXERDSL_H
