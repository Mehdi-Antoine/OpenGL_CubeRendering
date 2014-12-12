#version 330
layout(points) in;
layout(triangle_strip, max_vertices=36) out;

in Vertex 
{ 
  vec4 position;  
  vec3 color; 
} vertex[];

out vec3 g_Color;

uniform mat4 uVMatrix;
uniform mat4 uPMatrix;

const float f = 1.f;

const int elements[] = int[]
(
    0,2,1,
    2,3,1,

    1,3,5,
    3,7,5,

    5,7,4,
    7,6,4,

    4,6,0,
    6,2,0,

    3,2,7,
    2,6,7,

    5,4,1,
    4,0,1
);

void main()
{
    vec4 vertices[] = vec4[]
    (
        vec4(-f,-f,-f, 1), // 0
        vec4(-f,-f,+f, 1), // 1
        vec4(-f,+f,-f, 1), // 2
        vec4(-f,+f,+f, 1), // 3
        vec4(+f,-f,-f, 1), // 4
        vec4(+f,-f,+f, 1), // 5
        vec4(+f,+f,-f, 1), // 6
        vec4(+f,+f,+f, 1)  // 7
    );

    vec4 MVPposition;

    mat4 VPMatrix = uPMatrix * uVMatrix;

    int iIndex = 0;
    for(int iTri = 0; iTri < 12; ++iTri)
    {
        for(int iVert = 0; iVert < 3; ++iVert)
        {
            MVPposition = VPMatrix * (vertices[elements[iIndex++]] + vertex[0].position);
            gl_Position = MVPposition;
            g_Color = vertex[0].color;
            EmitVertex();         
        }

        EndPrimitive();
    }
}