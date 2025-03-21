uniform sampler2D texture;
void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	gl_FragColor=vec4(pixel.r-1.0/3.0,pixel.g-1.0/3.0,pixel.b-1.0/3.0,1.0);
}