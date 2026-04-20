#version 120 

attribute vec2 vPosition;
uniform mat4 model;
uniform vec2 modelPos;
varying vec2 UV;
varying vec2 fragPos;
uniform sampler2D text;
uniform int isBackground;
uniform vec2 dimensions;
uniform mat4 rotationMatrix;
uniform float size;
uniform vec2 textSize;
uniform vec2 massCenter;
void main() {
     vec4 pos;
     if (isBackground == 1){
       UV = vec2(vPosition.x, 1.0 - vPosition.y-1)*(dimensions/(textSize*size));
       vec4 localPos = vec4(vPosition*dimensions,0.0f,1.0f);
       localPos = rotationMatrix*localPos;
       pos = (localPos)+vec4(modelPos,0.0f,0.0f);
     } else {
       UV = vec2(vPosition.x, 1.0 - vPosition.y);
       vec2 textureDimensions= textSize*size;
       vec4 localPos = rotationMatrix*vec4((vPosition*textureDimensions)-massCenter,0.0f,1.0f)+vec4(massCenter,0.0f,0.0f);
       pos = localPos+vec4(modelPos,0.0f,0.0f);

     }
  
   //  vec4 rotatedPos = rotationMatrix*vec4(pos-vec2(9.5*size,10.5*size),0.0f,1.0f);
     //fragPos = vec2(rotationMatrix*vec4(pos,0.0f,1.0f) );
     gl_Position = model*pos;
 
    



    

}