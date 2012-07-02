#include "stdafx.h"
#include "SelectionMarker.h"

#include <build/cmake/include/debug.h>

SelectionMarker::SelectionMarker(QsciScintilla *textEdit)
{
    if(textEdit->hasSelectedText())
    {
        textEdit->getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
        selectedText = textEdit->selectedText(); 
        positionFrom = textEdit->positionFromLineIndex(lineFrom, indexFrom);
        positionTo = textEdit->positionFromLineIndex(lineTo, indexTo);

        //std::string *oukk = new std::string("Du older Depp");
        //QString *nase = new QString(selectedText);
    }
}

/*SelectionMarker::SelectionMarker(void)
{
}*/

SelectionMarker::~SelectionMarker(void)
{
}
