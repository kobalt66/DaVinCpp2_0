#include "ByteCastHelper.h"
#include <algorithm>
#include <array>
#include <bit>
#include <Console.h>
#include <cstring>
#include <stdexcept>

namespace davincpp::davscript
{
template <typename T>
std::vector<uint8_t> ByteCastHelper::nativeToBytes(const T& value)
{
	auto bytes = std::bit_cast<std::array<uint8_t, sizeof(T)>>(value);
	return std::vector<uint8_t>{bytes.begin(), bytes.end()};
}

std::vector<uint8_t> ByteCastHelper::stringToBytes(const std::string& str)
{
	std::vector<uint8_t> bytes;

	for (const char c : str) {
		bytes.push_back(c);
	}

	return bytes;
}

uint32_t ByteCastHelper::bytesToUint32(const uint8_t* bytePtr)
{
	uint32_t value;
	std::memcpy(&value, bytePtr, sizeof(uint32_t));
	return value;
}

int64_t ByteCastHelper::bytesToInt(const uint8_t* bytePtr)
{
	int64_t value;
	std::memcpy(&value, bytePtr, sizeof(int64_t));
	return value;
}

bool ByteCastHelper::bytesToBool(const uint8_t* bytePtr)
{
	bool value;
	std::memcpy(&value, bytePtr, sizeof(bool));
	return value;
}

double ByteCastHelper::bytesToFloat(const uint8_t* bytePtr)
{
	double value;
	std::memcpy(&value, bytePtr, sizeof(double));
	return value;
}

std::string ByteCastHelper::bytesToString(const uint8_t* bytePtr)
{
	std::string str;

	size_t advances = 0;
	while (*(bytePtr + advances) != '\0') {
		str.push_back(static_cast<char>(*(bytePtr + advances)));
		advances++;
	}

	return str;
}

template std::vector<uint8_t> ByteCastHelper::nativeToBytes(const uint32_t& value);
template std::vector<uint8_t> ByteCastHelper::nativeToBytes(const int64_t& value);
template std::vector<uint8_t> ByteCastHelper::nativeToBytes(const bool& value);
template std::vector<uint8_t> ByteCastHelper::nativeToBytes(const double& value);
} // namespace davincpp::davscript
