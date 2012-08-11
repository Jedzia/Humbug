echo on
rem ******************************************
rem *                                        *
rem *           LintAllCpp.bat               *
rem *                                        *
rem ******************************************
date < %~dp0\cr.txt
time  < %~dp0\cr.txt
erase c:\linttemp.txt
for  %%i in (*.cpp) DO %comspec% /C %~dp0\LintAllCppHelper.bat %%i %1 %2 %3 %4 %5 %6 %7 %8 %9
rem for  %%i in (*.cpp) DO %comspec% /C c:\lint\lint-nt  -b %~dp0\LintCPP.lnt  "%%i" | %~dp0\EchoAndSave c:\linttemp.txt
%~dp0\jzLintReport < c:\linttemp.txt %~dp0\msgCats.txt
date  < %~dp0\cr.txt
time  < %~dp0\cr.txt
echo on
rem ************ Done **************


