module;

#include <functional>
#include <map>
#include <memory>
#include <utility>

export module Mikrokosmos.Graphics.Rendering.RasterizerFactory;

import Mikrokosmos.Core.Array;
import Mikrokosmos.Graphics.Color;
import Mikrokosmos.Graphics.Rendering.Primitive;
import Mikrokosmos.Graphics.Rendering.PrimitiveTopology;
import Mikrokosmos.Graphics.Rendering.Rasterizer;
import Mikrokosmos.Graphics.Rendering.RasterizerState;
import Mikrokosmos.Graphics.Rendering.Vertex;
import Mikrokosmos.Graphics.Rendering.VertexStream;
import Mikrokosmos.Mathematics.Geometry.Point;

export namespace mk
{
	class RasterizerFactory
	{
	public:

		RasterizerFactory() = delete;

		static std::unique_ptr<Rasterizer> create(PrimitiveTopology primitiveTopology, RasterizerState rasterizerState)
		{
			auto it = mapping.find({ primitiveTopology, rasterizerState.fillMode });
			if (it != mapping.end()) return it->second();
			else return nullptr;
		}

	private:

		using enum PrimitiveTopology;
		using enum FillMode;

		static inline std::map<
			std::pair<PrimitiveTopology, FillMode>,
			std::function<std::unique_ptr<Rasterizer>()>> mapping
		{
			{ { PointList,     Point     }, []() {return std::make_unique<PointRasterizer>();    } },
			{ { PointList,     Wireframe }, []() {return std::make_unique<PointRasterizer>();    } },
			{ { PointList,     Solid     }, []() {return std::make_unique<PointRasterizer>();    } },

			{ { LineList,      Point     }, []() {return std::make_unique<PointRasterizer>();    } },
			{ { LineList,      Wireframe }, []() {return std::make_unique<LineRasterizer>();     } },
			{ { LineList,      Solid     }, []() {return std::make_unique<LineRasterizer>();     } },

			{ { LineStrip,     Point     }, []() {return std::make_unique<PointRasterizer>();    } },
			{ { LineStrip,     Wireframe }, []() {return std::make_unique<LineRasterizer>();     } },
			{ { LineStrip,     Solid     }, []() {return std::make_unique<LineRasterizer>();     } },

			{ { TriangleList,  Point     }, []() {return std::make_unique<PointRasterizer>();    } },
			{ { TriangleList,  Wireframe }, []() {return std::make_unique<LineRasterizer>();     } },
			{ { TriangleList,  Solid     }, []() {return std::make_unique<TriangleRasterizer>(); } },

			{ { TriangleStrip, Point     }, []() {return std::make_unique<PointRasterizer>();    } },
			{ { TriangleList,  Wireframe }, []() {return std::make_unique<LineRasterizer>();     } },
			{ { TriangleList,  Solid     }, []() {return std::make_unique<TriangleRasterizer>(); } }
		};

	};
}
