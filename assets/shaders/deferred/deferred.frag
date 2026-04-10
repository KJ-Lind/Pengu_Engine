#version 460 core

out vec4 FragColor;

in vec2 TexCoords;
vec3 FragPos;
vec3 Normal;
vec4 FragPosLightSpace;

uniform mat4 lightSpaceMatrix;

uniform vec3 viewPos;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gColorSpec;

uniform sampler2D DepthText; 

struct Light{
    int light_type;
    vec3 color;

    vec3 position;
    vec3 direction;

    float ambientStrength;
    float specularStrength;
    float shininess;

    float radius;
    float cutoff;
    float outerCutoff;

    float constant;
    float linear;
    float quadratic; 

    float shadowSoftness;
};

uniform Light light;

vec3 Calculate_Dir(Light light, vec3 materialDiffuse, float Specular)
{
    //ambient
    vec3 ambient = light.ambientStrength * light.color;

    ambient = ambient * materialDiffuse;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    
    float diff = max(dot(norm, lightDir),0.0);
    vec3 diffuse = diff * materialDiffuse;

    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(norm, halfwayDir), 0.0), light.shininess);
    vec3 specular = light.color * spec * Specular;

    //float shadow = ShadowCalculation(FragPosLightSpace, DepthText, norm, lightDir);

    return (ambient + (diffuse + specular));
}

vec3 Calculate_Point(Light light, vec3 materialDiffuse, float Specular)
{
    //ambient
    vec3 ambient = light.ambientStrength * light.color;
    ambient = ambient * materialDiffuse;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir),0.0);
    vec3 diffuse = diff * materialDiffuse;

    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), light.shininess);
    vec3 specular = light.color * spec * Specular;

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + 
                        light.linear * distance + 
                        light.quadratic * (distance * distance));

    if(distance > light.radius) attenuation = 0.0;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 Calculate_Spot(Light light, vec3 materialDiffuse, float Specular)
{

   //ambient
    vec3 ambient = light.ambientStrength * light.color;
    ambient = ambient * materialDiffuse;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir),0.0);
    vec3 diffuse = diff * materialDiffuse;

    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), light.shininess);
    vec3 specular = light.color * spec * Specular; 

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.cutoff - light.outerCutoff);
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0,1.0);
    diffuse *= intensity;
    specular *= intensity;

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + 
                        light.linear * distance + 
                        light.quadratic * (distance * distance));

    if(distance > light.radius) attenuation = 0.0;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    //float shadow = ShadowCalculation(FragPosLightSpace, DepthText, norm, lightDir);

    return ambient + (diffuse + specular);
}

void main()
{   

    FragPos = texture(gPosition, TexCoords).rgb;
    Normal =  texture(gNormal, TexCoords).rgb;
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);

    vec3 materialDiffuse = texture(gColorSpec, TexCoords).rgb;
    float materialSpecular = texture(gColorSpec, TexCoords).a;

    vec3 result = materialDiffuse * 0.1f;

    if(light.light_type == 0)
    {
        result = Calculate_Dir(light, materialDiffuse, materialSpecular);
    }
    else if(light.light_type == 1)
    {
        result = Calculate_Point(light, materialDiffuse, materialSpecular);
    }
    else if(light.light_type == 2)
    {
        result = Calculate_Spot(light, materialDiffuse, materialSpecular);
    }


    FragColor = vec4(result, 1.0);
}