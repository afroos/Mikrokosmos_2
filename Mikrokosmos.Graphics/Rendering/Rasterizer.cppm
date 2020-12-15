module;

export module Mikrokosmos.Graphics.Rendering.Rasterizer;


import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Primitive;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexStream;

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

		void rasterize(const Primitive& primitive) override {}

	};

	class TriangleRasterizer : public Rasterizer
	{
	public:

		TriangleRasterizer() = default;

		void rasterize(const Primitive& primitive) override {}

	};

}
