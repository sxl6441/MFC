on error resume Next
Dim NewTargetPath,NewWorkingDirectory,Strlnk,WshShell,oShellLink,fs,fl
Dim Desktop,currdir,creodir
Dim Creo2Exe

Set fs=WScript.CreateObject("Scripting.FileSystemObject")
Set WshShell = WScript.CreateObject("WScript.Shell")
currdir=fs.getfolder(".")
'选择CREO的安装目录
Const MY_COMPUTER=&H11&
Const WINDOW_HANDLE=0
Const OPTIONS=0
'设置我的电脑为根目录
Set objShell=CreateObject("Shell.Application")
Set objFolder=objShell.BrowseForFolder(WINDOWS_HANDLE,"选择Creo安装目录,例" & vbCrLf & "Creo4.0 D:\PTC\Creo 4.0\M060",OPTIONS,NULL)
If objFolder Is Nothing Then 
	msgbox "Creo的安装目录选择错误，安装失败退出"
	Wscript.Quit
End If
Set objFolderItem=objFolder.Self
objPath=objFolderItem.Path
If objPath="" Then
	msgbox "Creo的安装目录选择错误，安装失败退出"
	Wscript.Quit
Else
	creodir=objPath
End If

Creo2Exe=creodir & "\Parametric\bin\parametric.exe"
if(fs.fileExists(Creo2Exe)) then
	NewTargetPath=Creo2Exe
Else
	msgbox "安装失败，选择的目录:" & creodir & "可能不是Creo的安装目录"
	set fs=nothing
	set WshShell=nothing
	Wscript.Quit
End If 

dim pro_fl,dat_fl
pro_fl=currdir & "\ProcessFixture\Config.pro"
dat_fl=currdir & "\ProcessFixture\ProcessFixture.dat"
dim dat_file,pro_file
dat_file = "protkdat " & dat_fl
pro_file = creodir & "\Common Files\text\config.pro"
'删除文件
if (fs.fileExists(pro_fl)) then
fs.DeleteFile(pro_fl)
end if
'写开始config.pro
set fl=fs.opentextfile(pro_fl,2,true)
fl.write ("protkdat " & dat_fl & vbCrLf)
fl.close 
'写结束onfig.pro
'删除文件
if (fs.fileExists(dat_fl)) then
fs.DeleteFile(dat_fl)
end if
'写开始ProcessFixture.dat
set fl=fs.opentextfile(dat_fl,2,true)
fl.write ("name ProcessFixture" & vbCrLf)
fl.write ("startup dll" & vbCrLf)
fl.write ("exec_file " & currdir & "\ProcessFixture\dll\ProcessFixture.dll" & vbCrLf)
fl.write ("text_dir " & currdir & "\ProcessFixture\text" & vbCrLf)
fl.write ("allow_stop TRUE" & vbCrLf)
fl.write ("end" & vbCrLf)
fl.close
'写结束ProcessFixture.dat


Desktop = WshShell.SpecialFolders("Desktop")
Strlnk = "\Creo_ProcessFixture.lnk"     '快捷方式文件
if (fs.fileExists(pro_file)) then
	NewWorkingDirectory = currdir & "\ProcessFixture\workdir\" 'Creo工作目录
else
	NewWorkingDirectory = currdir & "\ProcessFixture\" 'Creo工作目录
end if
set oShellLink = WshShell.CreateShortcut(Desktop & Strlnk)
oShellLink.IconLocation = creodir & "\Parametric\install\nt\parametric.ico"
oShellLink.TargetPath = NewTargetPath
oShellLink.WorkingDirectory = NewWorkingDirectory
oShellLink.Save

'复制POSTGRES_dll文件
fs.CopyFile  currdir & "\ProcessFixture\postgres_dll\*.*","c:\windows\sysnative\",true


'在TEXT目录下config.pro中增加自动起动内容
Dim arrFileLines()
dim f2
if (fs.fileExists(pro_file)) then
	set f2 = fs.OpenTextFile(pro_file, 1, false) '第二个参数 ForReading:1/ForWriting:2/ForAppending:8，第三个参数表示目标文件不存在时是否创建
	dim line_text
	find =false
	i = 0
	Do Until f2.atEndOfStream
		line_text=f2.ReadLine() '从当前位置向后读取直到遇到换行符（不读取换行符），并将当前位置移动到下一行的第一个字符，注意：无参数
		pos=InStr(ucase(line_text),ucase("ProcessFixture.dat"))
		if pos>0 and  line_text<>"" then
			find=true
		else
			Redim Preserve arrFileLines(i)
			arrFileLines(i) = line_text
			i = i + 1
		end if
	loop
	f2.Close()
	set f2 = nothing
	if find=true and Ubound(arrFileLines)>1 then'找到了要新重写文件，过滤原有已注册的说明行
		'msgbox "find"
		set f2 = fs.OpenTextFile(pro_file, 2, false)
		For l = 0 to Ubound(arrFileLines) Step 1
			f2.write (arrFileLines(l) & vbCrLf)
		Next	
		f2.write (dat_file & vbCrLf)
		f2.Close()
		set f2 = nothing
	else'没找到在后面写一行就可以了
		'msgbox " no find"
		set f2 = fs.OpenTextFile(pro_file, 8, false) 
		f2.write (vbCrLf)
		f2.write (dat_file & vbCrLf)
		f2.Close()
		set f2 = nothing
	end if
end if
'释放
set fs=nothing
set WshShell=nothing
WScript.Quit
