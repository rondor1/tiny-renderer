#include "Model.hpp"
#include "point/Point.hpp"

#include <filesystem>
#include <fstream>
#include <string_view>
#include <sstream>
#include <iostream>

namespace tr
{
    class ModelPrivateImpl
    {
        public:
            std::vector<Point3Df> vertices;
            std::vector<std::vector<std::int32_t>> faces;

        std::optional<ErrorCodes> initModel(const std::string_view& filename)
        {
            std::ifstream inputFile(filename.data(), std::ios::in | std::ios::binary);

            if(!inputFile.is_open())
            {
                return ErrorCodes::InvalidReadOperation;
            }

            auto inputDataType = static_cast<char>(inputFile.get());

            while(inputDataType != EOF)
            {

                std::string line;
                std::array<float, 3> verts;
                std::vector<int> f;

                Point3Df pt;
                switch (inputDataType)
                {
                    case 'v':
                        for(auto iter = 0; iter < 3; ++iter)
                        {
                            inputFile >> verts[iter];
                        }
                        pt = {verts[0], verts[1], verts[2]};
                        vertices.push_back(pt);
                        break;
                    case '#':
                            std::getline(inputFile, line);
                            std::cout << line;
                        break;
                    default:
                        break;
                }

                inputDataType = static_cast<char>(inputFile.get());
            }

            return std::nullopt;
        }

        private:
            void readFaces(std::istream& inputFile, std::vector<int>& f)
            {
                int itrash, idx;
                char trash;
                std::string line;
                std::getline(inputFile, line);
                std::istringstream iss(line.c_str());
                iss >> idx >> trash >> itrash >> trash>> itrash;
                idx--;
                std::cout << idx << std::endl;
                f.push_back(idx);
            }

    };

    Model::Model() : d_ptr{new ModelPrivateImpl}
    {

    }

    std::optional<ErrorCodes> Model::load(const std::string_view& filename)
    {
        if(!verifyDirectoryExistence(filename))
        {
            return ErrorCodes::InvalidPath;
        }

        return d_ptr->initModel(filename);
    }

    bool Model::verifyDirectoryExistence(const std::string_view& imagePath)
    {
        //Start of the string + position where '/' is located
        const auto directoryPath = imagePath.substr(0, imagePath.find_last_of('/') + 1);

        return std::filesystem::exists( directoryPath) ? true : std::filesystem::create_directories(directoryPath);
    }

    Model::~Model()
    {

    }
} // namespace tr
