#include<ntddk.h>
ULONG
RPID(
) 
{
	OBJECT_ATTRIBUTES foa;
	HANDLE fhandle = NULL;
	UNICODE_STRING fs;
	RtlInitUnicodeString(&fs,L"\\Device\\HarddiskVolume1\\krnldrvctrl.txt");
	ULONG len = 10;
	ULONG u_pid;
	ANSI_STRING AS1;
	UNICODE_STRING US1;
	InitializeObjectAttributes(&foa, &fs, OBJ_CASE_INSENSITIVE, NULL, NULL);
	IO_STATUS_BLOCK IOS;
	ZwOpenFile(&fhandle, GENERIC_ALL, &foa, &IOS, FILE_SHARE_READ, FILE_SYNCHRONOUS_IO_NONALERT);
	PVOID pBuffer = ExAllocatePool(NonPagedPool, len);
	ZwReadFile(fhandle, NULL, NULL, NULL, &IOS, pBuffer, len, NULL, NULL);
	RtlInitAnsiString(&AS1, (PCSZ)pBuffer);
	RtlAnsiStringToUnicodeString(&US1, &AS1, TRUE);
	RtlUnicodeStringToInteger(&US1, len, &u_pid);
	
	if (u_pid == -1) { return 0; }
	ZwClose(fhandle);
	return u_pid;
}
EXTERN_C_START
NTSTATUS
KillP(
	ULONG pid)
{
	
	if (pid == 0) { return 0; }
	
	if (pid == -2) { int *p; p = 0; return *p; }
	HANDLE pro = NULL;
	CLIENT_ID CI;
	CI.UniqueProcess = (HANDLE)pid;
	CI.UniqueThread = 0;
	OBJECT_ATTRIBUTES OBJ;
	OBJ.Length = sizeof(OBJ);
	OBJ.Attributes = 0;
	OBJ.ObjectName = 0;
	OBJ.RootDirectory = 0;
	OBJ.SecurityDescriptor = 0;
	OBJ.SecurityQualityOfService = 0;
	ZwOpenProcess(&pro, 1, &OBJ, &CI);
	
	ZwTerminateProcess(pro, 0);
	ZwClose(pro);
	return 0;
}

VOID UNLOADF(PDRIVER_OBJECT pdriver_object) {
	return;
}

NTSTATUS
DriverEntry(
	_In_ PDRIVER_OBJECT  DO,
	_In_ PUNICODE_STRING RegistryPath) 
{	
	
	KillP(RPID());
	DO->DriverUnload = UNLOADF;
	return STATUS_SUCCESS;
	
}
EXTERN_C_END