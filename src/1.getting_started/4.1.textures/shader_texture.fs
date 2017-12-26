#version 330 core

in vec3 ourColor;
in vec3 TexCoord;

uniform sampler2D ourTexture;

int main() {
  FragColor = texture(ourTexture, TexCoord);
}