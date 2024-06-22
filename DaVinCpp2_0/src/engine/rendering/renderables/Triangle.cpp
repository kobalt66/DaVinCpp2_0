#include "Triangle.h"

namespace davincpp
{
	Triangle::Triangle(
        glm::vec2 basePosition, 
        glm::vec2 position2, 
        glm::vec2 position3, 
        glm::vec4 color
    )
		: Renderable(basePosition, color),
		m_Position2(position2),
		m_Position3(position3)
	{ }


	void Triangle::onRender(FrameBuffer& frameBuffer) const
	{
        // Source: https://web.archive.org/web/20050408192410/http://sw-shader.sourceforge.net/rasterizer.html

        const int Y1 = (int)glm::round(16.0f * m_Position.y);
        const int Y2 = (int)glm::round(16.0f * m_Position2.y);
        const int Y3 = (int)glm::round(16.0f * m_Position3.y);

        const int X1 = (int)glm::round(16.0f * m_Position.x);
        const int X2 = (int)glm::round(16.0f * m_Position2.x);
        const int X3 = (int)glm::round(16.0f * m_Position3.x);

        const int DX12 = X1 - X2;
        const int DX23 = X2 - X3;
        const int DX31 = X3 - X1;

        const int DY12 = Y1 - Y2;
        const int DY23 = Y2 - Y3;
        const int DY31 = Y3 - Y1;

        const int FDX12 = DX12 << 4;
        const int FDX23 = DX23 << 4;
        const int FDX31 = DX31 << 4;

        const int FDY12 = DY12 << 4;
        const int FDY23 = DY23 << 4;
        const int FDY31 = DY31 << 4;

        int minx = (std::min(X1, std::min(X2, X3)) + 0xF) >> 4;
        int maxx = (std::max(X1, std::max(X2, X3)) + 0xF) >> 4;
        int miny = (std::min(Y1, std::min(Y2, Y3)) + 0xF) >> 4;
        int maxy = (std::max(Y1, std::max(Y2, Y3)) + 0xF) >> 4;

        const int q = 8;

        minx &= ~(q - 1);
        miny &= ~(q - 1);

        int C1 = DY12 * X1 - DX12 * Y1;
        int C2 = DY23 * X2 - DX23 * Y2;
        int C3 = DY31 * X3 - DX31 * Y3;

        if (DY12 < 0 || (DY12 == 0 && DX12 > 0)) C1++;
        if (DY23 < 0 || (DY23 == 0 && DX23 > 0)) C2++;
        if (DY31 < 0 || (DY31 == 0 && DX31 > 0)) C3++;

        for (int y = miny; y < maxy; y += q)
        {
            for (int x = minx; x < maxx; x += q)
            {
                int x0 = x << 4;
                int x1 = (x + q - 1) << 4;
                int y0 = y << 4;
                int y1 = (y + q - 1) << 4;

                bool a00 = C1 + DX12 * y0 - DY12 * x0 > 0;
                bool a10 = C1 + DX12 * y0 - DY12 * x1 > 0;
                bool a01 = C1 + DX12 * y1 - DY12 * x0 > 0;
                bool a11 = C1 + DX12 * y1 - DY12 * x1 > 0;
                int a = (a00 << 0) | (a10 << 1) | (a01 << 2) | (a11 << 3);

                bool b00 = C2 + DX23 * y0 - DY23 * x0 > 0;
                bool b10 = C2 + DX23 * y0 - DY23 * x1 > 0;
                bool b01 = C2 + DX23 * y1 - DY23 * x0 > 0;
                bool b11 = C2 + DX23 * y1 - DY23 * x1 > 0;
                int b = (b00 << 0) | (b10 << 1) | (b01 << 2) | (b11 << 3);

                bool c00 = C3 + DX31 * y0 - DY31 * x0 > 0;
                bool c10 = C3 + DX31 * y0 - DY31 * x1 > 0;
                bool c01 = C3 + DX31 * y1 - DY31 * x0 > 0;
                bool c11 = C3 + DX31 * y1 - DY31 * x1 > 0;
                int c = (c00 << 0) | (c10 << 1) | (c01 << 2) | (c11 << 3);

                if (a == 0x0 || b == 0x0 || c == 0x0) continue;

                if (a == 0xF && b == 0xF && c == 0xF)
                {
                    for (int iy = 0; iy < q; iy++)
                    {
                        for (int ix = x; ix < x + q; ix++)
                        {
                            frameBuffer.setPixel(ix, y + iy, m_Color);
                        }
                    }
                }
                else
                {
                    int CY1 = C1 + DX12 * y0 - DY12 * x0;
                    int CY2 = C2 + DX23 * y0 - DY23 * x0;
                    int CY3 = C3 + DX31 * y0 - DY31 * x0;

                    for (int iy = y; iy < y + q; iy++)
                    {
                        int CX1 = CY1;
                        int CX2 = CY2;
                        int CX3 = CY3;

                        for (int ix = x; ix < x + q; ix++)
                        {
                            if (CX1 > 0 && CX2 > 0 && CX3 > 0)
                            {
                                frameBuffer.setPixel(ix, iy, m_Color);   // Blue
                            }

                            CX1 -= FDY12;
                            CX2 -= FDY23;
                            CX3 -= FDY31;
                        }

                        CY1 += FDX12;
                        CY2 += FDX23;
                        CY3 += FDX31;
                    }
                }
            }
        }
	}
}
