/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include "stdafx.h"
#include "mainwindow.h"
#include "defs.h"
#include <memory>   // std::auto_ptr
#include <iostream>
#ifndef LINUX
# include "AssetList.hxx"
#endif


#include "Project/ProjectModel.h"

//#include <iostream>

#include <QDebug>
#include <QDomDocument>
#include <Qsci/qscilexercpp.h>
#include "SelectionMarker.h"
#include "SelectionDialog.h"
//#ifdef DEBUG_MEMORY
//    #include DEBUG_MEMORY_INCLUDE
//#endif
#include "Customlexer.h"
#include "CppStructz/filesystem/CszDirSearch.h"
#include "CppStructz/filesystem/CszGlobals.h"

#include <build/cmake/include/debug.h>

using namespace std;
using namespace CPPSTRUCTZ_NAMESPACE;

//! [0]
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), lex(0), projectModel(NULL)
{
    ui.setupUi(this);
    connect(ui.actionLoadXml, SIGNAL(triggered()), this, SLOT(loadXML()));
    connect(ui.actionGetSelection, SIGNAL(triggered()), this, SLOT(selection()));
    connect(ui.actionHighlight, SIGNAL(triggered()), this, SLOT(highlight()));
    connect(ui.actionRun_Dirsearch, SIGNAL(triggered()), this, SLOT(runDirsearch()));
    // http://www.riverbankcomputing.com/pipermail/qscintilla/2007-March/000044.html
    //QsciLexerCPP* lex = new QsciLexerCPP(ui.textEdit);
    lex = new LexerDSL(ui.codeEditor);
    //Customlexer* lex = new Customlexer(ui.textEdit);
    /*ui.textEdit->setPaper(QColor(1,81,107));
    ui.textEdit->setMarginLineNumbers(1,true);
    ui.textEdit->setFolding(QsciScintilla::CircledTreeFoldStyle);
    ui.textEdit->setAutoIndent(true);
    ui.textEdit->setAutoCompletionThreshold(2);
    ui.textEdit->setAutoCompletionSource(QsciScintilla::AcsAPIs);*/

    ui.codeEditor->setLexer(lex);
    //ui.codeEditor->setReadOnly(true);
#if WIN32
	QString exePath = QString::fromUtf8(CszGlobals::Instance().getInstallPath().c_str());
    QString filePath(exePath + "/mainwindow.cpp");
    //QString filePath("D:/E/Projects/C++/Humbug/src/Humbug/mainwindow.cpp");
#else
    QString filePath("/home/askme/devel/Humbug/trunk/src/Humbug/mainwindow.cpp");
#endif //WIN32

    try
    {
        std::string sss = CszGlobals::Instance().getInstallPath();
        //ui.lineEdit_6->setText(QString::fromStdString(sss));
        ui.lineEdit_6->setText(QString::fromUtf8(sss.c_str()));
        ui.lineEdit_7->setText(QString::fromUtf8(CszGlobals::Instance().getProfilePath().c_str()));

		// This is not working correct. use D:\QT4\src\corelib\kernel\qcoreapplication_win.cpp qAppFileName()
		ui.leMarked->setText(QString::fromUtf8(boost::filesystem::current_path().generic_string().c_str()));

    }
    catch (boost::filesystem3::filesystem_error &e)
    {
        std::cout << "SAKRAMENT !" << e.what() << std::endl;
    }

	/*QStringList args = QCoreApplication::arguments();
    //std::cout << "Cmd " << args.at(0).toStdString() << std::endl;
    //std::cout << "Cmd " << args.at(0).toAscii() << std::endl;
	ui.lineEdit_9->setText(args.at(0));*/

	ui.lineEdit_9->setText(QCoreApplication::applicationDirPath());

    QString fileContent = "";
    QFile inSrcFile(filePath);
    if ( !inSrcFile.open(QFile::ReadOnly | QFile::Text) ) {
        QMessageBox::warning(NULL, tr("Error opening file"), tr("Cannot read the file ")+"\""+filePath+"\"." );
        return;
    }


    QTextStream inSrcStrm(&inSrcFile);

    fileContent = inSrcStrm.readAll();
    //QApplication::restoreOverrideCursor();
    inSrcFile.close();


    ui.textEdit->setText(fileContent);
    ui.textEditN->setText(fileContent);
    ui.codeEditor->setText(fileContent);
    //CszGlobals *fuck = CszGlobals::Instance();

    //ui.lineEdit_6->setText(QString::fromStdString(Glob->getExePath()));
    //ui.lineEdit_7->setText(QString::fromStdString(Glob->getProfilePath()));
//ui.textEdit->read(&inSrcStrm);

}

MainWindow::~MainWindow(void)
{
    //delete lex;
}

void MainWindow::selection()
{

    //SelectionDialog selectDialog(this);
    //selectDialog.exec();

    SelectionDialog *selectDialog = new SelectionDialog(this);
    //selectDialog->setModal(true);
    selectDialog->exec();


    if (selectDialog->radioButton_1->isChecked())
    {
        qDebug() << "radioButton_1 pressed";
    }
    else if (selectDialog->radioButton_2->isChecked())
    {
        qDebug() << "radioButton_2 pressed";
    }
    else if (selectDialog->radioButton_3->isChecked())
    {
        qDebug() << "radioButton_3 pressed";
    }

    SelectionMarker sel(ui.textEdit);
    ui.leMarked->setText(sel.getSelectedText());

    /*QTextEdit::ExtraSelection ex;
    ex.cursor = QTextCursor(ui.textEditN->document());
    ex.format = QTextCharFormat();
    ex.format.setFontUnderline(true);
    QList<QTextEdit::ExtraSelection> extraselections;
    extraselections.*/
    //ui.textEditN->setExtraSelections(
    //std::string *oukk = new std::string("Olde Nase");

    QList<QTextEdit::ExtraSelection> extraSelections;

    QTextEdit::ExtraSelection selection;

    QColor lineColor = QColor(Qt::yellow).lighter(160);

    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = ui.textEditN->textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);
    ui.textEditN->setExtraSelections(extraSelections);


}

void MainWindow::runDirsearch()
{
    CszDirSearch ds;
#if WIN32
	//std::string sdir("D:\\tmp");
	std::string sdir(CszGlobals::Instance().getInstallPath());
#else
    std::string sdir(".");
#endif //WIN32
	//ds.SearchDirectory(sdir, "C*.*", false);
	const filelist& flist = ds.searchDirectory(sdir + "/", "n*.*", true);
	QStringList fstrlist;
	//std::vector<std::string>::const_iterator it;
	filelist::const_iterator it;
	int count = 0;
	for( it = flist.begin(); it != flist.end(); it++ ) {
		//std::wstring s = *it;
		//QString wide = QString::fromStdWString(s);
		//ui.textEditN->append("\r\n");
		//ui.textEditN->append(QString::fromUtf8(s.c_str()));
		//ui.textEditN->append(QString::fromLatin1(s.c_str()));
		//std::wstring qStr(L"RickTest");
		//const wchar_t * chars = s.c_str();
		//QStdWString qStr(s);
		//QString xxx = QString::fromWCharArray(chars);
		ui.textEditN->append(QString::fromStdWString(*it));
	}
    //ds.TraverseDirectory(sdir);
	/*std::string str = "abc\0";
	QString qstr = QString::fromStdString(str);
	const std::string str2 = qstr.toStdString();

	std::wstring wstr = L"abc\0";
	QString wqstr = QString::fromStdWString(wstr);
	const std::wstring wstr2 = wqstr.toStdWString();*/

}
//http://stackoverflow.com/questions/688760/how-to-create-a-utf-8-string-literal-in-visual-c-2008

#if defined(_MSC_VER) && _MSC_VER > 1310
// Visual C++ 2005 and later require the source files in UTF-8, and all strings
// to be encoded as wchar_t otherwise the strings will be converted into the
// local multibyte encoding and cause errors. To use a wchar_t as UTF-8, these
// strings then need to be convert back to UTF-8. This function is just a rough
// example of how to do this.
#include <Windows.h>
# define utf8(str)  ConvertToUTF8(L##str)
const char *
ConvertToUTF8(const wchar_t * pStr) {
static char szBuf[1024];
WideCharToMultiByte(CP_UTF8, 0, pStr, -1, szBuf, sizeof(szBuf), NULL, NULL);
return szBuf;
}
#else
// Visual C++ 2003 and gcc will use the string literals as is, so the files
// should be saved as UTF-8. gcc requires the files to not have a UTF-8 BOM.
# define utf8(str)  str
#endif

void MainWindow::highlight()
{
    /*boost::shared_ptr<SelectionMarker> sel(new SelectionMarker(ui.codeEditor));

    ui.leMarked->setText(sel->getSelectedText());
    lex->setSelection(sel);*/
    lex->markSelection();
    //QString qs;
    //QStdWString ws;
    //ws.insert(L"Dreck");
    //qs.fromStdWString(L"abc");
    //std::string kacka("C?t?lin Piti?");

    std::string mText;
    mText = utf8("Chinese (Traditional)");
    mText = utf8("??? (??)");
    mText = utf8("??? (??)");
    //mText = utf8("Chinês (Tradicional)");

    std::string kacka(utf8("C?t?lin Piti?"));
    std::wstring ws(L"C?t?lin Piti?");
    //std::wstring ws(utf8("C?t?lin Piti?"));
    std::string temp;
    std::copy(ws.begin(), ws.end(), std::back_inserter(temp));
    std::string xx1("Ond bra\314\212d do\314\210d i Venedig");
    //ui.textEditN->setText(temp.c_str());
    //ui.textEditN->setText(kacka.c_str());
    //ui.textEditN->setText(xx1.c_str());
    QString qs;
    QString qs1("C?t?lin Piti?");

    //Das geht!
    ui.textEditN->setText(QString::fromUtf8("C?t?lin Piti?"));
    ui.textEditN->append("\r\n");
    ui.textEditN->append(qs1);

    std::cout << xx1 << "Fuck  " << "C?t?lin Piti?" << std::endl;
    //ui.textEdit->autoCompleteFromAll();

    /*ui.textEdit->setCallTipsStyle(QsciScintilla::CallTipsStyle::CallTipsContext);
    ui.textEdit->callTip();*/

    /*QPixmap p(QString::fromUtf8(":/icons/triangle.png"));
    int ma = ui.textEdit->markerDefine(p);
    ui.textEdit->markerAdd(22, ma);*/

    //ui.textEdit->setSelectionBackgroundColor(Qt::red);
    //ui.textEdit->trUtf8(

    return;
    QsciLexerCPP *lexer = (QsciLexerCPP*) ui.textEdit->lexer();

    QStringList aList = lexer->autoCompletionWordSeparators();
    QString aListStr = aList.join(";");

    QSettings lexersettings;
    lexer->readSettings(lexersettings);

    QString settStr = lexersettings.allKeys().join(";");




    //std::string *oukk = new std::string("Olde Nase");
}

void MainWindow::loadXML()
{
#ifndef LINUX
    try
    {
        const std::string filename("D:\\AssetListRaw-characterID_1003586849-corp_True-2010-11-20_035549.xml");
        //auto_ptr<eveapi_> h (eveapi_ ("hello.xml"));
        //auto_ptr<eveapi> h (eveapi_ ("D:/Eigene Dateien/Projects/C++/Humbug/src/Humbug/content/AssetListRaw-characterID_1003586849-corp_True-2010-11-20_035549.xml"));
        //auto_ptr<eveapi> h (eveapi_ ("D:\\AssetListRaw-characterID_1003586849-corp_True-2010-11-20_035549.xml"));
        xml_schema::properties p = xml_schema::properties ();
        p.no_namespace_schema_location("D:/Eigene Dateien/Projects/C++/Humbug/src/Humbug/content/AssetList.xsd");
        auto_ptr<eveapi> docEveapi (eveapi_ (filename,0, p));
        eveapi::result_type res = docEveapi->result();
        result::rowset_type rowset = res.rowset();
        rowset::row_sequence rows = rowset.row();

        // alle Elemente "Name" unter Root durchlaufen
        for( rowset::row_const_iterator i (rows.begin());
            i != rows.end();
            ++i )
        {
            // Element "greeting" und Element "name" ausgeben
            //cout << i->quantity() << ", " << *i << "!" << endl;
            cout << "itemID: " << i->itemID() << endl;
        }

        /*for( hello_t::name_const_iterator i (h->name().begin());
        i != h->name().end();
        ++i )
        {
        // Element "greeting" und Element "name" ausgeben
        //cout << h->greeting() << ", " << *i << "!" << endl;
        }*/
        cout << filename << endl;
    }
    catch (const xml_schema::exception& e)
    {
        cerr << e << endl;
        //return 1;
    }

    return;

    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    std::cout << "     Bytes Filename" << std::endl;
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
            .arg(fileInfo.fileName()));
        std::cout << std::endl;
    }


    QDomDocument doc("mydocument");
    // QFile file("D:/Eigene Dateien/Projects/C++/Humbug/src/Humbug/content/foreach.snippet");
    QFile file("D:/Eigene Dateien/Projects/C++/Humbug/src/Humbug/content/Simplified DocBook Article Title.xml");
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }
    file.close();

    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = doc.documentElement();
    //QTextStream xxx(stdout);
    QTextStream out(stdout);

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            std::cout << qPrintable(e.tagName()) <<  std::endl; // the node really is an element.
            //xxx << qPrintable(e.tagName()) <<  endlw; // the node really is an element.
        }
        n = n.nextSibling();
    }

    // Here we append a new element to the end of the document
    QDomElement elem = doc.createElement("img");
    elem.setAttribute("src", "myimage.png");
    docElem.appendChild(elem);
#endif //ndef LINUX
}

//! [0]

//! [1]
/*void MainWindow::on_inputSpinBox1_valueChanged(int value)
{
    //ui.outputWidget->setText(QString::number(value + ui.inputSpinBox2->value()));
}*/
//! [1]

//! [2]
/*void MainWindow::on_inputSpinBox2_valueChanged(int value)
{
    //ui.outputWidget->setText(QString::number(value + ui.inputSpinBox1->value()));
}*/
//! [2]

void MainWindow::ca_p_clicked()
{
    //ui.outputWidget->setText(QString::number(33));
}


void MainWindow::on_pbTest_clicked()
{
    ui.lineEdit_8->setText("Jau FICKEN !");

	QList<QTreeWidgetItem *> items;
	for (int i = 0; i < 10; ++i)
	{
		QTreeWidgetItem * topitem;
		items.append(topitem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
		QTreeWidgetItem * subitem;
		topitem->addChild(subitem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Arschloch"))));
	}
	ui.prjExplorer->insertTopLevelItems(0, items);

	if(projectModel != NULL)
		delete projectModel;
	projectModel = new ProjectModel(this);
	ui.prjView->setModel(projectModel);
	//projectModel->setRootNode(XmlProjectParser::test());

}

void MainWindow::on_pbLoadProject_clicked()
{
    try
    {
		const std::string startloc = "D:/E/Projects/C++/Humbug/projects/Humbug/XSD/";
		QString fileName = QFileDialog::getOpenFileName(this,
		//	tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
		tr("Open Project"), QString::fromStdString(startloc), tr("Project Files (*.prj *.xml *.tmplproj)"));
		if (fileName.isEmpty())
		{
			return;
		}
        //const std::string filename("D:\\AssetListRaw-characterID_1003586849-corp_True-2010-11-20_035549.xml");
        //auto_ptr<eveapi_> h (eveapi_ ("hello.xml"));
        //auto_ptr<eveapi> h (eveapi_ ("D:/Eigene Dateien/Projects/C++/Humbug/src/Humbug/content/AssetListRaw-characterID_1003586849-corp_True-2010-11-20_035549.xml"));
        //auto_ptr<eveapi> h (eveapi_ ("D:\\AssetListRaw-characterID_1003586849-corp_True-2010-11-20_035549.xml"));
        //xml_schema::properties p = xml_schema::properties ();
        //p.no_namespace_schema_location("D:/E/Projects/C++/Humbug/projects/Humbug/XSD/project.xsd");
        //project_type /* this is auto_ptr<project>*/ tmplProject (project_(fileName.toStdString(),0, p));

		/*ProjectParser pp;
		//ProjectNode * root = pp.parse(fileName);
		if(projectModel != NULL)
			delete projectModel;
		projectModel = new ProjectModel(this);
		ui.prjView->setModel(projectModel);
		projectModel->setRootNode(pp.parse(fileName.toStdString()));

		*/
        cout << fileName.toStdString() << endl;
    }
    catch (const xml_schema::exception& e)
    {
        cerr << e << endl;
        //return 1;
    }
}

