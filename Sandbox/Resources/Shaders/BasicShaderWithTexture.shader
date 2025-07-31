#SHADER VERTEX
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 Color;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	Color = aColor;
	TexCoord = aTexCoord;
};

#SHADER FRAGMENT
#version 460 core
in vec3 Color;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * vec4(Color, 1.0);
};