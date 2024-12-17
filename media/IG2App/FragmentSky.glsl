#version 330 core

in vec2 vUv0;

uniform sampler2D text0;
uniform sampler2D text1;

out vec4 fFragColor;

void main()
{
    vec3 color0 = vec3(texture(text0, vUv0));
    vec3 color1 = vec3(texture(text1, vUv0)); 

    vec3 color = mix(color0, color1, 0.5);

    fFragColor = vec4(color, 1.0);
}