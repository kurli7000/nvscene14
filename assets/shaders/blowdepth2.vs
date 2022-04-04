attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec3 a_data0;

uniform mat4 mat;
uniform float blow;
uniform vec3 blowpos;

mat3 rotationMatrix(vec3 axis, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    return mat3(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c);
}

void main() {
	vec3 blowdir = a_data0 - blowpos;
	float blowpow = 1.0 / length(blowdir) * blow;
	blowpow *= blowpow * blowpow;
	normalize(blowdir);
	vec3 rotaxis = cross(vec3(0.0, 0.0, 1.0), blowdir);
	mat3 rotmat = rotationMatrix(normalize(rotaxis), -blowpow*1.5);
	vec3 rotated = rotmat * (a_position - a_data0) + a_data0;
	vec4 pos = vec4(rotated + blowdir * blowpow, 1.0);
	gl_Position = mat * pos;
}


