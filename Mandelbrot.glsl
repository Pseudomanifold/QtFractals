uniform int iterations;

void main()
{
  vec2 position  = gl_FragCoord.xy; 
  
  if(position.x <= 0.0 && position.y < 1.0)
    gl_FragColor = vec4(1.0, 0.0, 0.0, 0.0);
  else
    gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
}
