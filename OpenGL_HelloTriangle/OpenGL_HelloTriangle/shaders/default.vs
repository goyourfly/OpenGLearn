#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

// 每一个面的垂线
out vec3 Normal;
// 每一个点所在的面的位置(我们假设一个点和距离它很近的点形成一个面)
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    // 计算每一个点在经过Model转换后的实际位置，由于我们只关心它在世界中的位置，所以不考虑view和projection，既物体所在的位置不受观察者的影响,这一点很重要
    FragPos = vec3(model * vec4(position,1.0f));
    Normal = mat3(transpose(inverse(model))) * normal;
}
