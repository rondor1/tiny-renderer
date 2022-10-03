#include "Logger.hpp"
#include "Renderer.hpp"
#include "tgaImage/TGAImageLoad.hpp"
#include "point/Point.hpp"

#include "Model.hpp"

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


    tr::Model m;
    m.load(argv[1]);

    render->drawModel(m, *image);

    storeImage->storeImage(argv[2], *image);

    utils::logger::infoMessage("Image sucessfully stored!");

    return 0;
}
