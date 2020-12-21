module;

#include <cstddef>
#include <memory>
#include <span>

export module Mikrokosmos.Graphics.Rendering.Rasterizer;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Fragment;
import Mikrokosmos.Graphics.Rendering.FragmentStream;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.Texture;

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
			for (std::size_t i = 0; i < iterations; ++i)
			{
				std::size_t j = (i + 1) % vertexCount;
				rasterizeLine(vertexes[i], vertexes[j], fragmentStream);
			}
		}

	private:

		void rasterizeLine(const Vertex& vertex0, const Vertex& vertex1, FragmentStream& fragmentStream)
		{
			bool steep = false;

			int x0 = static_cast<int>(vertex0.position().x());
			int y0 = static_cast<int>(vertex0.position().y());
			int x1 = static_cast<int>(vertex1.position().x());
			int y1 = static_cast<int>(vertex1.position().y());

			Vertex v0 = vertex0;
			Vertex v1 = vertex1;

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

		void rasterize(std::span<Vertex> vertexes, FragmentStream& fragmentStream) override {}

	};

}
