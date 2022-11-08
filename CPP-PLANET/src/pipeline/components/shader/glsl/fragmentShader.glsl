#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;

void main()
{
    vec3 ambient = vec3(0.2, 0.2, 0.2)*vec3(1.0,1.0,1.0);
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize((lightPos - FragPos)*6);
    //vec3 lightDir = normalize(-lightPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = vec3(0.5,0.5,0.5)*diff*vec3(1.0,1.0,1.0);

    vec3 result = ambient + diffuse;

    FragColor = vec4(result, 1.0);
    
    if (FragColor.a == 0) {
        discard;
    }
}