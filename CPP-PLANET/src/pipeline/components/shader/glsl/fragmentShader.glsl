#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

//uniform sampler2D texture1;

void main()
{
    FragColor = vec4(1,1,1,1);//texture(texture1, TexCoord);
    
    if (FragColor.a == 0) {
        discard;
    }
}