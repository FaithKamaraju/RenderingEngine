#SHADER VERTEX
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

layout (std140) uniform Matrices {
	mat4 view;
	mat4 projection;
};

uniform mat4 model;
uniform mat3 normalMatrix;

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

#define MAX_NUM_TOTAL_LIGHTS 20

struct Material {
	sampler2D diffuseMap;
	sampler2D specularMap;
	float shininess;

};
/*struct Light 
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

layout (std140) uniform {
	Light lights[MAX_NUM_TOTAL_LIGHTS];
	int numLights;
}*/

layout (std140) uniform DirectionalLight {
	vec4 dirLightdirection;
    vec4 dirLightambient;
    vec4 dirLightdiffuse;
    vec4 dirLightspecular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
out vec4 FragColor;

uniform vec3 cameraPos;
uniform Material material;
//uniform DirectionalLight dirLight;

void main()
{
	//Directional Light
		// ambient
		vec3 ambient = dirLightambient.xyz * vec3(texture(material.diffuseMap, TexCoords));

		// diffuse
		vec3 norm = normalize(Normal);
		//vec3 lightDir = normalize(dirLight.position - FragPos);
		vec3 lightDir = normalize(-dirLightdirection.xyz);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = dirLightdiffuse.xyz * diff * vec3(texture(material.diffuseMap, TexCoords));

		// specular
		vec3 viewDir = normalize(cameraPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
		vec3 specular = dirLightspecular.xyz * spec * vec3(texture(material.specularMap, TexCoords)) ;

	// Point Lights

	/*for(int i; i < numLights; i++ ){
		ambient += light[i].ambient * vec3(texture(material.diffuseMap, TexCoords));

		// diffuse
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(light[i].position - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		diffuse += light[i].diffuse * diff * vec3(texture(material.diffuseMap, TexCoords));

		// specular
		vec3 viewDir = normalize(cameraPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
		specular += light[i].specular * spec * vec3(texture(material.specularMap, TexCoords)) ;
	}*/

	vec3 result = ambient + diffuse + specular ;

    FragColor = vec4(result, 1.0f);
};