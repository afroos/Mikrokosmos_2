#include <fstream>
#include <sstream>
#include <vector>

import Mikrokosmos.Applications;
import Mikrokosmos.Graphics;
import Mikrokosmos.Mathematics.Algebra;
import Mikrokosmos.Mathematics.Geometry;

class Mesh : public mk::WindowApplication
{
public:

    std::shared_ptr<mk::SFMLSwapChainPresenter> presenter;
    std::shared_ptr<mk::Device> device;
    std::shared_ptr<mk::SwapChain> swapChain;
    std::shared_ptr<mk::RenderTargetView> renderTargetView;
    std::shared_ptr<mk::DeviceContext> context;

    const float radius = 5.0f;
    float angle = 0.0f;
    mk::Matrix44f model = mk::Matrix44f::Identity();
    mk::Matrix44f projection = mk::Orthographic(2.0f, 2.0f, 0.0f, radius * 2.0f);

    Mesh()
		:
        mk::WindowApplication{ {.name = "Mesh", .windowSize = {800, 800}} }
	{

	}

	void initialize() noexcept override
	{

        presenter = std::make_shared<mk::SFMLSwapChainPresenter>(_window);

        device = std::make_shared<mk::Device>();

        swapChain = device->createSwapChain(_width, _height, presenter.get());

        renderTargetView = device->createRenderTargetView(&swapChain->backBuffer());

        context = device->immediateContext();

        std::vector<mk::Vertex> vertexes;
        std::vector<mk::Index> indexes;

        std::vector<mk::Vector4f> positions;
        std::vector<mk::Vector3f> normals;

        std::ifstream in;
        in.open("african_head.obj", std::ifstream::in);
        if (in.fail()) return;
        std::string line;
        while (!in.eof())
        {
            std::getline(in, line);
            std::istringstream iss(line.c_str());
            char trash;
            if (!line.compare(0, 2, "v "))
            {
                iss >> trash;
                float v;
                mk::Vector4f position;
                for (int i = 0; i < 3; i++)
                {
                    iss >> v;
                    position[i] = v * 0.99f;
                }
                position[3] = 1.0f;

                positions.push_back(position);
            }
            else if (!line.compare(0, 3, "vn ")) {
                iss >> trash >> trash;
                mk::Vector3f n;
                for (int i = 0; i < 3; i++) iss >> n[i];
                normals.push_back(normalize(n));
            }
            else if (!line.compare(0, 2, "f "))
            {
                int itrash, idx;
                iss >> trash;
                while (iss >> idx >> trash >> itrash >> trash >> itrash)
                {
                    idx--; // in wavefront obj all indices start at 1, not zero
                    indexes.push_back(idx);
                }
            }
        }

        for (std::size_t i = 0; i < positions.size(); i++)
        {
            mk::Vertex vertex;
            vertex.position() = positions[i];
            vertex.color() = mk::Color{ rand() % 256, rand() % 256, rand() % 256 };
            vertex.normal() = normals[i];
            vertexes.push_back(vertex);
        }

        auto vertexBuffer = device->createVertexBuffer(vertexes);

        auto indexBuffer = device->createIndexBuffer(indexes);

        context->inputAssemblerStage()->setPrimitiveTopology(mk::PrimitiveTopology::TriangleList);
        context->inputAssemblerStage()->setVertexBuffer(vertexBuffer);
        context->inputAssemblerStage()->setIndexBuffer(indexBuffer);

        auto vertexShader = device->createVertexShader("Basic");

        context->vertexShaderStage()->setShader(vertexShader);

        context->rasterizerStage()->setState(mk::RasterizerState{ .fillMode = mk::FillMode::Wireframe, .cullMode = mk::CullMode::None });
        context->rasterizerStage()->setViewport({ 0.0, 0.0, (float)_width, (float)_height });

        auto fragmentShader = device->createFragmentShader("");

        context->fragmentShaderStage()->setShader(fragmentShader);
        context->fragmentShaderStage()->shader()->_ambientColor = mk::Color::Green();
        context->fragmentShaderStage()->shader()->_ambientIntensity = 1.0f;

        context->outputMergerStage()->setRenderTargetView(*renderTargetView);
	}

    void draw() noexcept override
    {
        renderTargetView->clear(mk::Color::Black());

        angle += 0.01f;
        float camX = std::sin(angle) * radius;
        float camZ = std::cos(angle) * radius;

        auto view = mk::LookAt(mk::Point3f{ camX, 0.0f, camZ }, mk::Point3f{ 0.0f, 0.0f, 0.0f }, mk::Vector3f{ 0.0, 1.0, 0.0 });

        context->vertexShaderStage()->shader()->_modelViewProjection = projection * view * model;

        context->fragmentShaderStage()->shader()->_lightDirection = mk::Vector4f{ 0.0f, 0.0f, 1.0f, 0.0f };

        context->drawIndexed(context->inputAssemblerStage()->indexBuffer()->size(), 0, 0);

        swapChain->present();
    }
};

int main()
{
    Mesh application;
	return application.run();
}