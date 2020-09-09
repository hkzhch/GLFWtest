#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
//layout (location = 1) in vec3 aColor;
//layout (location = 2) in vec2 aTexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float emissionMove;
//uniform mat4 transform;
//out vec3 ourColor;
out vec2 texCoord;
out vec3 FragPos;
out vec3 Normal;
out vec2 emissionTexCoord;
//out vec3 ourPosition;
void main()
{
    //gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //ourPosition = aPos;
    //ourColor = aColor;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal; 
    gl_Position = projection * view * vec4(FragPos, 1.0);
    texCoord = aTexCoord;
    emissionTexCoord = vec2(aTexCoord.x,aTexCoord.y + emissionMove);
}