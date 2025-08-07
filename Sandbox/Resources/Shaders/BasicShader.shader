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

layout (std140) uniform DirectionalLight {
	vec4 dirLightdirection;
    vec4 dirLightambient;
    vec4 dirLightdiffuse;
    vec4 dirLightspecular;
};

layout (std140) uniform PointLight {
    vec4 pointLightposition;
    vec4 pointLightambient;
    vec4 pointLightdiffuse;
    vec4 pointLightspecular;
	float pointLightconstant;
    float pointLightlinear;
    float pointLightquadratic;
};

/*layout (std140) uniform {
	PointLight lights[MAX_NUM_TOTAL_LIGHTS];
	int numLights;
}*/



in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
out vec4 FragColor;

uniform vec3 cameraPos;
uniform Material material;

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
	// ambient
	vec3 pointambient = pointLightambient.xyz * texture(material.diffuseMap, TexCoords).rgb;

	// diffuse
	vec3 pointLightDir = normalize(pointLightposition.xyz - FragPos);
	float pointLightdiff = max(dot(norm, pointLightDir), 0.0);
	vec3 pointdiffuse = pointLightdiffuse.xyz * pointLightdiff * texture(material.diffuseMap, TexCoords).rgb;

	// specular
	vec3 pointLightreflectDir = reflect(-pointLightDir, norm);
	float pointLightspec = pow(max(dot(pointLightreflectDir, viewDir), 0.0), material.shininess);
	vec3 pointspecular = pointLightspecular.xyz * pointLightspec * texture(material.specularMap, TexCoords).rgb;

	float distance    = length(pointLightposition.xyz - FragPos);
	float attenuation = 1.0 / (pointLightconstant + (pointLightlinear * distance) + (pointLightquadratic * (distance * distance)));

	pointambient *= attenuation;
	pointdiffuse *= attenuation;
	pointspecular *= attenuation;
	//ambient + diffuse + specular
	vec3 result = pointambient + pointdiffuse + pointspecular;

    FragColor = vec4(result, 1.0f);
};