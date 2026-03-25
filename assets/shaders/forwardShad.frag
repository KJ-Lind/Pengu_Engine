#version 460 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;

uniform vec3 viewPos;

uniform bool u_hasAlbedoMap;
uniform vec4 u_albedoColor;

uniform bool u_hasNormalMap;
uniform bool u_hasRoughnessMap;
uniform float u_roughness;
uniform float u_metallic;

uniform sampler2D u_albedoMap;
uniform sampler2D u_normalMap;
uniform sampler2D u_roughnessMap;
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

float ShadowCalculation(vec4 fragPosLightSpace, sampler2D shadowMap, vec3 normal, vec3 lightDir)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    
    float closestDepth = texture(DepthText, projCoords.xy).r; 
    float shadow = 0.0;
    float samples = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    
    float currentDepth = projCoords.z;
    
    shadow = currentDepth > closestDepth  ? 1.0 : 0.0;
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);  

    for(float x = -light.shadowSoftness; x <= light.shadowSoftness; x += 1.0)
    {
        for(float y = -light.shadowSoftness; y <= light.shadowSoftness; y += 1.0)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
            samples++;
        }
    }
    shadow /= samples;

    if(projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}

vec3 Calculate_Dir(Light light, vec3 materialDiffuse, vec3 materialSpecular)
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
    vec3 specular = light.specularStrength * spec * materialSpecular;

    float shadow = ShadowCalculation(FragPosLightSpace, DepthText, norm, lightDir);

    return (ambient + (1.0 - shadow) * (diffuse + specular));
}

vec3 Calculate_Point(Light light, vec3 materialDiffuse, vec3 materialSpecular)
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
    vec3 specular = light.specularStrength * spec * materialSpecular;

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

vec3 Calculate_Spot(Light light, vec3 materialDiffuse, vec3 materialSpecular)
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
    vec3 specular = light.specularStrength * spec * materialSpecular; 

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

    float shadow = ShadowCalculation(FragPosLightSpace, DepthText, norm, lightDir);

    return (ambient + (1.0 - shadow) * (diffuse + specular));
}

void main()
{   

    vec3 materialDiffuse = vec3(0.0,0.0,0.0);
    vec3 materialSpecular = vec3(0.0,0.0,0.0);

    if(u_hasAlbedoMap)
    {
        materialDiffuse = texture(u_albedoMap, TexCoords).rgb;
        materialSpecular = texture(u_roughnessMap, TexCoords).rgb;
    }
    else
    {
        materialDiffuse = u_albedoColor.xyz;
        materialSpecular = vec3(u_roughness,u_roughness,u_roughness);
    }

    

    vec3 result = vec3(0.0,0.0,0.0);

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