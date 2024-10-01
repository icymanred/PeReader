#pragma once
#include <Windows.h>
#include <expected>
#include <string>

const wchar_t* prefix = L"Pet";
const int pathSize = MAX_PATH + 1;
namespace tempFiles {
	// Make sure to close handle then delete file in that order
	std::expected<std::wstring,DWORD> generateTempFile() {
		
		std::wstring tmpPath(pathSize, u8'\0');
		DWORD pathResult = GetTempPath2W(pathSize, (LPWSTR)tmpPath.c_str());
		if (pathResult == 0) {
			return std::unexpected(GetLastError());

		}


		std::wstring tmpFileName(pathSize, u8'\0');
		UINT fileNameResult = GetTempFileNameW(tmpPath.c_str(), prefix, 1, (LPWSTR)tmpFileName.c_str());
		if (fileNameResult == 0) {
			return std::unexpected(GetLastError());
		}
		HANDLE hopefullyFile = CreateFileW((LPWSTR)tmpFileName.c_str(), GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, 1, FILE_ATTRIBUTE_TEMPORARY, NULL);
		if (hopefullyFile == INVALID_HANDLE_VALUE) {
			return std::unexpected(GetLastError());

		}





		CloseHandle(hopefullyFile);
		return tmpFileName;
	}
	
}
