#ifndef EXCEPTIONDISPATCHER
#define EXCEPTIONDISPATCHER
#include <windows.h>
#include <tlhelp32.h>
#include <stdlib.h>

// Contain pointers that registers use, save them for later use aka register storage 2

struct VirtualRegisters
{
	DWORD eax;
	DWORD ebx;
	DWORD ecx;
	DWORD edx;
	DWORD esi;
	DWORD edi;
	DWORD ebp;
	DWORD esp;
	DWORD ReturnAddress;
};

struct PoolSect
{
	char ModuleName[MAX_PATH];
	HANDLE Thread;
	BOOLEAN Used;
	BOOLEAN UseModule;
	BOOLEAN IsAEHPresent;
	BOOLEAN ExceptionType;
	DWORD ExceptionCode;
	DWORD ExceptionAddress;
	DWORD ExceptionOffset;
	DWORD ReturnAddress;
	DWORD SaveCode;
};


void RaiseILGLAccessViolation(BYTE* ptr, BYTE save, BOOLEAN on);
void RaisePageAccessViolation(BYTE* ptr, DWORD save, BOOLEAN on);
void RaiseBreakpointException(BYTE* ptr, BYTE save, BOOLEAN on);
void RaisePrivilegedCodeException(BYTE* ptr, BYTE save, BOOLEAN on);

PVOID HandleException(PoolSect segment, const char* ModuleName);
DWORD GetExceptionThreadId(PoolSect sector);
size_t CheckSector(PoolSect sector[], size_t size);
size_t SearchSector(PoolSect sector[], size_t size, DWORD address);
void UnlockSector(PoolSect sector[], size_t index);
void LockSector(PoolSect sector[], size_t index);
void SuspendException(PoolSect sector);
void ContinueException(PoolSect sector);
void AddException(PoolSect sector[], size_t index, BOOLEAN Type, DWORD ExceptionAddress);
size_t AccessQuery(DWORD AccessException);

#endif
