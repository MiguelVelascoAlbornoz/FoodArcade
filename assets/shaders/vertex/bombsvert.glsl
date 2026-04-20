#version 120 

attribute vec2 vPosition;
uniform mat4 model;
uniform vec2 modelPos;
varying vec2 UV;
varying vec2 fragPos;
uniform sampler2D text;
uniform int isBackground;
uniform vec2 dimensions;
uniform vec2 textSize;
uniform float size;
void main() {
     vec2 pos;
     if (isBackground == 1){
       UV = vec2(vPosition.x, 1.0 - vPosition.y-1)*(dimensions/(textSize*size));
       pos = vPosition*dimensions+modelPos;
     } else {
       UV = vec2(vPosition.x, 1.0 - vPosition.y);
       vec2 textureDimensions= textSize*size;
       pos = vPosition*textureDimensions+modelPos;

     }
  
    
     fragPos = pos;
     gl_Position = model*vec4(pos,0.0f,1.0f);
 
    



    

}