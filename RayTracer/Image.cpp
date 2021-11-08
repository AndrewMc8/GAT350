#include "Image.h"
#include "Renderer.h"
#include <iostream>
#include <fstream>

Image::~Image()
{
    
}

Image::Image(const std::string& filename, uint8_t alpha)
{
    Load(filename, alpha);
}

bool Image::Load(const std::string& filename, uint8_t alpha)
{
    std::ifstream stream(filename, std::ios::binary);
    if (stream.fail())
    {
        std::cout << "Error: Cannot open file: " << filename << std::endl;
        return false;
    }

    uint8_t header[54];
    stream.read((char*)header, 54);

    uint16_t id = *((uint16_t*)(header));
    if (id != 'MB')
    {
        std::cout << "Error: Invalid file format: " << filename << std::endl;
        return false;
    }

    colorBuffer.width = *((int*)(&header[18]));   
    colorBuffer.height = *((int*)(&header[22]));

    //int pitch = colorBuffer.width * sizeof(color_t);

    colorBuffer.pitch = colorBuffer.width * sizeof(color_t);
    colorBuffer.data = new uint8_t[colorBuffer.height * colorBuffer.pitch];

    uint16_t bitsPerPixel = *((uint16_t*)(&header[28]));
    uint16_t bytesPerPixel = bitsPerPixel/8;

    size_t size = colorBuffer.width * colorBuffer.height * bytesPerPixel;
    uint8_t* data = new uint8_t[size];

    stream.read((char*)data, size);

    for (int i = 0; i < colorBuffer.width * colorBuffer.height; i++)
    {
        color_t color;

        // colors in bmp data are stored (BGR)
        int index = i * bytesPerPixel;
        color.b = data[index];
        color.g = data[index + 1];
        color.r = data[index + 2];
        color.a = alpha;

        ((color_t*)(colorBuffer.data))[i] = color;
    }

    delete[] data;
}

void Image::Flip()
{
    // set the pitch (width * number of bytes per pixel)
    colorBuffer.pitch = colorBuffer.width * sizeof(color_t);

    // create temporary line to store data
    uint8_t* temp = new uint8_t[colorBuffer.pitch];

    for (int i = 0; i < colorBuffer.height / 2; i++)
    {
        uint8_t* line1 = &((colorBuffer.data)[i * colorBuffer.pitch]);
        uint8_t* line2 = &((colorBuffer.data)[((colorBuffer.height - 1) - i) * colorBuffer.pitch]);
        memcpy(temp, line1, colorBuffer.pitch);
        memcpy(line1, line2, colorBuffer.pitch);
        memcpy(line2, temp, colorBuffer.pitch);
    }
    delete[] temp;

}
