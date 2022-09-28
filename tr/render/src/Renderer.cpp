#include "Renderer.hpp"

#include <algorithm>
#include <tuple>

#include "Logger.hpp"

namespace tr
{
    class RenderPrivateImpl
    {
        public:
        void drawLine(std::int32_t& x0, std::int32_t& y0,
                  std::int32_t& x1, std::int32_t& y1,
                  imageloader::TGAImage& image, const imageloader::TGAColor& color)
        {

            const auto differenceX = std::abs(x1 - x0);
            auto incrementStepX = x0 < x1 ? 1 : -1;
            const auto differenceY = -std::abs(y1 - y0);
            auto incrementStepY = y0 < y1 ? 1 : -1;
            auto error = differenceX + differenceY;

            auto x = x0;
            auto y = y0;


            while(x != x1 || y != y1)
            {
                image.setColor(x, y, color);

                std::tie(x,y) = calculateNextPoint(x, y, differenceX, differenceY,
                                                   incrementStepX, incrementStepY, error);
            }
        }

        void drawTriangle(Point2Di& p0, Point2Di& p1, Point2Di& p2,
                  imageloader::TGAImage& image, const imageloader::TGAColor& color)
        {
            if(p0.y > p1.y)
            {
                std::swap(p0.x, p1.x);
                std::swap(p0.y, p1.y);
            }
            if(p0.y > p2.y)
            {
                std::swap(p0.x, p2.x);
                std::swap(p0.y, p2.y);
            }
            if(p1.y > p2.y)
            {
                std::swap(p1.x, p2.x);
                std::swap(p1.y, p2.y);
            }

            drawLine(p0.x, p0.y, p1.x, p1.y, image, color);
            drawLine(p1.x, p1.y, p2.x, p2.y, image, color);
            drawLine(p2.x, p2.y, p0.x, p0.y, image, color);
        }

        private:
            std::tuple<int, int> calculateNextPoint(std::int32_t& x,std::int32_t& y,
                                                    const std::int32_t& differenceX, const std::int32_t& differenceY,
                                                    std::int32_t& incrementStepX,std::int32_t& incrementStepY,
                                                    std::int32_t& incrementalError)
            {
                auto doubleError = incrementalError << 1;

                if(doubleError >= differenceY)
                {
                    incrementalError += differenceY;
                    x += incrementStepX;
                }

                if(doubleError <= differenceX)
                {
                    incrementalError += differenceX;
                    y += incrementStepY;
                }

                return {x,y};
            }
    };

    Renderer::Renderer() : d_ptr{new RenderPrivateImpl}
    {

    }

    std::optional<RenderingErrorCodes> Renderer::drawLine(Point2Di& p0, Point2Di& p1,
                  imageloader::TGAImage& image, const imageloader::TGAColor& color)
    {
        if(p0.x < 0 || p0.x > image.width() ||
           p0.y < 0 || p0.y > image.height() ||
           p1.x < 0 || p1.x > image.width() ||
           p1.y < 0 || p1.y > image.height())
        {
            return RenderingErrorCodes::IndexOutOfRange;
        }

        d_ptr->drawLine(p0.x, p0.y, p1.x, p1.y, image, color);

        return std::nullopt;
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

    std::optional<RenderingErrorCodes> Renderer::drawTriangle(Point2Di& p0, Point2Di& p1, Point2Di& p2,
                  imageloader::TGAImage& image, const imageloader::TGAColor& color)
    {
        if(p0.x < 0 || p0.x > image.width() ||
           p0.y < 0 || p0.y > image.height() ||
           p1.x < 0 || p1.x > image.width() ||
           p1.y < 0 || p1.y > image.height() ||
           p2.x < 0 || p2.x > image.width() ||
           p2.y < 0 || p2.y > image.height())
        {
            return RenderingErrorCodes::IndexOutOfRange;
        }

        d_ptr->drawTriangle(p0, p1, p2, image, color);

        return std::nullopt;
    }

    Renderer::~Renderer()
    {

    }

} // namespace tr
