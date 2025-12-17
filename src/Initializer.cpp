#include "Initializer.hpp"
#include <filesystem>
namespace FS = std::filesystem;
void Init()
{
    if (!FS::exists("data"))
        FS::create_directory("data");
}