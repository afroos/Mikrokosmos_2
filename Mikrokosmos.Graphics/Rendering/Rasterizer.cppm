module;

#include <cstddef>
#include <memory>

export module Mikrokosmos.Graphics.Rendering.Rasterizer;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Fragment;
import Mikrokosmos.Graphics.Rendering.FragmentStream;
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

		virtual void rasterize(Primitive& primitive, FragmentStream& fragmentStream) {};

	};

	class PointRasterizer : public Rasterizer
	{
	public:

		PointRasterizer() = default;

		void rasterize(Primitive& primitive, FragmentStream& fragmentStream) override {}

	};

	class LineRasterizer : public Rasterizer
	{
	public:

		LineRasterizer() = default;

		void rasterize(Primitive& primitive, FragmentStream& fragmentStream) override
		{
			auto vertexCount = primitive.vertexCount();
			auto iterations = vertexCount > 2 ? vertexCount : vertexCount - 1;
			for (std::size_t i = 0; i < iterations; ++i)
			{
				std::size_t j = (i + 1) % vertexCount;
				rasterizeLine(primitive.vertex(i), primitive.vertex(j), fragmentStream);
			}
		}

	private:

		void rasterizeLine(const Vertex& v0, const Vertex& v1, FragmentStream& fragmentStream)
		{
			bool steep = false;

			auto x0 = static_cast<int>(v0.position().x());
			auto y0 = static_cast<int>(v0.position().y());
			auto x1 = static_cast<int>(v1.position().x());
			auto y1 = static_cast<int>(v1.position().y());

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
				
				auto position = Point2i{};
				auto depth = float{};
				auto color = v0.color();
				auto normal = Vector3f{};
				auto textureCoordinates = Vector2f{};
				
				if (steep) 
				{
					position = {y, x};	
				}
				else 
				{
					position = {x, y};	
				}

				error2 += derror2;
				if (error2 > dx) {
					y += (y1 > y0 ? 1 : -1);
					error2 -= dx * 2;
				}

				fragmentStream.emplace_back(position, depth, color, normal, textureCoordinates);
			}
		}

	};

	class TriangleRasterizer : public Rasterizer
	{
	public:

		TriangleRasterizer() = default;

		void rasterize(Primitive& primitive, FragmentStream& fragmentStream) override {}

	};

}
