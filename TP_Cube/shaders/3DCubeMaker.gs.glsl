#version 330
layout(points) in;
layout(triangle_strip, max_vertices=36) out;

in Vertex 
{ 
  vec3 color; 
} vertex[];

out vec3 g_Color;

void main()
{	
  for(int i=0; i<36; i++)
  {
    gl_Position = gl_in[i].gl_Position;
    g_Color = vertex[i].color;
    EmitVertex();
  }
  EndPrimitive();
} 