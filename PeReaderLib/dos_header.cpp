
#include "dos_header.h"

 std::expected<IMAGE_DOS_HEADER, DWORD> PeReader::DosHeader::ExtractDosHeader(std::wstring Path)
{
	HANDLE File = CreateFileW(Path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (File == INVALID_HANDLE_VALUE) {
		return std::unexpected(GetLastError());
	}
	char dosBuf[dosHeaderSz] = { 0 };
	DWORD bytesRead = 0;
	BOOL readResult = ReadFile(File, reinterpret_cast<LPVOID>(dosBuf), dosHeaderSz, &bytesRead, NULL);
	CloseHandle(File);
	if (readResult == FALSE) {
		return std::unexpected(GetLastError());
	}
	IMAGE_DOS_HEADER header = *reinterpret_cast<IMAGE_DOS_HEADER*>(dosBuf);
	if (bytesRead == dosHeaderSz && header.e_magic == IMAGE_DOS_SIGNATURE) {
		return header;





	}
	return std::unexpected(ERROR_MRM_INVALID_FILE_TYPE);

}


