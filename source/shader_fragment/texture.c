uniform sampler2D texture;
varying mediump vec4 texc;
void main(void)
{
	gl_FragColor = texture2D(texture, texc.st);
}