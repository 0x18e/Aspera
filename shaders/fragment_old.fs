#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture_1; // container
uniform sampler2D texture_2; // awesomeface
uniform float mixer;
in vec3 ourColor;
void main() {
    // Mix the two textures; adjust the factor as needed.
    //FragColor = mix(texture(texture_1, TexCoord),texture(texture_2, vec2(1.0f - TexCoord.x, TexCoord.y), 0.2);
    //FragColor = texture(texture_2, vec2(TexCoord.x, TexCoord.y));
    //FragColor = mix(texture(texture_1, TexCoord), texture(texture_2, vec2(1.0f - TexCoord.x, TexCoord.y)), mixer);
    //FragColor = vec4(ourColor, 1.0f);
    FragColor = texture(texture_1, TexCoord);
}
