#SHADER VERTEX
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

layout (std140) uniform CameraData {
	mat4 view;
	mat4 projection;
	vec4 position;
};

uniform mat4 model;
uniform mat3 normalMatrix;

out vec3 cameraPos;
out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	FragPos = vec3(model * vec4(aPos, 1.0f));
	Normal = normalMatrix * aNormal;
	TexCoords = aTexCoords;
	cameraPos = position.xyz;
};

#SHADER FRAGMENT
#version 460 core

#define MAX_NUM_TOTAL_LIGHTS 20

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	float shininess;
};

layout (std140) uniform DirectionalLight {
	vec4 dirLightdirection;
    vec4 dirLightambient;
    vec4 dirLightdiffuse;
    vec4 dirLightspecular;
};

struct PointLight {
    vec4 pointLightposition;
    vec4 pointLightambient;
    vec4 pointLightdiffuse;
    vec4 pointLightspecular;
	float pointLightconstant;
    float pointLightlinear;
    float pointLightquadratic;
};

struct SpotLight {
	vec4 spotLightposition;
	vec4 spotLightdirection;
    vec4 spotLightambient;
    vec4 spotLightdiffuse;
    vec4 spotLightspecular;
	float spotLightinnerCutoff;
	float spotLightouterCutoff;
	float spotLightconstant;
    float spotLightlinear;
    float spotLightquadratic;
};

layout (std140) uniform Lights {
	PointLight pointLights[MAX_NUM_TOTAL_LIGHTS];
	SpotLight spotLights[MAX_NUM_TOTAL_LIGHTS];
	int numPointLights;
	int numSpotLights;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
out vec4 FragColor;
in vec3 cameraPos;

uniform Material material;

void main()
{
	//Directional Light
		// ambient
		vec3 ambient = dirLightambient.xyz * vec3(texture(material.texture_diffuse1, TexCoords));

		// diffuse
		vec3 norm = normalize(Normal);
		//vec3 lightDir = normalize(dirLight.position - FragPos);
		vec3 lightDir = normalize(-dirLightdirection.xyz);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = dirLightdiffuse.xyz * diff * vec3(texture(material.texture_diffuse1, TexCoords));

		// specular
		vec3 viewDir = normalize(cameraPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
		vec3 specular = dirLightspecular.xyz * spec * vec3(texture(material.texture_specular1, TexCoords));

		vec3 directionalResult = ambient + diffuse + specular;

	// Point Lights
	vec3 pointResult = vec3(0.0);
	for (int i = 0; i < numPointLights; i++){
		// ambient
		ambient = pointLights[i].pointLightambient.xyz * texture(material.texture_diffuse1, TexCoords).rgb;

		// diffuse
		lightDir = normalize(pointLights[i].pointLightposition.xyz - FragPos);
		diff = max(dot(norm, lightDir), 0.0);
		diffuse = pointLights[i].pointLightdiffuse.xyz * diff * texture(material.texture_diffuse1, TexCoords).rgb;

		// specular
		reflectDir = reflect(-lightDir, norm);
		spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
		specular = pointLights[i].pointLightspecular.xyz * spec * texture(material.texture_specular1, TexCoords).rgb;

		float distance    = length(pointLights[i].pointLightposition.xyz - FragPos);
		float attenuation = 1.0 / (pointLights[i].pointLightconstant + (pointLights[i].pointLightlinear * distance) + (pointLights[i].pointLightquadratic * (distance * distance)));

		vec3 tempResult = ambient + diffuse + specular;
		tempResult *= attenuation;
		pointResult += tempResult;
	}
		

	// Spot Lights
	vec3 spotLightResult = vec3(0.0);
	for (int i = 0; i < numSpotLights; i++){
		// ambient
		ambient = spotLights[i].spotLightambient.xyz * texture(material.texture_diffuse1, TexCoords).rgb;

		// diffuse
		lightDir = normalize(spotLights[i].spotLightposition.xyz - FragPos);

		float theta     = dot(lightDir, normalize(-spotLights[i].spotLightdirection.xyz));
		float epsilon   = spotLights[i].spotLightinnerCutoff - spotLights[i].spotLightouterCutoff;
		//float intensity = clamp((theta - spotLightouterCutoff) / epsilon, 0.0, 1.0);
		float intensity = smoothstep(0.0, 1.0, (theta - spotLights[i].spotLightouterCutoff) / epsilon);

		diff = max(dot(norm, lightDir), 0.0);
		diffuse = spotLights[i].spotLightdiffuse.xyz * diff * texture(material.texture_diffuse1, TexCoords).rgb;

		// specular
		reflectDir = reflect(-lightDir, norm);
		spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
		specular = spotLights[i].spotLightspecular.xyz * spec * texture(material.texture_specular1, TexCoords).rgb;

		float distance    = length(spotLights[i].spotLightposition.xyz - FragPos);
		float attenuation = 1.0 / (spotLights[i].spotLightconstant + (spotLights[i].spotLightlinear * distance) + (spotLights[i].spotLightquadratic * (distance * distance)));

		// we'll leave ambient unaffected so we always have a little light.
		diffuse  *= intensity;
		specular *= intensity;

		vec3 tempResult = ambient + diffuse + specular;
		tempResult *= attenuation;
		spotLightResult += tempResult;
	}
		//
	
	vec3 result = directionalResult + pointResult +  spotLightResult ;

    FragColor = vec4(result, 1.0f);
};