#version 460 core
out vec4 FragColor;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 texCoord;

uniform sampler2D texture_diffuse1;
uniform vec3 objectColor;

uniform vec3 lightPos1;     
uniform vec3 viewPos;

uniform bool blinn;

uniform vec3 spotPos;
uniform vec3 spotDir;
uniform float innerCutOff;
uniform float outerCutOff;
uniform vec3 spotColor;


uniform int lightMode;

void main()
{
    vec3 color = texture(texture_diffuse1, texCoord).rgb * objectColor;
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result;

    if (lightMode == 0)
    {
     
        vec3 lightDir = normalize(lightPos1 - fragPos);

        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diff * color;

        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
        vec3 specular = vec3(1.0) * spec;

        vec3 ambient = 0.5 * color;

        result = ambient + diffuse + specular;
    }
    else if (lightMode == 1)
    {
     
        vec3 lightDir = normalize(spotPos - fragPos);

        float theta = dot(lightDir, normalize(-spotDir));
        float epsilon = innerCutOff - outerCutOff;
        float intensity = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);

        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diff * color * spotColor * 2.0;

        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
        vec3 specular = vec3(1.0) * spec * spotColor * 2.0;

        vec3 ambient = 0.40 * color;

        result = ambient + (diffuse + specular) * intensity;
    }
    else
    {
      
        result = vec3(0.5) * color;
    }

    FragColor = vec4(result, 1.0);
}
