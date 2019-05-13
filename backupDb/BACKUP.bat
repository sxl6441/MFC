sqlcmd -S WANGYONGLING-PC\SQL2005 -E -i E:\bakupMDS.sql

sqlcmd -S WANGYONGLING-PC\MDS -E -i E:\bakupMDSPOW.sql

forfiles /P E:\MDS_10.68.130.81_Backup /M *.bak /d 0 /c "cmd /c C:\rar.exe a @path.rar @path"

forfiles /P E:\MDS_10.68.130.81_Backup /M *.bak.rar /d 0 /c "cmd /c copy /y @path \\10.26.40.34\MDS_10.68.130.81_backup2"

forfiles /P E:\MDS_10.68.130.81_Backup /M *.bak /d -10 /c "cmd /c del @path"

forfiles /P E:\MDS_10.68.130.81_Backup /M *.bak.rar /d -100 /c "cmd /c del @path"
