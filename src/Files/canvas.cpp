
#include <filesystem>
#include <fstream>

#include "canvas.hpp"
#include "Tools/canvas.hpp"
#include "raylib.h"


namespace fs = std::filesystem;

namespace Files
{

// DJB2 Implementation, simple but it works for something small
unsigned long computeHash(const char* bytes, int size)
{
    unsigned long hash = 5381;
    for(int i=0; i<size; ++i)
	{
        hash = ((hash << 5) + hash) + bytes[i]; // hash * 33 + c
    }
    return hash;
}

// Grabs the current canvas an creates a png image from it
bool saveCanvasAsPng(const std::string pathStr, Canvas& c)
{
    fs::path path(pathStr);

    // Validations
    if( fs::is_directory(path) || path.extension() != ".png" )
    {
        return false;
    }

    // Then the whole image exporting is up to raylib
    ExportImage(c._exportImage(), path.c_str());
    return true;
}

// Saves file as an .rdraw file
void saveAsRdraw(const std::string pathStr, CanvasData& cData)
{
    std::ofstream file(pathStr, std::ios::binary);

    // Extra properties
    file.write(reinterpret_cast<const char*>(&cData.props), sizeof(CanvasProperties));
    file.write(reinterpret_cast<const char*>(&cData.layerAmount), sizeof(size_t));
    file.write(reinterpret_cast<const char*>(&cData.layerSize), sizeof(size_t));

    // For each layer
    for(size_t i=0; i<cData.layerAmount; ++i)
    {
        file.write(reinterpret_cast<const char*>(cData.layerData[i].data), cData.layerSize);
    }
}

CanvasData loadRdrawFile(const std::string pathStr)
{
    fs::path path(pathStr);
    if( !fs::exists(path))
    {
        return CanvasData();
    }
    if(fs::is_directory(path) || path.extension() != ".rdraw")
    {
        return CanvasData();
    }
    std::ifstream file(pathStr, std::ios::binary);

    CanvasData cData;
    file.read(reinterpret_cast<char*>(&cData.props), sizeof(CanvasProperties));
    file.read(reinterpret_cast<char*>(&cData.layerAmount), sizeof(size_t));
    file.read(reinterpret_cast<char*>(&cData.layerSize), sizeof(size_t));

    // For each layer
    for(size_t i=0; i<cData.layerAmount; ++i)
    {
        
        // Why not `new`? I just wated to use the same methods that raylib uses internally, just in case
        unsigned char* data = (unsigned char*)RL_CALLOC(cData.layerSize, sizeof(unsigned char));
        
        // This whole thing works over the idea that every layer has the same size 
        // due to having the same dimensions and format
        file.read(reinterpret_cast<char*>(data), cData.layerSize);

        cData.layerData.emplace_back(
            Image{
                data, 
                cData.props.width, cData.props.height, 
                1, cData.props.format
        });
    }

    // C++ trivia (yey!): Passing cData by copy will invalidate the data
    //
    // CanvasData destructor automatically cleans the image data 
    // If you return it by copy, all the data pointer in the images will be invalid
    // and everything will crash and be so sad
    // 
    // The solutions are either not use the automatic clean-up or use move semantics
    // (Muchas gracias theCherno)
    return std::move(cData);
}

}