uniform sampler2D texture;
uniform float r1,b1,g1,r2,b2,g2,r3,b3,g3;
void main()
{
	// lookup the pixel in the texture
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	if(pixel==vec4(r1,g1,b1,1))gl_FragColor=vec4(r4,g4,b4,1);
	else if(pixel.r==r1)gl_FragColor=vec4(r5,g5,b5,1);
	else if(pixel==vec4(r3,g3,b3,1))gl_FragColor=vec4(r6,g6,b6,1);
	else gl_FragColor=pixel;
}