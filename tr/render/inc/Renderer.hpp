#pragma once

#include <cstdint>
#include <memory>
#include <optional>

#include "tgaImage/TGAImage.hpp"

namespace tr
{
    enum class RenderingErrorCodes
    {
        IndexOutOfRange
    };

    class RenderPrivateImpl;

    class Renderer
    {
        public:
            Renderer();
            ~Renderer();

            std::optional<RenderingErrorCodes> drawLine(const std::int32_t& x0, const std::int32_t& y0,
                  const std::int32_t& x1, const std::int32_t& y1,
                  imageloader::TGAImage& image, const imageloader::TGAColor& color = {255,255,255,0});

        private:
            std::unique_ptr<RenderPrivateImpl> d_ptr;
    };
} // namespace tr
