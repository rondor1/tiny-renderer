#include "Renderer.hpp"

namespace tr
{
    class RenderPrivateImpl
    {
        public:
        void drawLine(std::int32_t& x0, std::int32_t& y0,
                  std::int32_t& x1, std::int32_t& y1,
                  imageloader::TGAImage& image, const imageloader::TGAColor& color)
        {
            auto isLineSteep = false;
            if(isLineSteep = checkIfLineIsSteep(x0, y0, x1, y1); isLineSteep )
            {
                std::swap(x0, x1);
                std::swap(y0, y1);
            }

            if(x0 > x1)
            {
                std::swap(x0, x1);
                std::swap(y0, y1);
            }

            const auto dx = std::abs(x0-x1);
            const auto dy = std::abs(y0-y1);
            auto d = dy*2 - dx;
            auto y = y0;

            for(auto x = x0; x < x1; ++x)
            {
                if(isLineSteep)
                {
                    std::swap(x,y);
                }

                image.setColor(x,y,color);

                if(d > 0)
                {
                    ++y;
                    d = d-2*dx;
                }

                d += 2*dy;
            }
        }

        private:
            bool checkIfLineIsSteep(const std::int32_t& x0, const std::int32_t& y0,
                  const std::int32_t& x1, const std::int32_t& y1)
                  {
                    return std::abs(x0-x1) < std::abs(y0 - y1);
                  }
    };

    Renderer::Renderer() : d_ptr{new RenderPrivateImpl}
    {

    }

    std::optional<RenderingErrorCodes> Renderer::drawLine(std::int32_t&& x0, std::int32_t&& y0,
                  std::int32_t&& x1, std::int32_t&& y1,
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
