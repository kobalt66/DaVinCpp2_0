#pragma once

namespace davincpp
{
	constexpr int R = 0;
	constexpr int G = 1;
	constexpr int B = 2;
	constexpr int A = 3;

	constexpr float MAX_COLOR_VALUE = 255.f;

	/// TODO: Find a more suffisticated solution for this hardcoded mess...
#ifdef _WIN32
	constexpr const char* BASE_DIR = "D:\\C++\\DaVinCpp 2_0\\DaVinCpp2_0\\DaVinCpp2_0\\";
	constexpr const char* TEST_ENV = "D:\\C++\\DaVinCpp 2_0\\DaVinCpp2_0\\TestEnv\\";
#else
	constexpr const char* BASE_DIR = "/home/lephobix/CLionProjects/DaVinCpp2_0/DaVinCpp2_0/";
	constexpr const char* TEST_ENV = "/home/lephobix/CLionProjects/DaVinCpp2_0/TestEnv";
#endif

	constexpr uint32_t DEFAULT_RESOLUTION_WIDTH = 1200;
	constexpr uint32_t DEFAULT_RESOLUTION_HEIGHT = 720;
	constexpr uint32_t DEFAULT_PIXEL_SIZEX = 4;
	constexpr uint32_t DEFAULT_PIXEL_SIZEY = 4;
	constexpr uint32_t MIN_FRAMEBUFFER_SIZEX = 1;
	constexpr uint32_t MIN_FRAMEBUFFER_SIZEY = 1;
}
