#pragma once

#include <memory>
#include <optional>
#include <vector>

namespace tr
{

    enum class [[nodiscard]] ErrorCodes
    {
        InvalidPath,
        InvalidReadOperation
    };

    class ModelPrivateImpl;

    class Model
    {
        public:
            Model();
            ~Model();

            std::optional<ErrorCodes> load(const std::string_view& filename = "/home/robert/projects/tiny-renderer/build/african_head.obj");

        private:
            bool verifyDirectoryExistence(const std::string_view& imagePath);

        private:
            std::unique_ptr<ModelPrivateImpl> d_ptr;
    };
} // namespace tr