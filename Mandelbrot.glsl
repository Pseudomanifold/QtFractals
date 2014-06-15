uniform int iterations;
varying highp vec2 texture_out;

void main()
{
  vec2 position  = texture_out;
  
  if(position.x <= 0.5 && position.y <= 0.5)
    gl_FragColor = vec4(1.0, 0.0, 0.0, 0.0);
  else
    gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
}
