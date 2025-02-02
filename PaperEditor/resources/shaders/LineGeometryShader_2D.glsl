﻿#type vertex
#version 460 core
layout(location = 0) in vec3 aPos; // the position variable has attribute position 0
layout(location = 1) in vec4 aColor; //the color of the vector
layout(location = 2) in int aCoreID;
layout(location = 3) in int aUIID;

// camera variables
layout(std140, binding = 0) uniform Camera
{
    mat4 uProjection;
    mat4 uView;
};

struct VertexOutput
{
    vec4 Color;
};
 
layout(location = 0) out VertexOutput Output;
layout(location = 1) out flat int CoreID;

void main()
{
    Output.Color = aColor;
    CoreID = aCoreID;

    gl_Position = uProjection * uView * vec4(aPos, 1.0f);
}


#type fragment
#version 460 core

// attachment 0 and 1
layout(location = 0) out vec4 display;
layout(location = 1) out int objectID;

struct VertexOutput
{
    vec4 Color;
};

layout(location = 0) in VertexOutput Input;
layout(location = 1) in flat int CoreID;

//uniform sampler2D uIDAttachment;

void main()
{
    display = Input.Color;
    objectID = CoreID;
}