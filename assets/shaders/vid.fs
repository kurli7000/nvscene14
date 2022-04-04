precision mediump float;

uniform float br;
//uniform sampler2D t_shadow;

varying vec3 color;
//varying vec3 v_tc;
//const float offset = 0.001;

void main() {
	//float depth = texture2D(t_shadow, v_tc.xy).r;
	//float shadow = step(v_tc.z, depth+offset);
	gl_FragColor = vec4(color*br, 1.0);
}
