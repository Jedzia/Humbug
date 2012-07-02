#include <iostream>
#include <sstream>
#include <string>
#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QFile>


#include <CppStructz/text/TextDocument.h>
#include <CppStructz/filesystem/CszGlobals.h>
#include "CppStructz/filesystem/CszDirSearch.h"

//#include <TCHAR.H>
#define _T(x)      L ## x

using namespace std;
using namespace CPPSTRUCTZ_NAMESPACE;

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

#ifdef LINUX
typedef int DWORD;
#endif

void PrintCharTab()
{
#ifndef LINUX
	const int num = 4*4*256;
	const int start = 0x100;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	wchar_t buffer[num];

	for (wchar_t val = start; val<start+num; val++)
		buffer[val-start] = val;

	DWORD ignore;
	WriteConsoleW(console, buffer, num, &ignore, NULL);
#endif	
}

void WrConsoleWtest()
{

	QString unicodeString(QChar(0x9788));
	QTextStream qStdOut(stdout, QIODevice::WriteOnly);
	DWORD dwWritten;

	// 1st try: replace oem with ascii
#ifdef _WIN32
	std::cout << "Switch input to Ascii CodePage (1252): " << (::SetConsoleCP(::GetACP())?"ok":"fail") << std::endl;
	std::cout << "Switch output to Ascii CodePage (1252): " << (::SetConsoleOutputCP(::GetACP())?"ok":"fail") << std::endl;
	std::cout << "Current input CodePage: " << (unsigned int)::GetConsoleCP() << std::endl;
	std::cout << "Current output CodePage: " << (unsigned int)::GetConsoleOutputCP() << std::endl;
#endif
	qStdOut << QString("QTextStream: ") << unicodeString << QChar('\n');
	qStdOut.flush();
	qStdOut.setCodec("UTF-16");
	qStdOut << QString("QTextStream: ") << unicodeString << QChar('\n');
	qStdOut.flush();
	std::cout << "cout: " << (char*)unicodeString.utf16() << std::endl;
	std::cout << "cout: " << (char*)(unicodeString.toUtf8().constData()) << std::endl;
	std::wcout << L"wcout: " << (wchar_t*)unicodeString.utf16() << std::endl;
	std::wcout << L"wcout: " << (char*)(unicodeString.toUtf8().constData()) << std::endl;
	printf("printf: %ls\n", unicodeString.utf16());
	wprintf(L"wprintf: %ls\n", unicodeString.utf16());
#ifdef _WIN32
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), L"WriteConsoleW: ", 15, &dwWritten, NULL);
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), (unicodeString + '\n').utf16(), unicodeString.length()+1, &dwWritten, NULL);
#endif
}

void FileOut()
{
	QString fname("out.txt");
	QFile file(fname);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	//file.open(QFile::WriteOnly);
	//file.write(QString::fromUtf8(L"éä").toUtf8());
	/*char msg[] = "éä";
	file.write(msg, strlen(msg)); // avoids a QByteArray temporary
	file.close();
	return;*/

	QTextStream outfile(&file);
	outfile.setCodec("UTF-8");
	//outfile << bom;
	QString fff = QString::fromUtf8(utf8("Älkopâps°€"));
	outfile << fff << "\n";
	outfile << "The magic number is: " << 49 << "\n";
	//fff = QString::fromUtf8(utf8("??? (??)"));
	fff = QString::fromUtf8(utf8("®EvePanix © Jedzia 2011"));
	outfile << fff << "\n";
	outfile << "The magic number is: " << 49 << "\n";
}

int main(int argc, char *argv[])
{
	CszGlobals::Instance().init(argc, argv);
	QCoreApplication a(argc, argv);

	const string input = "\\begin{minipage}[t]{1\\columnwidth}% \n \
						 \\begin{jcode}{Testerei von $Code$}{link} \n \
						 \n \
						 Das ist $Mathe$: $\\sqrt{25*22}$ +  \n \
						 \n \
						 \\textit{$InfoDreckDepp$}\\end{jcode}% \n \
						 \\end{$$minipage}";


//	PrintCharTab();


//	WrConsoleWtest();
//	a.exec();



//???????????????????????????????
	std::string mText;
	mText = utf8("Chinese (Traditional)");
	mText = utf8("??? (??)");
	mText = utf8("??? (??)");
	//mText = utf8("Chinês (Tradicional)");

	std::string kacka(utf8("C?t?lin Pitiáß"));
	std::wstring ws(L"C?t?lin Pitiáß");

	std::string sdir(CszGlobals::Instance().getExeLocation());
	cout << sdir << endl;

	cout << "---------------------------------------------------" << endl;
	cout << endl;

	CszDirSearch ds;
	const filelist& flist = ds.searchDirectory(sdir + "/", "n*.*", true);
	cout << "---------------------------------------------------" << endl;
	cout << endl;

	QStringList fstrlist;
	filelist::const_iterator it;
	int count = 0;
	for( it = flist.begin(); it != flist.end(); it++ ) {
		QString qStr = QString::fromStdWString(*it);

	}
	cout << "---------------------------------------------------" << endl;
	cout << endl;

	// Check Console
	// dir D:\E\Projects\C++\Humbug\build\Playground\Debug

	/*Csz::Text::TextDocument doc(input);*/

	cout << "******cout and utf8()****" << endl;
	//mText = utf8("?? ?????? ?????");
	mText = utf8("???????????????????????????????");
	cout << mText << endl;

	cout << "******Normal String constData()****" << endl;
	//QString str = QString::fromStdWString(L"www.?????.tw");
	//QString str = QString::fromStdWString(L"www.BlödeSau.tw");
	QString str = QString::fromStdWString(L"www.BlödeSau.tw");
	//WCHAR* wcar = (WCHAR*)(str.constData());
	//std::wcout << wcar << endl;
	std::wcout << str.utf16() << endl;

	cout << "******std::wcout << wchar*********" << endl;
	//std::wcout << ws << std::endl;
	std::wcout << std::wstring(L"schrßeissenDrück") << std::endl;
	std::wcout << std::wstring(L"schrßeissenDrück") << std::endl;
	//std::wcout << std::wstring(L"www.?????.tw") << std::endl;
	//std::wcout << _T("?? ?????? ?????") << std::endl;
	std::wcout << L"???????????????????????????????" << std::endl;
	std::wcout << std::wstring(L"???????????????????????????????") << std::endl;
	//std::wcout << L"schrßeissenDrück" << std::endl;
	std::wcout << std::flush;

	//QString str("C?t?lin Piti?");
	//QString str = QString::fromStdWString(L"C?t?lin P€,Dreck");
	//QString str = QString::fromStdWString(ws);
	//qs.fromStdWString(L"abc");

	FileOut();

	return 0;
	ostringstream ss;
	ostringstream out;
	/*float num;

	// use it once
	string string1 = "25 1 3.235/n1111111/n222222";
	stream1.str(string1);
	while( stream1 >> num ) cout << "num: " << num << endl;  // displays numbers, one per line

	// use the same string stream again with clear() and str()
	string string2 = "1 2 3 4 5  6 7 8 9 10";
	stream1.clear();
	stream1.str(string2);*/
	/*ss << "arschloch";
	ss << endl;
	ss << input;
	cout << input << endl;  // displays the input string.
	cout << endl;
	cout << "-----------------------------------------------------------------" << endl;

	string output(ss.str());


	string::iterator it;
	int count = 0;
	for( it = output.begin(); it != output.end(); it++ ) {
	if(*it == '\n') {
	count = 0;
	}

	if(count > 40) {
	//if(*it == '\\' || *it == '{' || *it == '}' || *it == ' ') {
	if(*it == '\\' || *it == '{' || *it == '}') {
	out << "\r\n";
	count = 0;
	}
	}
	out << *it;
	count++;
	}

	cout << out.str() << endl;  // displays the processed output.
	*/
}
