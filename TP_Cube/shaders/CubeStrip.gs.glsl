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

    MVPposition = VPMatrix * (vertices[4] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;       
    EmitVertex();

    MVPposition = VPMatrix * (vertices[5] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;      
    EmitVertex();

    MVPposition = VPMatrix * (vertices[0] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;      
    EmitVertex();

    MVPposition = VPMatrix * (vertices[1] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;      
    EmitVertex();

    MVPposition = VPMatrix * (vertices[3] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;       
    EmitVertex();

    MVPposition = VPMatrix * (vertices[5] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;       
    EmitVertex();

    MVPposition = VPMatrix * (vertices[7] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;      
    EmitVertex();

    MVPposition = VPMatrix * (vertices[6] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;       
    EmitVertex();

    MVPposition = VPMatrix * (vertices[3] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;      
    EmitVertex();

    MVPposition = VPMatrix * (vertices[2] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;      
    EmitVertex();

    MVPposition = VPMatrix * (vertices[0] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;      
    EmitVertex();

    MVPposition = VPMatrix * (vertices[6] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;      
    EmitVertex();

    MVPposition = VPMatrix * (vertices[4] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;      
    EmitVertex();

    MVPposition = VPMatrix * (vertices[5] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertex[0].color;       
    EmitVertex();
  
    EndPrimitive();
}