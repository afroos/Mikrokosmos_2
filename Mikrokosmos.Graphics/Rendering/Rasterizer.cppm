module;

#include <cstddef>

export module Mikrokosmos.Graphics.Rendering.Rasterizer;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Primitive;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexStream;
import Mikrokosmos.Graphics.Rendering.Texture;

export namespace mk
{
	class Rasterizer
	{
	public:

		Rasterizer() = default;

		virtual void rasterize(const Primitive& primitive) {};

	};

	class PointRasterizer : public Rasterizer
	{
	public:

		PointRasterizer() = default;

		void rasterize(const Primitive& primitive) override {}

	};

	class LineRasterizer : public Rasterizer
	{
	public:

		LineRasterizer() = default;

		void rasterize(const Primitive& primitive) override
		{
			auto vertexCount = primitive.vertexCount();
			for (std::size_t i = 0; i < vertexCount; ++i) 
			{
				std::size_t j = (i + 1) % vertexCount;
				/*drawLine(vertices[i].px, vertices[i].py,
					vertices[i].depth, vertices[i].varyings,
					vertices[j].px, vertices[j].py,
					vertices[j].depth, vertices[j].varyings,
					shader, framebuffer);*/
			}
		}

	private:
		void drawLine(const Vertex& v0, const Vertex& v1, Texture& target)
		{
			/*bool steep = false;

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
					target.at(y, x) = color;
				}
				else {
					target.at(x, y) = color;
				}
				error2 += derror2;
				if (error2 > dx) {
					y += (y1 > y0 ? 1 : -1);
					error2 -= dx * 2;
				}
			}*/
		}

	};

	class TriangleRasterizer : public Rasterizer
	{
	public:

		TriangleRasterizer() = default;

		void rasterize(const Primitive& primitive) override {}

	};

}
