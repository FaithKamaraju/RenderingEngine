#SHADER VERTEX
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat3 normalMatrix;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	FragPos = vec3(model * vec4(aPos, 1.0f));
	Normal = normalMatrix * aNormal;
	TexCoords = aTexCoords;
};

#SHADER FRAGMENT
#version 460 core

struct Material {
	sampler2D diffuseMap;
	sampler2D specularMap;
	float shininess;

};
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
out vec4 FragColor;

uniform vec3 cameraPos;

uniform Material material;
uniform Light light; 

void main()
{
	// ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, TexCoords));

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseMap, TexCoords));

	// specular
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specularMap, TexCoords)) ;

	vec3 result = ambient + diffuse + specular ;

    FragColor = vec4(result, 1.0f);
};