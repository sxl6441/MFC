declare @bdchardate varchar(8)
declare @sqlName nvarchar(100)

set @bdchardate= convert(char(10),getdate(),112)

--第1步:备份MDS数据库在本地
set @sqlName='backup database MDS to disk=''E:\MDS_10.68.130.81_Backup\MDS_BACKUP'+@bdchardate+'.bak'' ' 
exec(@sqlName)

go
