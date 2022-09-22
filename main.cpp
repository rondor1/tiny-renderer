#include "Renderer.hpp"
#include "tgaImage/TGAImageLoad.hpp"
int main(int argv, char** argc)
{
    auto image = new imageloader::TGAImage(1000, 1000, imageloader::Format::RGB, false);
    auto storeImage = std::make_unique<imageloader::TGAImageLoader>();
    std::unique_ptr render = std::make_unique<tr::Renderer>();
    render->drawLine(100, 100, 500, 500, *image);
    storeImage->storeImage("/home/robert/image.tga", *image);

    delete image;
    return 0;
}