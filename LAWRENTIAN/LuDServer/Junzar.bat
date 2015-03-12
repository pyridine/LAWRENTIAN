@echo off
echo Junzar opened! Do not fear arg0!
echo docxname is %1
echo directory of docx is %2
::this should change the dir to the folder where the docxs roam.
CD %2
::now just call 7z.
7z e %~1.docx -o%~1
exit 0
