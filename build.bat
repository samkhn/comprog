@ECHO off

SET PROJECTDIR=%cd%
SET OUTDIR=%PROJECTDIR%\out

IF NOT EXIST %OUTDIR% MKDIR %OUTDIR%

IF "%1"=="clean" (
   DEL %OUTDIR%\*
   GOTO :EOF
)

PUSHD %OUTDIR%

SET DEBUGOPTS=/std:c++17 /Zi /MT /EHsc
SET OPTIMOPTS=/std:c++17 /O2

REM cl.exe %DEBUGOPTS% %PROJECTDIR%\bitmanip.cpp
REM cl.exe %DEBUGOPTS% %PROJECTDIR%\cirq.cpp
cl.exe %DEBUGOPTS% %PROJECTDIR%\graph.cpp
REM cl.exe %DEBUGOPTS% %PROJECTDIR%\linked-list.cpp
REM cl.exe %DEBUGOPTS% %PROJECTDIR%\trie.cpp

REM cl.exe %DEBUGOPTS% %PROJECTDIR%\monotonic-stack.cpp
REM cl.exe %DEBUGOPTS% %PROJECTDIR%\sliding-window.cpp
REM cl.exe %DEBUGOPTS% %PROJECTDIR%\substr-search.cpp
REM cl.exe %DEBUGOPTS% %PROJECTDIR%\two-heaps.cpp
REM cl.exe %DEBUGOPTS% %PROJECTDIR%\xor.cpp

REM TODO

REM cl.exe %DEBUGOPTS% %PROJECTDIR%\todo_dp.cpp
REM cl.exe %DEBUGOPTS% %PROJECTDIR%\todo_intervals.cpp
REM cl.exe %DEBUGOPTS% %PROJECTDIR%\todo_kway-merge-sort.cpp

REM Maybe later

REM cl.exe %DEBUGOPTS% %PROJECTDIR%\todo_rbtree.cpp
REM cl.exe %DEBUGOPTS% %PROJECTDIR%\todo_suffix-tree.cpp
REM cl.exe %DEBUGOPTS% %PROJECTDIR%\todo_sudoku.cpp

POPD
