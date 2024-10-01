#include "gle.h"

std::wstring GetLastErrorAsString(DWORD er)
{

	if (er == 0) {
		return std::wstring(L"No error passed in");
	}
	LPWSTR buf = 0;
	DWORD res = FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		er,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&buf,
		0,
		NULL

	);
	if (res == 0 or buf == 0) {
		return std::wstring(L"Couldn't find error");
	}
	std::wstring retv = std::wstring(buf);
	LocalFree(buf);
	return retv;


	
}
