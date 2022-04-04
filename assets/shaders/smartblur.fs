precision mediump float;

uniform sampler2D t_color;

varying vec2 tc0, tc1, tc2, tc3, tc4;
//, tc5, tc6, tc7, tc8;
const float threshold = 0.1;

void main() {
	vec4 col = texture2D(t_color, tc0);
	float mid = col.a;
	float samples = 1.0;
	vec4 smp1 = texture2D(t_color, tc1);
	vec4 smp2 = texture2D(t_color, tc2);
	vec4 smp3 = texture2D(t_color, tc3);
	vec4 smp4 = texture2D(t_color, tc4);
	//vec4 smp5 = texture2D(t_color, tc5);
	//vec4 smp6 = texture2D(t_color, tc6);
	//vec4 smp7 = texture2D(t_color, tc7);
	//vec4 smp8 = texture2D(t_color, tc8);

	if (abs(smp1.a - mid) < threshold) { col+=smp1; samples += 1.0; }
	if (abs(smp2.a - mid) < threshold) { col+=smp2; samples += 1.0; }
	if (abs(smp3.a - mid) < threshold) { col+=smp3; samples += 1.0; }
	if (abs(smp4.a - mid) < threshold) { col+=smp4; samples += 1.0; }
	//if (abs(smp5.a - mid) < threshold) { col+=smp5; samples += 1.0; }
	//if (abs(smp6.a - mid) < threshold) { col+=smp6; samples += 1.0; }
	//if (abs(smp7.a - mid) < threshold) { col+=smp7; samples += 1.0; }
	//if (abs(smp8.a - mid) < threshold) { col+=smp8; samples += 1.0; }
	gl_FragColor = col / samples;
}

