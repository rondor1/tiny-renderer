#include "Logger.hpp"
#include "Renderer.hpp"
#include "tgaImage/TGAImageLoad.hpp"

int main(void)
{

    utils::logger::setup("debug");
    utils::logger::debugMessage("Starting renderer...");
    std::unique_ptr render = std::make_unique<tr::Renderer>();

    auto image = std::make_unique<imageloader::TGAImage>(1000, 1000, 3,imageloader::Format::RGB, false );
    auto storeImage = std::make_unique<imageloader::TGAImageLoader>();

    if (auto result = render->drawLine(100, 100, 500, 500, *image); result.has_value() && result.value() == tr::RenderingErrorCodes::IndexOutOfRange) {
        utils::logger::setup("error");
        utils::logger::errorMessage("Invalid points for line provided!");
    }

    storeImage->storeImage("/home/robert/image.tga", *image);

    return 0;
}