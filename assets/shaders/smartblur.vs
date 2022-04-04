attribute vec4 a_position;
attribute vec2 a_texcoord;
uniform vec2 texel;

varying vec2 tc0, tc1, tc2, tc3, tc4;
//, tc5, tc6, tc7, tc8;

void main() {
  gl_Position = a_position;

  tc0 = a_texcoord;
  tc1 = a_texcoord + vec2(texel.x, 0.0);
  tc2 = a_texcoord - vec2(texel.x, 0.0);
  tc3 = a_texcoord + vec2(0.0, texel.y);
  tc4 = a_texcoord - vec2(0.0, texel.y);
  //tc5 = a_texcoord + texel;
  //tc6 = a_texcoord - texel;
  //tc7 = a_texcoord + vec2(texel.x, -texel.y);
  //tc8 = a_texcoord + vec2(-texel.x, texel.y);
}



