#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{ 
	const string input = "\\begin{minipage}[t]{1\\columnwidth}% \n \
\\begin{jcode}{Testerei von Code}{link} \n \
\n \
Das ist Mathe: $\\sqrt{25*22}$ + $\\sum e\\frac{o^{2}}{\\pi}*22_{\\beta}...in\\, q\\left\\Uparrow \\oiintop+a\\right\\Uparrow $ \n \
\n \
\\textit{InfoDreckDepp}\\end{jcode}% \n \
\\end{minipage}";


	
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
	for( it = output.begin(); it != output.end(); ++it ) {
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