#ifndef HUMBUGLIB_APPGB_H
#define HUMBUGLIB_APPGB_H
#include <string>


class AppGB {
public:

	static AppGB& Instance() {
		static AppGB theAppGB;   // Instantiated when this function is called
		return theAppGB;
	}

	std::string ExePath() const { return exePath; }
	std::string AppDir() const { return appDir; }

private:

	AppGB();                                  // constructor is private
	AppGB(AppGB const&);                 // copy constructor is private
	AppGB& operator=(AppGB const&);  // assignment operator is private
	~AppGB();                                 // destructor is private

	std::string exePath;
	std::string appDir;
};

#endif // HUMBUGLIB_APPGB_H
