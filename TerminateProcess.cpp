 
#include <iostream>
#include <windows.h>
#include <psapi.h>
 
void TerminateProcessByName(DWORD processId,  std::string processNameToTerminate ) {
	
	HANDLE hProcess = nullptr;
	char processName[MAX_PATH] {};
 
	hProcess = OpenProcess(
		PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		FALSE,
		processId
	);

	GetModuleBaseNameA(
		hProcess,
		0,
		processName,
		sizeof(processName) / sizeof(char)
	);

	std::string name = processName;
	if (name == processNameToTerminate) {
		BOOL res = TerminateProcess(hProcess, -1);
		DWORD error = GetLastError();

		if (res != 0) {
			std::cout << "success terminate" << std::endl;
		}
		else {
			std::cout << error << " - error code" << std::endl;
		}
	}
 
}

int main()
{
 
	DWORD aProcess[2048]{};
	DWORD bytesNeeded = 0;

	BOOL res =  EnumProcesses(
		aProcess,
		sizeof(aProcess),
		&bytesNeeded
	);
	
	size_t totalProcess = bytesNeeded / sizeof(DWORD);
	
	std::string nameToTerminate;
	std::cin >> nameToTerminate;

	for (size_t i = 0; i < totalProcess; i++) {
		TerminateProcessByName(aProcess[i], nameToTerminate);
	}
	
	 

}

