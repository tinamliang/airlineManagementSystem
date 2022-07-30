@echo off

RUNDLL32 PRINTUI.DLL,PrintUIEntry /y /n "HP1B0EC0"
call printJS.bat C:\personal_projects\airline_db\airline_db\ticket.txt

exit /b 0
