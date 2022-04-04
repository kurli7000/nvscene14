attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texcoord;

uniform mat4 mat;
uniform vec3 up, right;
uniform float size;
uniform float time;
uniform vec4  params;

varying vec2 tc;

mat3 rotationMatrix(vec3 axis, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    return mat3(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c);
}

void main() {
	const vec3 center1 = vec3(-8.0, 0.0, 3.0);
	const vec3 center2 = vec3( 0.0, -5.0, -4.0);
	const vec3 center3 = vec3( 4.0, 4.0, 0.0);
	mat3 rotmatrix1 = rotationMatrix(normalize(vec3(0.7, 0.5, -0.1)), params.x*a_position.z * (1.0 + a_normal.z * params.w));
	mat3 rotmatrix2 = rotationMatrix(normalize(vec3(0.3, -0.7, 0.2)), params.y*a_position.y * (1.0 + a_normal.z * params.w));
	mat3 rotmatrix3 = rotationMatrix(normalize(vec3(-0.2, 0.2, 0.8)), params.z*a_position.x * (1.0 + a_normal.z * params.w));

	vec3 pos;
	pos = rotmatrix1 * (a_position - center1) + center1;
	pos = rotmatrix2 * (pos - center2) + center2;
	pos = rotmatrix3 * (pos - center3) + center3;

	//pos  *= (1.0 + a_normal.z * params.w);

 	gl_Position = mat * vec4(up * a_normal.x * size + right * a_normal.y * size + pos, 1.0);
	tc = a_texcoord;
}
