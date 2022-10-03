#pragma once

#include <cstdint>
#include <memory>
#include <optional>


#include "Model.hpp"
#include "tgaImage/TGAImage.hpp"
#include "point/Point.hpp"

namespace tr
{
    enum class [[nodiscard]] RenderingErrorCodes
    {
        IndexOutOfRange
    };

    class RenderPrivateImpl;

    class Renderer
    {
        public:
            Renderer();
            ~Renderer();

            std::optional<RenderingErrorCodes> drawModel(const Model& model, imageloader::TGAImage& image);

            std::optional<RenderingErrorCodes> drawLine(Point2Di& p0, Point2Di& p1,
                  imageloader::TGAImage& image, const imageloader::TGAColor& color = {255,255,255,0});

            std::optional<RenderingErrorCodes> drawLine(std::int32_t& x0, std::int32_t& y0,
                  std::int32_t& x1, std::int32_t& y1,
                  imageloader::TGAImage& image, const imageloader::TGAColor& color = {255,255,255,0});

            std::optional<RenderingErrorCodes> drawTriangle(Point2Di& p0, Point2Di& p1, Point2Di& p2,
                  imageloader::TGAImage& image, const imageloader::TGAColor& color = {255,255,255,0});

        private:
            std::unique_ptr<RenderPrivateImpl> d_ptr;
    };
} // namespace tr
