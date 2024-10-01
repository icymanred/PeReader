#include "pch.h"
#include "tempfiles.h"
#include <expected>
#include "../PeReaderLib/framework.h"
#include "../PeReaderLib/gle.h"
const uint8_t validHeader[64] = {
	0x4D, 0x5A, 0x90, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
	0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00,
}   ; // Taken from notepad.exe
//TODO Create actual function for creating and writing to temp file instead of copy and pasting
 
namespace PeReaderTests {
		
	TEST(DosHeader, GenerateAndConsumeValidPe) {
		std::expected<std::wstring, DWORD> TempRes = tempFiles::generateTempFile();
		ASSERT_EQ(TempRes.has_value(), true) << L"Error generating temporary file: " << GetLastErrorAsString(TempRes.error()) << std::endl; 
		std::wcout << TempRes.value().c_str() << L"\n";
		HANDLE fileHandle = CreateFileW(TempRes.value().c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, 3, FILE_ATTRIBUTE_NORMAL, NULL);
		ASSERT_NE(fileHandle, INVALID_HANDLE_VALUE) << L"Couldn't open file: " << GetLastErrorAsString(GetLastError());
		DWORD bytesWritten = 0;
		BOOL writeRes = WriteFile(fileHandle, validHeader, sizeof(validHeader), &bytesWritten, NULL);
		ASSERT_EQ(writeRes, TRUE) << L"Couldn't write to temporary file: " <<  GetLastErrorAsString(GetLastError());
		// CloseHandle(fileHandle);
		std::expected<IMAGE_DOS_HEADER, DWORD> dosReaderRes = PeReader::DosHeader::ExtractDosHeader(TempRes.value().c_str());
		ASSERT_EQ(dosReaderRes.has_value(), true) << L"Error performing dos read: " << GetLastErrorAsString(dosReaderRes.error());
		CloseHandle(fileHandle);
		BOOL RES = DeleteFileW(TempRes.value().c_str());
		ASSERT_EQ(RES, TRUE) << L"Couldn't delete file: " << GetLastErrorAsString(GetLastError());
		
	}
	TEST(DosHeader, GenerateAndConsumeInValidPeSize) {
		std::expected<std::wstring, DWORD> TempRes = tempFiles::generateTempFile();
		ASSERT_EQ(TempRes.has_value(), true) << L"Error generating temporary file: " << GetLastErrorAsString(TempRes.error()) << std::endl;
		std::wcout << TempRes.value().c_str() << L"\n";
		HANDLE fileHandle = CreateFileW(TempRes.value().c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, 3, FILE_ATTRIBUTE_NORMAL, NULL);
		ASSERT_NE(fileHandle, INVALID_HANDLE_VALUE) << L"Couldn't open file: " << GetLastErrorAsString(GetLastError());
		DWORD bytesWritten = 0;
		BOOL writeRes = WriteFile(fileHandle, validHeader, sizeof(validHeader), &bytesWritten, NULL);
		ASSERT_EQ(writeRes, TRUE) << L"Couldn't write to temporary file: " << GetLastErrorAsString(GetLastError());
		// CloseHandle(fileHandle);
		std::expected<IMAGE_DOS_HEADER, DWORD> dosReaderRes = PeReader::DosHeader::ExtractDosHeader(TempRes.value().c_str());
		ASSERT_EQ(dosReaderRes.has_value(), true) << L"Error performing dos read: " << GetLastErrorAsString(dosReaderRes.error());
		CloseHandle(fileHandle);
		BOOL RES = DeleteFileW(TempRes.value().c_str());
		ASSERT_EQ(RES, TRUE) << L"Couldn't delete file: " << GetLastErrorAsString(GetLastError());

	}



}