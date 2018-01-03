#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
  FragColor = mix(texture(texture1, vec2(TexCoord.x*0.1, TexCoord.y*0.1)), texture(texture2, vec2(TexCoord.x*0.1, TexCoord.y*0.1)), 0.2);
}