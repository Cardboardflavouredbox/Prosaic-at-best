uniform sampler2D texture;
uniform float color1,color2,color3,color4;

int fmod(int a,int b)
{
  int c = a-(a/b)*b;
  return c;
}

void main()
{
	// lookup the pixel in the texture
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	if(pixel.g==1.0&&pixel.a==1.0)gl_FragColor=vec4((float(2.0/3.0*float(fmod((int(color1)/4),2))) + 1.0/3.0*float(int(color1)/8)),float((1.0-float(int(color1)==6?1:0)/3.0)*2.0/3.0*float(fmod((int(color1)/2),2)) + 1.0/3.0*float(int(color1)/8)),float(2.0/3.0*float(fmod(int(color1),2)) + 1.0/3.0*float(int(color1)/8)),1);
	else if(pixel.g>0.5&&pixel.a==1.0)gl_FragColor=vec4((float(2.0/3.0*float(fmod((int(color3)/4),2))) + 1.0/3.0*float(int(color3)/8)),float((1.0-float(int(color3)==6?1:0)/3.0)*2.0/3.0*float(fmod((int(color3)/2),2)) + 1.0/3.0*float(int(color3)/8)),float(2.0/3.0*float(fmod(int(color3),2)) + 1.0/3.0*float(int(color3)/8)),1);
	else if(pixel.g>0.0&&pixel.a==1.0)gl_FragColor=vec4((float(2.0/3.0*float(fmod((int(color4)/4),2))) + 1.0/3.0*float(int(color4)/8)),float((1.0-float(int(color4)==6?1:0)/3.0)*2.0/3.0*float(fmod((int(color4)/2),2)) + 1.0/3.0*float(int(color4)/8)),float(2.0/3.0*float(fmod(int(color4),2)) + 1.0/3.0*float(int(color4)/8)),1);
	else if(pixel.g==0.0&&pixel.a==1.0)gl_FragColor=vec4((float(2.0/3.0*float(fmod((int(color2)/4),2))) + 1.0/3.0*float(int(color2)/8)),float((1.0-float(int(color2)==6?1:0)/3.0)*2.0/3.0*float(fmod((int(color2)/2),2)) + 1.0/3.0*float(int(color2)/8)),float(2.0/3.0*float(fmod(int(color2),2)) + 1.0/3.0*float(int(color2)/8)),1);
	else gl_FragColor=pixel;
}