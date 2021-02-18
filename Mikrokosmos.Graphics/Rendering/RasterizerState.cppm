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

	enum class CullMode
	{
		None,
		Front,
		Back
	};

	struct RasterizerState
	{
		FillMode fillMode{ FillMode::Solid };
		CullMode cullMode{ CullMode::None  };
	};

}