precision mediump float;

uniform mat4 mat;
uniform vec3 params;

varying vec2 tc;

const float initstep = 2.0;
const float perspmul = 1.0;
const int maxsteps = 50;
const float threshold = 0.0;
const int forksteps = 8;

float func(vec3 pos) {
	vec3 center = vec3(0.0, 0.0, 4.0);
	vec3 spos = pos + params;
	return 2.0 - length(pos-center) + (sin(spos.x*4.0) + sin(spos.y*4.0) + sin(spos.z*4.0)) * 0.2;
}

vec3 normal(vec3 pos, float d) {
	float dx = func(pos + vec3(0.01, 0.0, 0.0));
	float dy = func(pos + vec3(0.0, 0.01, 0.0));
	float dz = func(pos + vec3(0.0, 0.0, 0.01));
	vec3 n = vec3(d - dx, d - dy, d - dz);
	return normalize(n);
}


void main() {
	vec3 xaxis = mat[0].xyz;
	vec3 yaxis = mat[1].xyz;
	vec3 zaxis = mat[2].xyz;
	vec3 pos, dir, col = vec3(0.5);
	float stepsize = 0.1;
	float dens;

	dir = normalize(vec3(tc, perspmul));
	pos = dir * initstep;

	int i;
	for (i = 0; i < maxsteps; i++) {
		dens = func(pos);
		if (dens > threshold) {
			break;
		}
		pos += dir * stepsize;
	}
	if (i == maxsteps) discard;

	float fstep = stepsize * 0.5;
	pos += dir * -fstep;
	for (i = 0; i < forksteps; i++) {
		dens = func(pos);
		if (dens > threshold) pos += dir * -fstep;
		else pos += dir * fstep;
		fstep *= 0.5;
	}
	col = normal(pos, dens);


	gl_FragColor = vec4(col*0.5+0.5, 0.0);
}

