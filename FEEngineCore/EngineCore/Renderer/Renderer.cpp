
#include "Renderer.h"
#include <iostream>
#include <memory>

#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EngineCore/Renderer/Constants.h"
#include "EngineCore/GameplayStatics/EngineStatics.h"
#include "EngineCore/Renderer/OpenGL/Shader.h"
#include "EngineCore/Renderer/Mesh/Model.h"
#include "EngineCore/Renderer/Lights/PointLight.h"

namespace FE {

    Renderer* createRenderer()
    {
        return new Renderer();
    }

    int Renderer::render() 
    {


    return 0;
    }
}
