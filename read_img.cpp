#include <iostream>
#include <vector>

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "header_files/stb_image.h"
}

// Loads as RGBA... even if file is only RGB
// Feel free to adjust this if you so please, by changing the 4 to a 0.
bool load_image(std::vector<unsigned char>& image, const std::string& filename, int& x, int&y)
{
    int n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 3);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(data, data + x * y * 3);
    }
    stbi_image_free(data);
    return (data != nullptr);
}

void print_pixel_rgb(int x, int y)
{
    std::string filename = "image.png";
    
    int width, height;
    std::vector<unsigned char> image;
    bool success = load_image(image, filename, width, height);
    if (!success)
    {
        std::cout << "Error loading image\n";
        return;
    }
    
    std::cout << "Image width = " << width << '\n';
    std::cout << "Image height = " << height << '\n';
    
    const size_t RGB = 3;
    
    size_t index = RGB * (y * width + x);
    std::cout << "RGB pixel @ x: " << x << ", y: " << y << " " 
              << static_cast<int>(image[index + 0]) << " "
              << static_cast<int>(image[index + 1]) << " "
              << static_cast<int>(image[index + 2]) << '\n';

}