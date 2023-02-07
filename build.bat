@ECHO off

SET PROJECTDIR=%cd%
SET OUTDIR=%PROJECTDIR%\out

IF NOT EXIST %OUTDIR% MKDIR %OUTDIR%

IF "%1"=="clean" (
   DEL %OUTDIR%\*
   GOTO :EOF
)

PUSHD %OUTDIR%

SET DEBUGOPTS=/std:c++20 /Zi /MT /EHsc
SET OPTIMOPTS=/std:c++20 /O2

:: cl.exe %DEBUGOPTS% %PROJECTDIR%\bitmanip.cc
:: cl.exe %DEBUGOPTS% %PROJECTDIR%\bst.cc
:: cl.exe %DEBUGOPTS% %PROJECTDIR%\cirq.cc
cl.exe %DEBUGOPTS% %PROJECTDIR%\linked-list.cc
:: cl.exe %DEBUGOPTS% %PROJECTDIR%\monotonic-stack.cc
:: cl.exe %DEBUGOPTS% %PROJECTDIR%\sliding-window.cc
:: cl.exe %DEBUGOPTS% %PROJECTDIR%\substr-searches.cc
:: cl.exe %DEBUGOPTS% %PROJECTDIR%\sudoku-solver.cc
:: cl.exe %OPTIMOPTS% %PROJECTDIR%\tail-recursion.cc
:: cl.exe %DEBUGOPTS% %PROJECTDIR%\xor.cc

POPD
