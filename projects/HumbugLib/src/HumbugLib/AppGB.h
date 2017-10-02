/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the AppGB.h class.
 * \folder     $(folder)
 * \file       AppGB.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUGGLLIB_APPGB_H
#define HUMBUGGLLIB_APPGB_H
#include <string>
class AppGB {
public:

    static AppGB& Instance() {
        static AppGB theAppGB;           // Instantiated when this function is called
        return theAppGB;
    }

    std::string ExePath() const { return exePath; }

    std::string AppDir() const { return appDir; }

private:

    AppGB();                                      // constructor is private
    AppGB(AppGB const&);                     // copy constructor is private
    AppGB& operator=(AppGB const&);      // assignment operator is private

    ~AppGB();                                     // destructor is private
    std::string exePath;
    std::string appDir;
};
#endif // HUMBUGGLLIB_APPGB_H
