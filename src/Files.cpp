#include "Files.hpp"
#include "canvas.hpp"
#include "raylib.h"


#include <cstddef>
#include <filesystem>
#include <fstream>


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
void saveCanvasAsPng(const std::string pathStr, Canvas& c)
{
    fs::path path(pathStr);

    // Validations
    if( fs::is_directory(path) || path.extension() != ".png" )
    {
        return;
    }

    // Then the whole image exporting is up to raylib
    ExportImage(c._exportImage(), path.c_str());
}

// Saves file as an .rdraw file
void saveCanvasAsRdraw(const std::string pathStr, Canvas& c)
{
    fs::path path(pathStr);
    
    if( fs::is_directory(path) || path.extension() != ".rdraw")
    {
        return;
    }
    std::ofstream file(pathStr, std::ios::binary);

    CanvasData cData = c._getData();
    
    // Extra properties
    file.write(reinterpret_cast<const char*>(&cData.props), sizeof(CanvasProperties));

    file.write(reinterpret_cast<const char*>(cData.layerAmount), sizeof(size_t));

    // For each layer
    for(size_t i=0; i<cData.layerAmount; ++i)
    {
        // Write layer size
        file.write(reinterpret_cast<const char*>(cData.bytesPerlayer[i]), sizeof(size_t));
        // Write layer data
        file.write(reinterpret_cast<const char*>(cData.layerData[i]), cData.bytesPerlayer[i]);
    }
}

CanvasData loadRdrawFile(const std::string pathStr)
{
    fs::path path(pathStr);
    
    std::ifstream file(pathStr, std::ios::binary);

    CanvasData cData;
    
    file.read(reinterpret_cast<char*>(&cData.props), sizeof(CanvasProperties));
    file.read(reinterpret_cast<char*>(cData.layerAmount), sizeof(size_t));
}

}