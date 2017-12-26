#version 330 core
layout (location = 0) vec3 aPos;
layout (location = 1) vec3 aColor;
layout (location = 2) vec2 aTexCoord;

out vec3 ourColor;
out vec3 TexCoord;

int main() {
  gl_Position = vec4(aPos, 1.0f);
  ourColor = aColor;
  TexCoord = aTexCoord;
}