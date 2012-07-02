#include <iostream>
#include <sstream>
#include <string>

//#include <CppStructz/support/debug.h>
#include <CppStructz/log/LogHelper.h>
//#include <CppStructz/support/gettext.h>
//#include <CppStructz/support/docstring.h>
#include <CppStructz/text/TextDocument.h>
#include <CppStructz/text/TextPosition.h>
#include <CppStructz/filesystem/CszGlobals.h>
#include <CppStructz/TestClass.h>

using namespace std;

int main(int argc, char *argv[])
{
    using namespace CPPSTRUCTZ_NAMESPACE::text;
    //using namespace CPPSTRUCTZ_NAMESPACE;

	const string input = "\\begin{minipage}[t]{1\\columnwidth}% \n \
\\begin{jcode}{Testerei von $Code$}{link} \n \
\n \
Das ist $Mathe$: $\\sqrt{25*22}$ +  \n \
\n \
\\textit{$InfoDreckDepp$}\\end{jcode}% \n \
\\end{$$minipage}";

std::string exepath = csz::CszGlobals::Instance().getExeLocation();
exepath += "\\mainwindow.cpp";

cout << csz::CszGlobals::Instance().getExeLocation() << endl;
{
    TextDocument doc(input);

    csz::TestClass tc(33);

}
{

    TextDocument doc;
    doc.loadTemplates(exepath.c_str());
    TextDocument::TextPositionList poslist = doc.templatePositions();

    cout << "BLA" << endl;
}

    //csz::dbg << "Ending Execution" << LOGGER_ENDMSG;
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
	ss << "arschloch";
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

}