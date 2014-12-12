#version 330
layout(points) in;
layout(triangle_strip, max_vertices=4) out;

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
    //5,4,1,
    3,2,1,
    //4,0,1
    2,0,1
);

void main()
{   
    vec4 vertices[] = vec4[]
    (
        vec4(-f,f,-f, 1),
        vec4(-f,f,+f, 1), 
        vec4(+f,f,-f, 1), 
        vec4(+f,f,+f, 1) 
    );

    vec4 MVPposition;

    mat4 VPMatrix = uPMatrix * uVMatrix;

    MVPposition = VPMatrix * (vertices[0] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertices[0].xyz; //vec3(1,0,0);//vertex[0].color;      
    EmitVertex();

    MVPposition = VPMatrix * (vertices[1] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertices[1].xyz;//vec3(1,0,0);//vertex[0].color;    
    EmitVertex(); 

    MVPposition = VPMatrix * (vertices[2] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertices[2].xyz;//vec3(1,0,0);//vertex[0].color;      
    EmitVertex();           

    MVPposition = VPMatrix * (vertices[3] + vertex[0].position);
    gl_Position = MVPposition;
    g_Color = vertices[2].xyz;//vec3(0,1,0);//vertex[0].color;       
    EmitVertex();
  
    EndPrimitive();

}