#version 330 core
out vec4 FragColor;

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

#define NR_POINT_LIGHTS 1

in vec3 fragPos;
in vec3 fragNormal;
in vec2 texCoord;

uniform vec4 objectColor;
uniform sampler2D textureSample;
uniform vec3 viewPos;
uniform Material material;
uniform PointLight pointLights[NR_POINT_LIGHTS];

// function prototypes
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 color);

void main()
{    
    // properties
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec4 color = texture(textureSample, texCoord) * objectColor;
    
    vec4 result = vec4(0.0);
    // phase 2: point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, fragPos, viewDir, color);    
    
    FragColor = result;
}

// calculates the color when using a point light.
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 color)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
  vec3 halfwayDir = normalize(lightDir + viewDir);  
  float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * color.rgb * material.ambient;
    vec3 diffuse = light.diffuse * diff * color.rgb * material.diffuse;
    vec3 specular = light.specular * spec * color.rgb * material.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    return vec4(result, color.a);
}
