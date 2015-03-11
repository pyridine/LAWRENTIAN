@ECHO ON
::Remember,
::%0 always refers to working directory, 
::unless a shift happens to set %0 to a valid directory

::determine docxname::
set docxname=%1
IF %2==end GOTO dxend
:dxloop
shift
set docxname=%docxname% %1
if %2==end GOTO dxend
GOTO dxloop
:dxend
SHIFT
SHIFT

::determine docxdir::
set docxdir=%1
IF %2==end GOTO drend
:drloop
shift
set docxdir=%docxdir% %1
if %2==end GOTO drend
GOTO drloop
:drend
SHIFT
SHIFT



echo docxname is "%docxname%"
echo directory of docx is "%docxdir%"
::this should change the dir to the folder where the docxs roam.
@ECHO ON
CD "%docxdir%"
::now just call 7z.
set docxstention="%docxname%.docx"
7z e %docxstention% -o"%docxname%"
exit
