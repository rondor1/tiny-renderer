#include "Model.hpp"


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
            std::ifstream inputFile(filename.data(), std::ios::in);

            if(!inputFile.is_open())
            {
                return ErrorCodes::InvalidReadOperation;
            }

            std::string currentLine{};
            char trash;
            while(std::getline(inputFile, currentLine))
            {
                std::istringstream lineHandler{currentLine};
                if(currentLine.compare(0, 2, "v ") == 0)
                {
                    Point3Df pt;
                    lineHandler >> trash;
                    for(auto i = 0; i < POINTS_3D; ++i)
                    {
                        lineHandler >> pt.points[i];
                    }
                    vertices.push_back(pt);
                }
                if(currentLine.compare(0, 2, "f ")  == 0)
                {
                    std::vector<std::int32_t> _faces;
                    int trashIndex;
                    int currentIndex;
                    lineHandler >> trash;
                    while(lineHandler >> currentIndex >> trash >> trashIndex >> trash>>trashIndex)
                    {
                        --currentIndex;
                        _faces.push_back(currentIndex);
                    }
                    faces.push_back(_faces);
                }
            }

            inputFile.close();
            std::cout << "vertices count : " << vertices.size() << std::endl;
            std::cout << "faces count : " << faces.size() << std::endl;
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

    int Model::numberOfVertices() const {return d_ptr->vertices.size();}
    int Model::numberOfFaces() const {return d_ptr->faces.size();}

    Point3Df Model::vertex(const int& index) const
    {
        return d_ptr->vertices[index];
    }

    std::vector<int> Model::faces(const int& index) const
    {
        return d_ptr->faces[index];
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
