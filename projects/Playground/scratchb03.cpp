#include <iostream>
#include <sstream>
#include <string>
#include <boost/array.hpp>
#include <boost/algorithm/cxx14/equal.hpp>
#include <array>


inline void TestArrayFoo() {
    std::array<int, 9> marr;
    marr[0] = 123456;

    boost::array<int, 4> a = { { 1, 2, 3 } };
    boost::array<int, 4> b = { 1, 2, 3 };

    auto seq1 = { 0, 1, 2 };
    auto seq2 = { 0, 1, 2, 3, 4 };

    bool r1 = std::equal(seq1.begin(), seq1.end(), seq2.begin()); // true
    //bool r2 = std::equal(seq2.begin(), seq2.end(), seq1.begin()); // Undefined behavior
    bool r3 = boost::algorithm::equal(seq1.begin(), seq1.end(), seq2.begin(), seq2.end()); // false
}

int main(int argc, char *argv[])
{ 
    const std::string input = "\\begin{minipage}[t]{1\\columnwidth}% \n \
\\begin{jcode}{Testerei von Code}{link} \n \
\n \
Das ist Mathe: $\\sqrt{25*22}$ + $\\sum e\\frac{o^{2}}{\\pi}*22_{\\beta}...in\\, q\\left\\Uparrow \\oiintop+a\\right\\Uparrow $ \n \
\n \
\\textit{InfoDreckDepp}\\end{jcode}% \n \
\\end{minipage}";

    TestArrayFoo();
	
    std::ostringstream ss;
    std::ostringstream out;
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
    ss << std::endl;
	ss << input;
    std::cout << input << std::endl;  // displays the input string.
    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------------" << std::endl;
	
    std::string output(ss.str());
	
	
    std::string::iterator it;
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

    std::cout << out.str() << std::endl;  // displays the processed output.

}