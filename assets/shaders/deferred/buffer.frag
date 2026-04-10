#version 460 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gColorSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform bool      u_hasAlbedoMap;
uniform vec4      u_albedoColor;
uniform sampler2D u_albedoMap;

void main()
{    

    gPosition = FragPos;

    gNormal = normalize(Normal);

    vec3 result = u_hasAlbedoMap
            ? texture(u_albedoMap, TexCoords).rgb
            : u_albedoColor.rgb;

    gColorSpec.rgb = result;

    gColorSpec.a = 1.0f;
}