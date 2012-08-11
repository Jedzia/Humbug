echo off
rem ******************************************
rem *                                        *
rem *          LintCpp.bat                   *
rem *                                        *
rem ******************************************
rem date /T
rem time /T
date < %~dp0\cr.txt
time  < %~dp0\cr.txt
erase c:\linttemp.txt
REM c:\lint\lint-nt -i"C:\lint" -b c:\lint\LintCPP.lnt  %1 | c:\lint\EchoAndSave c:\linttemp.txt
REM c:\lint\lint-nt -i".\" -i"C:\lint" -b LintMSVC90.lnt  %1 | c:\lint\EchoAndSave c:\linttemp.txt
REM c:\lint\lint-nt -i"C:\lint" -b LintMSVC90.lnt %1 %2 %3 %4 %5 %6 %7 %8 %9 > c:\linttemp.txt
REM pushd "%~dp0"
REM goto exit
REM c:\lint\lint-nt -i"C:\lint" -i%~dp0 -b %~dp0LintMSVC90.lnt %1 %2 %3 %4 %5 %6 %7 %8 %9 | %~dp0\EchoAndSave c:\linttemp.txt
c:\lint\lint-nt -i"C:\lint" -i%~dp0 -b %~dp0LintMSVC90.lnt %1 %2 %3 %4 %5 %6 %7 %8 %9 > c:\linttemp.txt
%~dp0\jzLintReport < c:\linttemp.txt %~dp0\msgCats.txt
rem c:\lint\lint-nt  -b c:\lint\LintCPP.lnt  "%%~fi" 
date < %~dp0\cr.txt
time  < %~dp0\cr.txt
rem date /T
rem time /T
:exit
REM popd
REM echo "%~dp0"
echo on
rem ************ Done **************



