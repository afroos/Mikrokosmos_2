module;

export module Mikrokosmos.Graphics.Rendering.RasterizerState;

export namespace mk
{

	enum class FillMode
	{
		Point,
		Wireframe,
		Solid
	};

	struct RasterizerState
	{
		FillMode fillMode{ FillMode::Solid };
	};

}