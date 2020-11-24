module;

#include <algorithm>
#include <cmath>

export module Mikrokosmos.Graphics.Rendering.Rasterizer;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Mathematics.Geometry.Point;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.ColorBuffer;

export namespace mk
{
	class Rasterizer
	{
	public:

        Rasterizer() = default;

		void drawLine(const Point2i& p0, const Point2i& p1, const Color& color, ColorBuffer& framebuffer)
		{
            bool steep = false;

            auto x0 = p0.x();
            auto y0 = p0.y();
            auto x1 = p1.x();
            auto y1 = p1.y();

            if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
                std::swap(x0, y0);
                std::swap(x1, y1);
                steep = true;
            }
            if (x0 > x1) {
                std::swap(x0, x1);
                std::swap(y0, y1);
            }
            int dx = x1 - x0;
            int dy = y1 - y0;
            int derror2 = std::abs(dy) * 2;
            int error2 = 0;
            int y = y0;
            for (int x = x0; x <= x1; x++) {
                if (steep) {
                    framebuffer.at(y, x) = color;
                }
                else {
                    framebuffer.at(x, y) = color;
                }
                error2 += derror2;
                if (error2 > dx) {
                    y += (y1 > y0 ? 1 : -1);
                    error2 -= dx * 2;
                }
            }
		}

	private:

	};
}