#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff*vec3(1.0,1.0,1.0);

    FragColor = vec4(diffuse*vec3(1.0,0.0,1.0), 1.0);
    
    if (FragColor.a == 0) {
        discard;
    }
}