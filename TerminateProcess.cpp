#include <iostream>
#include <windows.h>
#include <psapi.h>
 
bool TerminateProcessByName(DWORD processId, const std::wstring& processNameToTerminate ) {
	
	HANDLE hProcess = nullptr;
	std::wstring processName(MAX_PATH, L'0');
 
	hProcess = OpenProcess(
		PROCESS_ALL_ACCESS,
		TRUE,
		processId
	);
	if (hProcess) {
		DWORD nameSize = GetModuleBaseName(
			hProcess,
			0,
			&processName[0],
			processName.size()
		);

		processName.resize(nameSize);
		if (processName == processNameToTerminate) {
			BOOL isProcTerminate = TerminateProcess(hProcess, -1);
			DWORD errorCode = GetLastError();

			if (isProcTerminate) {
				return true;
			}
			else {
				std::cerr << errorCode << " - error code" << std::endl;
				return false;
			}
		}
	}
	return false;
 
}

int main(int argc, wchar_t* argv[])
{
 
	DWORD aProcess[4096]{};
	DWORD bytesNeeded = 0;

	BOOL res =  EnumProcesses(
		aProcess,
		sizeof(aProcess),
		&bytesNeeded
	);
		if (!res) {
			return -1;
		}

		 

	size_t totalProcess = bytesNeeded / sizeof(DWORD);
	for (size_t i = 0; i < totalProcess; i++) {
		if (TerminateProcessByName(aProcess[i], argv[1])) {
			return 0;
			
		}
	}
	

}

