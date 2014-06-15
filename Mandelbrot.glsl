uniform int iterations;
varying highp vec2 texture_out;

void main()
{
  vec2 z  = texture_out;
  z      *= (3.0, 2.0);
  z      -= (2.0, 1.0);

  vec2 c  = z;

  int i = 0;
  for(; i < 256; ++i)
  {
    z  = vec2(z.x*z.x - z.y*z.y, 2.0*z.x*z.y);
    z += c;

    if( dot(z,z) > 4.0 ) 
      break;
  }

  vec4 color = vec4(0.0);

  if(i < 255)
  {
    color.x = sin(float(i) / 3.0);
    color.y = sin(float(i) / 6.0);
    color.z = cos(float(i) / 12.0 + 3.141 / 4.0);
  } 

  gl_FragColor = color;
}
