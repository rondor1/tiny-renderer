#include "Logger.hpp"
#include "Renderer.hpp"
#include "tgaImage/TGAImageLoad.hpp"
#include "point/Point.hpp"

int main(int argc, char** argv)
{
    utils::logger::setup("info");
    utils::logger::infoMessage("Starting renderer...");

    if(argc <= 2 && argv ==nullptr)
    {
        utils::logger::setup("error");
        utils::logger::errorMessage("Invalid number of arguments provided! Terminating...");
        return -1;
    }

    std::unique_ptr render = std::make_unique<tr::Renderer>();

    utils::logger::infoMessage("Renderer initialized; Proceeding with the creation of the blank image...");

    auto image = std::make_unique<imageloader::TGAImage>(1000, 1000, 3,imageloader::Format::RGB, false );

    if(image.get() == nullptr)
    {
        utils::logger::setup("error");
        utils::logger::errorMessage("Failed to create image in RAM! Terminating...");
        return -1;
    }

    auto storeImage = std::make_unique<imageloader::TGAImageLoader>();

    if(storeImage.get() == nullptr)
    {
        utils::logger::setup("error");
        utils::logger::errorMessage("Failed to create image handler! Terminating...");
        return -1;
    }

    utils::logger::infoMessage("Setup done! Starting rendering...");

    if (auto result = render->drawLine(100, 100, 500, 500, *image); result.has_value() && result.value() == tr::RenderingErrorCodes::IndexOutOfRange) {
        utils::logger::setup("error");
        utils::logger::errorMessage("Invalid points for line provided!");
    }

    if (auto result = render->drawLine(200, 100, 600, 500, *image, {255,0,0,0}); result.has_value() && result.value() == tr::RenderingErrorCodes::IndexOutOfRange) {
        utils::logger::setup("error");
        utils::logger::errorMessage("Invalid points for line provided!");
    }

    if (auto result = render->drawLine(200, 100, 100, 500, *image, {0,255,0,0}); result.has_value() && result.value() == tr::RenderingErrorCodes::IndexOutOfRange) {
        utils::logger::setup("error");
        utils::logger::errorMessage("Invalid points for line provided!");
    }

    if (auto result = render->drawLine(400, 100, 100, 500, *image, {0,0,255,0}); result.has_value() && result.value() == tr::RenderingErrorCodes::IndexOutOfRange) {
        utils::logger::setup("error");
        utils::logger::errorMessage("Invalid points for line provided!");
    }

    tr::Point2Di p0{100, 100};
    tr::Point2Di p1{500, 500};

    if(auto result = render->drawLine(p0, p1, *image, {255,128,128,0}); result.has_value() && result.value() == tr::RenderingErrorCodes::IndexOutOfRange) {
        utils::logger::setup("error");
        utils::logger::errorMessage("Invalid points for line provided!");
    }


    utils::logger::infoMessage("Rendering finished... Starting with image saving...");

    auto result = storeImage->storeImage(argv[1], *image);

    if(std::holds_alternative<imageloader::ErrorCodes>(result))
    {
        utils::logger::setup("error");
        utils::logger::errorMessage("Failed to store image at:" + std::string(argv[1]));
        return -1;
    }

    utils::logger::infoMessage("Image sucessfully stored!");

    return 0;
}
