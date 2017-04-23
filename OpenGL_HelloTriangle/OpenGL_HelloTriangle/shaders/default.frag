#version 330 core

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

in vec3 FragPos;
in vec3 Normal;


uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;


out vec4 color;

void main()
{
    // Ambient
//    float ambientStrength = 0.4f;
    vec3 ambient = light.ambient * material.ambient;
    
    // Diffuse
    vec3 norm = normalize(Normal);
    // normalize是转换为单元向量
    vec3 lightDir = normalize(lightPos - FragPos);
    // 点乘计算向量的投影长度，有可能为负，所以如果未负数则置为0
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // 反光强度
    float specularStrength = 0.5f;
    // 视角的单元向量
    vec3 viewDir = normalize(viewPos - FragPos);
    // 灯光的反射viewDir, 向量
    vec3 reflectDir = reflect(normalize(lightDir),norm);
    
    float spec = pow(max(dot(viewDir, reflectDir),0.0),material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    
    vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0f);
}
