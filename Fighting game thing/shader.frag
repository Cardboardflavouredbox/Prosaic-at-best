uniform sampler2D texture;
uniform float r4,b4,g4,r5,b5,g5,r6,b6,g6;
void main()
{
	// lookup the pixel in the texture
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	if(pixel.g==1&&pixel.a==1)gl_FragColor=vec4(r4,g4,b4,1);
	else if(pixel.g>0&&pixel.a==1)gl_FragColor=vec4(r6,g6,b6,1);
	else if(pixel.g==0&&pixel.a==1)gl_FragColor=vec4(r5,g5,b5,1);
	else gl_FragColor=pixel;
}