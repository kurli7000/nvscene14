precision mediump float;

uniform sampler2D t_color;
uniform vec4 br;

varying vec2 tc;

void main() {
	vec4 col = texture2D(t_color, tc);
	if (col.a < 0.5) discard;
	gl_FragColor = texture2D(t_color, tc);
}
