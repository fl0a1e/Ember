#pragma once

#include <string>

namespace Ember {

    class EMBER_API Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void bind() const;
        void unbind() const;
    private:
        
        uint32_t rendererID;
    };

}