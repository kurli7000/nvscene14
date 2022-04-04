precision mediump float;

uniform sampler2D t_shadow;
uniform float br;

varying vec3 v_diffuse;
varying vec3 v_ambient;
varying vec3 v_tc;
varying float dist;

const float offset = 0.001;

void main() {
	float depth = texture2D(t_shadow, v_tc.xy).r;
	float shadow = step(v_tc.z, depth+offset);
	gl_FragColor = vec4((v_diffuse*shadow+v_ambient)*br, dist);
}
