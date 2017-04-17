#version 330 core
out vec4 color;

void main()
{
    
    color = vec4(lightColor * objectColor,1.0f);
}
