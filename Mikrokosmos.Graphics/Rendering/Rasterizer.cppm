module;

#include <algorithm>
#include <cstddef>
#include <memory>
#include <span>

export module Mikrokosmos.Graphics.Rendering.Rasterizer;

import Mikrokosmos.Containers.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Fragment;
import Mikrokosmos.Graphics.Rendering.FragmentStream;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.Texture;
import Mikrokosmos.Mathematics.Algebra.Vector;

using Index = std::size_t;

export namespace mk
{
	class Rasterizer
	{
	public:

		Rasterizer() = default;

		virtual void rasterize(std::span<Vertex> vertexes, FragmentStream& fragmentStream) {};

	};

	class PointRasterizer : public Rasterizer
	{
	public:

		PointRasterizer() = default;

		void rasterize(std::span<Vertex> vertexes, FragmentStream& fragmentStream) override {}

	};

	class LineRasterizer : public Rasterizer
	{
	public:

		LineRasterizer() = default;

		void rasterize(std::span<Vertex> vertexes, FragmentStream& fragmentStream) override
		{
			auto vertexCount = vertexes.size();
			auto iterations = vertexCount > 2 ? vertexCount : vertexCount - 1;
			
			for (Index i = 0; i < iterations; ++i)
			{
				Index j = (i + 1) % vertexCount;
				rasterizeLine(vertexes[i], vertexes[j], fragmentStream);
			}
		}

	private:

		void rasterizeLine(const Vertex& vertex0, const Vertex& vertex1, FragmentStream& fragmentStream)
		{
			bool steep = false;

			Vertex v0 = vertex0;
			Vertex v1 = vertex1;

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
				std::swap(v0, v1);
			}

			int dx = x1 - x0;
			int dy = y1 - y0;
			int derror2 = std::abs(dy) * 2;
			int error2 = 0;
			int y = y0;

			float t = 0.0f;
			float dt = 1.0f / dx;

			for (int x = x0; x <= x1; x++) {
						
				Point2i position;
				auto depth = float{};
				auto color = interpolate(v0.color(), v0.position().w(), v1.color(), v1.position().w(), t);
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

				t += dt;
			}
		}

		template<typename Varying>
		Varying interpolate(Varying v0, float w0, Varying v1, float w1, float t)
		{
			auto alpha = (1.0f - t) / w0;
			auto beta = t / w1;
			return (v0 * alpha + v1 * beta) * (1.0f / (alpha + beta));
		}

	};

	class TriangleRasterizer : public Rasterizer
	{
	public:

		TriangleRasterizer() = default;

		void rasterize(std::span<Vertex> vertexes, FragmentStream& fragmentStream) override 
		{
			rasterizeTriangle(vertexes[0], vertexes[1], vertexes[2], fragmentStream);
		}

	private:

		void rasterizeTriangle(const Vertex& vertex0, const Vertex& vertex1, const Vertex& vertex2, FragmentStream& fragmentStream)
		{

			// Vertex positions.

			Vector3f v0{ vertex0.position() };
			Vector3f v1{ vertex1.position() };
			Vector3f v2{ vertex2.position() };

			// CW -> CCW? Area test?
			auto area = edgeFunction(v0, v1, v2);

			// Find triangle's AABB.
			auto xMin = static_cast<int>(std::min({ v0.x(), v1.x(), v2.x() }));
			auto xMax = static_cast<int>(std::max({ v0.x(), v1.x(), v2.x() }));
			auto yMin = static_cast<int>(std::min({ v0.y(), v1.y(), v2.y() }));
			auto yMax = static_cast<int>(std::max({ v0.y(), v1.y(), v2.y() }));

			// Clip if outside screen?
			
			// Iterate through each pixel inside the triangle's AABB.
			for (auto y = yMin; y <= yMax; ++y)
			{
				for (auto x = xMin; x <= xMax; ++x)
				{
					//Test point.
					Vector3f p{ x + 0.5f, y + 0.5f, 0.0f };

					// Find barycentric coordinates.
					auto w0 = edgeFunction(v1, v2, p);
					auto w1 = edgeFunction(v2, v0, p);
					auto w2 = edgeFunction(v0, v1, p);

					// If pixel is inside triangle...
					if ((w0 >= 0) == (w1 >= 0) && (w1 >= 0) == (w2 >= 0)) // Is this correct?
					{
						w0 /= area;
						w1 /= area;
						w2 /= area;

						auto position = Point2i{x, y};

						auto depth = float{};

						auto color = w0 * vertex0.color() + w1 * vertex1.color() + w2 * vertex2.color();
						//auto z = 1.0f / (w0 * v0.z() + w1 * v1.z() + w2 * v2.z());
						//color *= z;

						auto normal = w0 * vertex0.normal() + w1 * vertex1.normal() + w2 * vertex2.normal();
						
						auto textureCoordinates = Vector2f{};
						
						fragmentStream.emplace_back(position, depth, color, normal, textureCoordinates);
					}
				}
			}
		}

		constexpr float edgeFunction(const Vector3f& a, const Vector3f& b, const Vector3f& c) noexcept
		{
			//return (a.x() - b.x()) * (c.y() - a.y()) - (a.y() - b.y()) * (c.x() - a.x());
			//return (c.x() - a.x()) * (b.y() - a.y()) - (c.y() - a.y()) * (b.x() - a.x());
			return (b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x()); // Is this correct? Can this be used with both CW and CCW windings?
		}

	};

}
