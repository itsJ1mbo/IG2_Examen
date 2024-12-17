#version 330 core

in vec2 vUv0;

uniform sampler2D text0;
uniform sampler2D text1;
uniform sampler2D text2;

out vec4 fFragColor;

void main()
{
    vec3 color0 = vec3(texture(text0, vUv0));
    vec3 color1 = vec3(texture(text1, vUv0)); 
    vec3 color2 = vec3(texture(text2, vUv0)); 
    
    if(color0 == vec3(1, 1, 1))
        discard; 
    
    if(gl_FrontFacing)
        color0 = color2;
    else
        color0 = color1;

    fFragColor = vec4(color0, 1.0);
}