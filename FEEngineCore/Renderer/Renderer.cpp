
#include "Renderer.h"
#include <iostream>
#include <memory>

#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer/Constants.h"
#include "EngineCore/GameplayStatics/EngineStatics.h"
#include "Renderer/OpenGL/Shader.h"
#include "Renderer/Mesh/Model.h"
#include "Renderer/Lights/PointLight.h"

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
