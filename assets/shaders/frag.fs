#version 330 core
// I have no idea how to use proper convention for glsl? just stick to using hungarian notation i guess!?
out vec4 FragColor;
in vec3 c;
in vec2 texture_coordinates;
uniform sampler2D missing_texture; // texture data will be filled into this via GL_TEXTURE_2D, 0
void main(){
	//FragColor = vec4(c, 1.0f);
	FragColor = texture(missing_texture, texture_coordinates); //* vec4(c, 1.0f);
}