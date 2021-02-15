@echo off

::Դ�ļ�����
set sourcefile[0]=main

::���ļ����Ŀ¼���ļ���
set EPKFILE=helloworld.epk


:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::�����ļ����Ŀ¼����
set OUTFILE=bin\code
::ϵͳ����Ŀ¼����
set INCLUDEPATH=%GDK_PATH%

::�豸�ļ�Ŀ¼���ļ���
set DDBLIBFILE=%GDK_PATH%\lib\drive.asm
set MODULELIBS=%GDK_PATH%\lib\standard.asl

echo *************** start of precompiler ****%INCLUDEPATH%**********%DDBLIBFILE%**********
set "x=0"
:PrecompileLoop
if not defined sourcefile[%x%] goto :endPrecompileLoop
call set cppfile=%%sourcefile[%x%]%%.cpp
call set dpcfile=%temp%\%%sourcefile[%x%]%%.dpc
dp -DEXTERNC -DCPLUS -I%INCLUDEPATH% %cppfile% %dpcfile%
if not "%errorlevel%"=="0" (goto dperror)
echo precompile file %cppfile% OK!!!
SET /a "x+=1"
goto :PrecompileLoop
:endPrecompileLoop
goto dpcompile
:dperror
echo precompiler error!
pause
exit
:dpcompile
echo precompiler complete!


echo *************** start of cplus ************************
set "x=0"
:cplusLoop
if not defined sourcefile[%x%] goto :endcplusLoop
call set _filename=%%sourcefile[%x%]%%
call set ccfile=%temp%\%%sourcefile[%x%]%%.cc
call set dpcfile=%temp%\%%sourcefile[%x%]%%.dpc
cplus -s%_filename% < %dpcfile% > %ccfile%
if not "%errorlevel%"=="0" (goto cpluserror)
echo cplus file %ccfile% OK!!!
SET /a "x+=1"
goto :cplusLoop
:endcplusLoop
goto cpluscompile
:cpluserror
echo cplus error!
pause
exit
:cpluscompile
echo cplus complete!




echo *************** start of compiler ************************

set "x=0"
:CompileLoop
if not defined sourcefile[%x%] goto :endCompileLoop
call set dpcfile=%temp%\%%sourcefile[%x%]%%.cc
call set asmfile=%temp%\%%sourcefile[%x%]%%.asm
call set cfile=%%sourcefile[%x%]%%.cpp
echo compile file %cfile% %dpcfile% %asmfile%
dc %dpcfile% %asmfile%
echo compile file %cfile% OK!!!
if not "%errorlevel%"=="0" (goto dcerror)
SET /a "x+=1"
goto :CompileLoop
:endCompileLoop
goto dccompile
:dcerror
echo compiler error!
pause
exit
:dccompile
echo compiler complete!




echo *************** start of link ************************
set "x=0"
SET LinkFile=
:LinkLoop
if not defined sourcefile[%x%] goto :endLinkLoop
call set asmfile=%temp%\%%sourcefile[%x%]%%.asm
SET LinkFile=%LinkFile% %asmfile%
SET /a "x+=1"
goto :LinkLoop
:endLinkLoop

dlbc1 -o %OUTFILE% %DDBLIBFILE% %MODULELIBS% %LinkFile%
if not "%errorlevel%"=="0" (goto dlerror)
goto dlcompile
:dlerror
echo link error!
pause
exit
:dlcompile
echo link complete!


echo *************** start of pack ************************
packfile -build bin %EPKFILE%
if not "%errorlevel%"=="0" (goto packerror)
goto packcompile
:packerror
echo pack error!
pause
exit
:packcompile
echo pack complete!


echo all complete!

grey -start %EPKFILE%

exit