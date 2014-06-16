uniform highp vec2 center;
uniform highp float scale;

varying highp vec2 texture_out;

void main()
{
  vec2 z;
  vec2 c = texture_out;

  c *= scale * vec2(3.0, 2.0);
  c -= scale * vec2(2.0, 1.0);
  c += scale * center;
  
  z = c;

  int i = 0;
  for(; i < 256; ++i)
  {
    float x = z.x*z.x - z.y*z.y + c.x;
    float y = z.x*z.y + z.y*z.x + c.y;

    if( x*x + y*y > 4.0 ) 
      break;

    z.x = x;
    z.y = y;
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
