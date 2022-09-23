#include "Renderer.hpp"

namespace tr
{
    class RenderPrivateImpl
    {
        public:
        void drawLine(const std::int32_t& x0, const std::int32_t& y0,
                  const std::int32_t& x1, const std::int32_t& y1,
                  imageloader::TGAImage& image, const imageloader::TGAColor& color)
        {
            for (float t=0.; t<1.; t+=.01)
            {
                int x = x0 + (x1-x0)*t;
                int y = y0 + (y1-y0)*t;
                image.setColor(x, y, color);
            }
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

        d_ptr->drawLine(x0, y0, x1, y1, image, color);

        return std::nullopt;
    }

    Renderer::~Renderer()
    {

    }

} // namespace tr
