uniform sampler2D texture;
uniform float r1,b1,g1,r2,b2,g2,r3,b3,g3,r4,b4,g4;
void main()
{
	// lookup the pixel in the texture
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	if(pixel.g==1.0&&pixel.a==1.0)gl_FragColor=vec4(r1,g1,b1,1);
	else if(pixel.g>0.5&&pixel.a==1.0)gl_FragColor=vec4(r3,g3,b3,1);
	else if(pixel.g>0.0&&pixel.a==1.0)gl_FragColor=vec4(r4,g4,b4,1);
	else if(pixel.g==0.0&&pixel.a==1.0)gl_FragColor=vec4(r2,g2,b2,1);
	else gl_FragColor=pixel;
}