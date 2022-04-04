attribute vec3 a_position;

uniform mat4 mat;

void main() {
  gl_Position = mat * vec4(a_position, 1.0);
}
