#type vertex
#version 330 core
layout (location = 0) in vec2 aPos; // the position variable has attribute position 0
layout (location = 1) in vec4 aColor; //the color of the vector
layout (location = 2) in vec2 aTexCoord; //the coords of the texture
layout (location = 3) in ivec4 aTexID; //The slot of the texture

// declare vertex variables that are being piped to fragment
out vec4 fColor;
out vec2 fTexCoord;
out ivec4 fTexID;

// camera variables
uniform mat4 uProjection;
uniform mat4 uView;

void main()
{
    // pipe variables from the vbo
    gl_Position = uProjection * uView * vec4(aPos, 0.0f, 1.0f); // adjust gl_Position with the help of 'u' Factors
    fColor = aColor;
    fTexCoord = aTexCoord;
    fTexID = aTexID; // pipe texID to fragment
}


#type fragment
#version 330 core

in vec4 fColor; // get color from vertex
in vec2 fTexCoord; // get texCoord from vertex
flat in ivec4 fTexID; // get texID from vertex

uniform sampler2D uTexture[3];

out vec4 display;

void main()
{
    
    if (fTexID[0] => 0) {
        display = vec4(1.0f, 1.0f, 0.0f, 1.0f);
        //display = texture(uTexture[0], fTexCoord);
    }
    //if (fTexID.y >= 0) {
    //    display = texture(uTexture[fTexID.y], fTexCoord);
    //}
    //if (fTexID.z >= 0) {
    //    display = texture(uTexture[fTexID.z], fTexCoord);
    //}
    //if (fTexID.w >= 0) {
    //    display = texture(uTexture[fTexID.w], fTexCoord);
    //}
    //display = fColor;
}