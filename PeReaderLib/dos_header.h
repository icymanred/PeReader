#include <string>
#include <expected>
#include <Windows.h>
#pragma once
constexpr DWORD dosHeaderSz = sizeof(IMAGE_DOS_HEADER);
namespace PeReader {
	namespace DosHeader {


		std::expected<IMAGE_DOS_HEADER, DWORD> ExtractDosHeader(std::wstring Path);

	}
}
		
	