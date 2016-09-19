echo off
rem ************************************************
rem *                                              *
rem *     LintAllCppHelper.bat                     *
rem *                                              *
rem * designed to be called from "LintAllCPP.bat"  *
rem ************************************************
c:\lint\lint-nt -i"C:\lint" -i%~dp0 -b %~dp0LintMSVC90.lnt  "%1" %2 %3 %4 %5 %6 %7 %8 %9 | %~dp0\EchoAndSave c:\linttemp.txt
