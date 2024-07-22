#pragma once

namespace davincpp
{
	constexpr const int R = 0;
	constexpr const int G = 1;
	constexpr const int B = 2;
	constexpr const int A = 3;

	constexpr const float MAX_COLOR_VALUE = 255.f;

	/// TODO: Find a more suffisticated solution for this hardcoded mess...
#ifdef _WIN32
	constexpr const char* BASE_DIR = "D:\\C++\\DaVinCpp 2_0\\DaVinCpp2_0\\DaVinCpp2_0\\";
#else
	constexpr const char* BASE_DIR = "/home/lephobix/CLionProjects/DaVinCpp2_0/DaVinCpp2_0/";
#endif
}
