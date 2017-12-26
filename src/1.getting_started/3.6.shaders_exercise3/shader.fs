#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec4 gl_Position
void main() {
  FragColor = vec4(gl_Position);
}
