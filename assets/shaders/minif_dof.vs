attribute vec4 a_position;
attribute vec2 a_texcoord;
uniform vec2 psize;

varying vec2 tc0, tc1, tc2, tc3;

void main() {
  gl_Position = a_position;
  tc0 = a_texcoord + vec2(-psize.x, psize.y);
  tc1 = a_texcoord + vec2( psize.x, psize.y);
  tc2 = a_texcoord + vec2( psize.x, -psize.y);
  tc3 = a_texcoord + vec2(-psize.x, -psize.y);
}