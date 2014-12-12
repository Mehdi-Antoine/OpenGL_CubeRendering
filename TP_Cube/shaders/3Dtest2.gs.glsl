#version 330
layout(points) in;
layout(triangle_strip, max_vertices=36) out;

in Vertex 
{ 
  vec3 color; 
} vertex[];

out vec3 g_Color;

// UNIFORMS
const float f = 1.f;

const int elements[] = int[]
(
    //5,4,1,
    3,2,1,
    //4,0,1
    2,0,1
);

vec4 vOut_pos = vec4(0,0,0,1);
uniform mat4 uMVPMatrix;

// GS
void main()
{
    vec4 vertices[] = vec4[]
    (
        uMVPMatrix * (vOut_pos + vec4(-f,-f,-f, 0)),
        uMVPMatrix * (vOut_pos + vec4(-f,-f,+f, 0)), 
        //uMVPMatrix * (vOut_pos + vec4(-f,+f,-f, 0)), 
        //uMVPMatrix * (vOut_pos + vec4(-f,+f,+f, 0)), 
        uMVPMatrix * (vOut_pos + vec4(+f,-f,-f, 0)), 
        uMVPMatrix * (vOut_pos + vec4(+f,-f,+f, 0)) 
        //uMVPMatrix * (vOut_pos + vec4(+f,+f,-f, 0)), 
        //uMVPMatrix * (vOut_pos + vec4(+f,+f,+f, 0))
    );

    int iIndex = 0;
    for(int iTri = 0; iTri < 2; ++iTri)
    {
        for(int iVert = 0; iVert < 3; ++iVert)
        {
            gl_Position = vertices[elements[iIndex++]];
            g_Color = vertex[0].color;
            EmitVertex();          
        }

        EndPrimitive();
    }
}