typedef struct {
  int tex;
  float widthtab[256];
  float postab[256*2];
  int xres, yres;
} Font;

unsigned char font_index[]={
  97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,
  113,114,115,116,117,118,119,120,121,122,229,228,246,48,49,50,
  51,52,53,54,55,56,57,43,33,34,35,38,47,40,41,61,
  63,64,36,91,93,123,125,92,42,39,59,58,95,44,46,45,
};

/*
abcdefgh
ijklmnop
qrstuvwx
yzåäö012
3456789+
!"#&/()=
?@$[]{}\
*';:_,.-
*/

Font *loadfont(char *filename, char *filenamealpha, unsigned char *indextab) {
  Font *f = malloc(sizeof(Font));
  int x, y, xx, yy;
  unsigned char *tmpdata;
  int xres, yres;
  int xstart, xend;
  int threshold=8;

  f->tex = loadtexture(filename, filenamealpha);
  tmpdata = loadimage(filename, filenamealpha, &xres, &yres);
  f->xres = xres;
  f->yres = yres;

  for (x=0; x<256; x++) {
    f->postab[x*2+0] = 0.0;
    f->postab[x*2+1] = 0.0;
    f->widthtab[x] = 1.0;
  }

  for (y=0; y<8; y++) for (x=0; x<8; x++) {
    int i=indextab[y*8+x];

    f->postab[i*2+0] = (float)x/8.0;
    f->postab[i*2+1] = (float)y/8.0;

    xstart=-1;
    for (xx=0; xx<xres/8 && xstart==-1; xx++) for (yy=0; yy<yres/8; yy++) {
      int u, v;

      u=xx+x*xres/8;
      v=yy+y*yres/8;

      if (tmpdata[(v*xres+u)*4+3]>threshold) {
        xstart=xx;
        continue;
      }
    }

    xend=-1;
    for (xx=xres/8-1; xx>=0 && xend==-1; xx--) for (yy=0; yy<yres/8; yy++) {
      int u, v;

      u=xx+x*xres/8;
      v=yy+y*yres/8;

      if (tmpdata[(v*xres+u)*4+3]>threshold) {
        xend=xx;
        continue;
      }
    }

    if (xstart==-1 || xend==-1 || xstart==xend) LOGI("error finding start/end of font letter %i, start=%i, end=%i", i, xstart, xend);
    //else LOGI("letter %c width %5.2f", indextab[y*8+x], (float)(xend-xstart)/(xres/8.0));
    f->widthtab[i] = (float)(xend-xstart)/(xres/8.0);
  }

  free(tmpdata);

  return f;
}



void fontprint(Font *f, float* pos, float scale, float spacing, int center, char *fmt, ...) {
  static char str[8000];
  va_list ap;
  int ch;
  static float vbuf[8000 * 18];
  static float tbuf[8000 * 12];
  float xpos = pos[0];

  memset(vbuf, 0, sizeof(float)*8000*18);

  bindtexture("t_color", f->tex, 0);

  va_start(ap, fmt);
  vsprintf(str, fmt, ap);
  va_end(ap);
  //fontprintstring(f, spacing, center, colbuf, offsets, buf);

  if (center) {
    float width=0.0;

    /*for (ch=0; str[ch]!=0; ch++) {

      if (str[ch]==32) w += (1.0 + spacing) * 0.25;
      else w+=(f->widthtab[str[ch]&255])+spacing;
    }*/
    for (ch=0; str[ch]!=0; ch++) {
      if (str[ch]==32) {
        width += (scale + spacing * scale) * 0.5;
      } else {
        float w = f->widthtab[str[ch]&255];
        float padding = (1.0 - w) * scale;
        if (ch > 0) width -= padding;
        width += (w+spacing)*scale*2.0;
        width += padding;
      }
    }
    xpos -= width*center*0.5;
  }

  int numchars = strlen(str);
  if (numchars > 7999) LOGI("text too long!");

  xpos += scale;
  float y1 = pos[1] + scale * anal_aspect;
  float y2 = pos[1] - scale * anal_aspect;
  int bufpos = 0;
  for (ch=0; str[ch]!=0; ch++) {
    float u1, v1, u2, v2;
    //float x1, y1, x2, y2;
    float x1, x2;

    if (str[ch]==32) {
      xpos += (scale + spacing * scale) * 0.5;
    } else {
      float w = f->widthtab[str[ch]&255];
      float padding = (1.0 - w) * scale;

      u1 = f->postab[(str[ch]&255)*2+0];
      v1 = f->postab[(str[ch]&255)*2+1];
      u2 = u1+1.0/8.0;
      v2 = v1+1.0/8.0;

      if (ch > 0) xpos -= padding;
      x1 = xpos - scale;
      x2 = xpos + scale;

      //if (ch == 0) xpos += sca;
      //xpos -= scale-w;

      tbuf[bufpos*12+0] = u1; tbuf[bufpos*12+1] = v1;
      tbuf[bufpos*12+2] = u2; tbuf[bufpos*12+3] = v1;
      tbuf[bufpos*12+4] = u1; tbuf[bufpos*12+5] = v2;
      tbuf[bufpos*12+6] = u1; tbuf[bufpos*12+7] = v2;
      tbuf[bufpos*12+8] = u2; tbuf[bufpos*12+9] = v1;
      tbuf[bufpos*12+10] = u2; tbuf[bufpos*12+11] = v2;

      vbuf[bufpos*18+0] = x1; vbuf[bufpos*18+1] = y1; vbuf[bufpos*18+2] = pos[2];
      vbuf[bufpos*18+3] = x2; vbuf[bufpos*18+4] = y1; vbuf[bufpos*18+5] = pos[2];
      vbuf[bufpos*18+6] = x1; vbuf[bufpos*18+7] = y2; vbuf[bufpos*18+8] = pos[2];
      vbuf[bufpos*18+9] = x1; vbuf[bufpos*18+10] = y2; vbuf[bufpos*18+11] = pos[2];
      vbuf[bufpos*18+12] = x2; vbuf[bufpos*18+13] = y1; vbuf[bufpos*18+14] = pos[2];
      vbuf[bufpos*18+15] = x2; vbuf[bufpos*18+16] = y2; vbuf[bufpos*18+17] = pos[2];

      bufpos++;
      xpos += (w+spacing)*scale*2.0;
      xpos += padding;
    }
  }

  //LOGI("printing %s, len %i", str, numchars);

  int poshandle, texhandle;
  poshandle = glGetAttribLocation(currentshader, POSITION_ARRAY_NAME);
    glVertexAttribPointer(poshandle, 3, GL_FLOAT, GL_FALSE, 0, vbuf);
  glEnableVertexAttribArray(poshandle);
  texhandle = glGetAttribLocation(currentshader, TEXCOORD_ARRAY_NAME);
    glVertexAttribPointer(texhandle, 2, GL_FLOAT, GL_FALSE, 0, tbuf);     
  glEnableVertexAttribArray(texhandle);
  glDrawArrays(GL_TRIANGLES, 0, numchars * 6);

}

float fontprint_length(Font *f, float scale, float spacing, char *fmt, ...) {
  static char buf[8000];
  va_list ap;
  float w;
  int ch;

  va_start(ap, fmt);
  vsprintf(buf, fmt, ap);
  va_end(ap);

  w=0;
  for (ch=0; buf[ch]!=0; ch++) {
    if (buf[ch]==32) {
      w+=0.5;
    } else {
      w+=(f->widthtab[buf[ch]&255]+0.05)*spacing;
    }
  }

  return w*scale*2;
}




void fontprint_kikka3(Font *f, float* pos, float scale, float spacing, int center, char *fmt, ...) {
  static char str[8000];
  va_list ap;
  int ch;
  static float vbuf[8000 * 18];
  static float tbuf[8000 * 12];
  float xpos = pos[0];

  memset(vbuf, 0, sizeof(float)*8000*18);

  bindtexture("t_color", f->tex, 0);

  va_start(ap, fmt);
  vsprintf(str, fmt, ap);
  va_end(ap);
  //fontprintstring(f, spacing, center, colbuf, offsets, buf);

  if (center) {
    float w=0;

    for (ch=0; str[ch]!=0; ch++) {
      if (str[ch]==32) w+=1.0+spacing;
      else w+=(f->widthtab[str[ch]&255])+spacing;
    }

    //glTranslatef(-w*center, 0, 0);
    xpos -= w*center*scale;
  }

  int numchars = strlen(str);
  if (numchars > 7999) LOGI("text too long!");

  xpos += scale;
  float y1 = pos[1] + scale * anal_aspect;
  float y2 = pos[1] - scale * anal_aspect;
  int bufpos = 0;
  for (ch=0; str[ch]!=0; ch++) {
    float u1, v1, u2, v2;
    //float x1, y1, x2, y2;
    float x1, x2;

    if (str[ch]==32) {
      xpos += (scale + spacing * scale) * 0.5;
    } else {
      float w = f->widthtab[str[ch]&255];
      float padding = (1.0 - w) * scale;

      u1 = f->postab[(str[ch]&255)*2+0];
      v1 = f->postab[(str[ch]&255)*2+1];
      u2 = u1+1.0/8.0;
      v2 = v1+1.0/8.0;

      if (ch > 0) xpos -= padding;
      x1 = xpos - scale;
      x2 = xpos + scale;

      //if (ch == 0) xpos += sca;
      //xpos -= scale-w;

      tbuf[bufpos*12+0] = u1; tbuf[bufpos*12+1] = v1;
      tbuf[bufpos*12+2] = u2; tbuf[bufpos*12+3] = v1;
      tbuf[bufpos*12+4] = u1; tbuf[bufpos*12+5] = v2;
      tbuf[bufpos*12+6] = u1; tbuf[bufpos*12+7] = v2;
      tbuf[bufpos*12+8] = u2; tbuf[bufpos*12+9] = v1;
      tbuf[bufpos*12+10] = u2; tbuf[bufpos*12+11] = v2;

      vbuf[bufpos*18+0] = x1; vbuf[bufpos*18+1] = y1; vbuf[bufpos*18+2] = pos[2];
      vbuf[bufpos*18+3] = x2; vbuf[bufpos*18+4] = y1; vbuf[bufpos*18+5] = pos[2];
      vbuf[bufpos*18+6] = x1; vbuf[bufpos*18+7] = y2; vbuf[bufpos*18+8] = pos[2];
      vbuf[bufpos*18+9] = x1; vbuf[bufpos*18+10] = y2; vbuf[bufpos*18+11] = pos[2];
      vbuf[bufpos*18+12] = x2; vbuf[bufpos*18+13] = y1; vbuf[bufpos*18+14] = pos[2];
      vbuf[bufpos*18+15] = x2; vbuf[bufpos*18+16] = y2; vbuf[bufpos*18+17] = pos[2];

      if (ch > 0) bufpos++;
      xpos += (w+spacing)*scale*2.0;
      xpos += padding;
    }
  }

  //LOGI("printing %s, len %i", str, numchars);

  int poshandle, texhandle;
  poshandle = glGetAttribLocation(currentshader, POSITION_ARRAY_NAME);
    glVertexAttribPointer(poshandle, 3, GL_FLOAT, GL_FALSE, 0, vbuf);
  glEnableVertexAttribArray(poshandle);
  texhandle = glGetAttribLocation(currentshader, TEXCOORD_ARRAY_NAME);
    glVertexAttribPointer(texhandle, 2, GL_FLOAT, GL_FALSE, 0, tbuf);     
  glEnableVertexAttribArray(texhandle);
  glDrawArrays(GL_TRIANGLES, 0, numchars * 6);

}


