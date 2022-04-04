


Mesh *breakmesh(float *verts, float *norms, unsigned short *inds, int vc, int fc, float thickness) {
	int i, j;
	int tricount=0;
	float avgsize=0.0;
	int tmpfc=0;
	int tmpvc=0;
	float *tmpverts;
	unsigned short *tmpinds;

	tricount = fc;
	int newvc = tricount*18;
	int newfc = tricount*8;
	LOGI("broken verts %i, broken tris %i", newvc, newfc);
	float *newverts = malloc(sizeof(float)*newvc*3);
	unsigned short *newinds = malloc(sizeof(unsigned short)*newfc*3);
	float *data = malloc(sizeof(float)*newvc*3);

	int vpos=0, ipos=0, datapos=0;
	for (i=0; i<fc; i++) {
		int i1, i2, i3;
		i1 = inds[i*3+0];
		i2 = inds[i*3+1];
		i3 = inds[i*3+2];
		float *v1, *v2, *v3;
		v1 = verts+i1*3;
		v2 = verts+i2*3;
		v3 = verts+i3*3;

		float a = triarea(v1, v2, v3) * 200.0;
		if (a > 1.0) a = 1.0;
		float th1 = thickness * a;
		float th2 = thickness * a;
		float th3 = thickness * a;

		float fnorm[3];
		calc_fnorm(v1, v2, v3, fnorm);

/*
		if (norms) {
			float *n1, *n2, *n3;
			n1 = verts+i1*3;
			n2 = verts+i2*3;
			n3 = verts+i3*3;
			if (dot(n1, fnorm) < 0.0) th1 = 0.0;
			if (dot(n2, fnorm) < 0.0) th2 = 0.0;
			if (dot(n3, fnorm) < 0.0) th3 = 0.0;
		}*/

		float th = (th1 + th2 + th3) / 3.0;

		float cog[3];
		float vb1[3], vb2[3], vb3[3];
		float fcenter[3];
		fcenter[0] = (v1[0]+v2[0]+v3[0])/3.0;
		fcenter[1] = (v1[1]+v2[1]+v3[1])/3.0;
		fcenter[2] = (v1[2]+v2[2]+v3[2])/3.0;
		cog[0] = (v1[0]+v2[0]+v3[0])/3.0-fnorm[0]*th*0.5;
		cog[1] = (v1[1]+v2[1]+v3[1])/3.0-fnorm[1]*th*0.5;
		cog[2] = (v1[2]+v2[2]+v3[2])/3.0-fnorm[2]*th*0.5;
		vb1[0] = v1[0]-fnorm[0]*th1; vb1[1] = v1[1]-fnorm[1]*th1; vb1[2] = v1[2]-fnorm[2]*th1;
		vb2[0] = v2[0]-fnorm[0]*th2; vb2[1] = v2[1]-fnorm[1]*th2; vb2[2] = v2[2]-fnorm[2]*th2;
		vb3[0] = v3[0]-fnorm[0]*th3; vb3[1] = v3[1]-fnorm[1]*th3; vb3[2] = v3[2]-fnorm[2]*th3;

		// front
		newverts[vpos++] = v1[0]; newverts[vpos++] = v1[1]; newverts[vpos++] = v1[2];
		newverts[vpos++] = v2[0]; newverts[vpos++] = v2[1]; newverts[vpos++] = v2[2];
		newverts[vpos++] = v3[0]; newverts[vpos++] = v3[1]; newverts[vpos++] = v3[2];

		// back
		newverts[vpos++] = vb1[0]; newverts[vpos++] = vb1[1]; newverts[vpos++] = vb1[2];
		newverts[vpos++] = vb3[0]; newverts[vpos++] = vb3[1]; newverts[vpos++] = vb3[2];
		newverts[vpos++] = vb2[0]; newverts[vpos++] = vb2[1]; newverts[vpos++] = vb2[2];
		
		// side 1-2
		newverts[vpos++] = v2[0]; newverts[vpos++] = v2[1]; newverts[vpos++] = v2[2];
		newverts[vpos++] = v1[0]; newverts[vpos++] = v1[1]; newverts[vpos++] = v1[2];
		newverts[vpos++] = vb1[0]; newverts[vpos++] = vb1[1]; newverts[vpos++] = vb1[2];
		newverts[vpos++] = vb2[0]; newverts[vpos++] = vb2[1]; newverts[vpos++] = vb2[2];

		// side 2-3
		newverts[vpos++] = v3[0]; newverts[vpos++] = v3[1]; newverts[vpos++] = v3[2];
		newverts[vpos++] = v2[0]; newverts[vpos++] = v2[1]; newverts[vpos++] = v2[2];
		newverts[vpos++] = vb2[0]; newverts[vpos++] = vb2[1]; newverts[vpos++] = vb2[2];
		newverts[vpos++] = vb3[0]; newverts[vpos++] = vb3[1]; newverts[vpos++] = vb3[2];

		// side 3-1
		newverts[vpos++] = v1[0]; newverts[vpos++] = v1[1]; newverts[vpos++] = v1[2];
		newverts[vpos++] = v3[0]; newverts[vpos++] = v3[1]; newverts[vpos++] = v3[2];
		newverts[vpos++] = vb3[0]; newverts[vpos++] = vb3[1]; newverts[vpos++] = vb3[2];
		newverts[vpos++] = vb1[0]; newverts[vpos++] = vb1[1]; newverts[vpos++] = vb1[2];

		for (j=0; j<18; j++) {
			data[datapos++] = cog[0];
			data[datapos++] = cog[1];
			data[datapos++] = cog[2];
		}

		newinds[ipos++] = i*18+0; newinds[ipos++] = i*18+1; newinds[ipos++] = i*18+2;
		newinds[ipos++] = i*18+3; newinds[ipos++] = i*18+4; newinds[ipos++] = i*18+5;
		newinds[ipos++] = i*18+6; newinds[ipos++] = i*18+7; newinds[ipos++] = i*18+8;
		newinds[ipos++] = i*18+6; newinds[ipos++] = i*18+8; newinds[ipos++] = i*18+9;
		newinds[ipos++] = i*18+10; newinds[ipos++] = i*18+11; newinds[ipos++] = i*18+12;
		newinds[ipos++] = i*18+10; newinds[ipos++] = i*18+12; newinds[ipos++] = i*18+13;
		newinds[ipos++] = i*18+14; newinds[ipos++] = i*18+15; newinds[ipos++] = i*18+16;
		newinds[ipos++] = i*18+14; newinds[ipos++] = i*18+16; newinds[ipos++] = i*18+17;
	}

	Mesh *m = loadmesh(newinds, newverts, 0, 0, data, newfc, newvc);
	free(newverts);
	free(newinds);
	free(data);
	return m;
}


Mesh *flatmesh(float *verts, unsigned short *inds, int vc, int fc) {
	int i, j;
	int tricount=0;
	float avgsize=0.0;
	int tmpfc=0;
	int tmpvc=0;
	float *tmpverts;
	unsigned short *tmpinds;

	tricount = fc;
	int newvc = tricount*3;
	int newfc = tricount;
	LOGI("flat verts %i, flat tris %i", newvc, newfc);
	float *newverts = malloc(sizeof(float)*newvc*3);
	unsigned short *newinds = malloc(sizeof(unsigned short)*newfc*3);
	float *data = malloc(sizeof(float)*newvc*3);

	int vpos=0, ipos=0, datapos=0;
	for (i=0; i<fc; i++) {
		int i1, i2, i3;
		i1 = inds[i*3+0];
		i2 = inds[i*3+1];
		i3 = inds[i*3+2];
		float *v1, *v2, *v3;
		v1 = verts+i1*3;
		v2 = verts+i2*3;
		v3 = verts+i3*3;

		float fnorm[3];
		calc_fnorm(v1, v2, v3, fnorm);
		newverts[vpos++] = v1[0]; newverts[vpos++] = v1[1]; newverts[vpos++] = v1[2];
		newverts[vpos++] = v2[0]; newverts[vpos++] = v2[1]; newverts[vpos++] = v2[2];
		newverts[vpos++] = v3[0]; newverts[vpos++] = v3[1]; newverts[vpos++] = v3[2];
		newinds[ipos++] = i*3+0; newinds[ipos++] = i*3+1; newinds[ipos++] = i*3+2;
	}

	memset(data, 0, sizeof(float)*newvc*3);

	Mesh *m = loadmesh(newinds, newverts, 0, 0, data, newfc, newvc);
	free(newverts);
	free(newinds);
	free(data);
	return m;
}




