#include "Renderer.hpp"

namespace tr
{
    class RenderPrivateImpl
    {
        public:
        std::optional<RenderingErrorCodes> drawLine(const std::int32_t& x0, const std::int32_t& y0,
                  const std::int32_t& x1, const std::int32_t& y1,
                  imageloader::TGAImage& image, const imageloader::TGAColor& color)
        {
            return std::nullopt;
        }
    };

    Renderer::Renderer() : d_ptr{new RenderPrivateImpl}
    {

    }

    std::optional<RenderingErrorCodes> Renderer::drawLine(const std::int32_t& x0, const std::int32_t& y0,
                  const std::int32_t& x1, const std::int32_t& y1,
                  imageloader::TGAImage& image, const imageloader::TGAColor& color)
    {
        if(x0 < 0 || x0 > image.width() ||
           y0 < 0 || y0 > image.height() ||
           x1 < 0 || x1 > image.width() ||
           y1 < 0 || y1 > image.height())
        {
            return RenderingErrorCodes::IndexOutOfRange;
        }

        return d_ptr->drawLine(x0, y0, x1, y1, image, color);
    }

    Renderer::~Renderer()
    {

    }
} // namespace tr
