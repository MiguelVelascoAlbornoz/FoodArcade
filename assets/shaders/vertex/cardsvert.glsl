#version 120 

attribute vec2 vPosition;
uniform mat4 model;
uniform int cardWidth;
uniform vec2 modelPos;
varying vec2 UV;
varying vec2 fragPos;
uniform int isBackground;
uniform mat4 rotation;

void main() {
    vec2 pos;
    UV = vec2(1.0f,1.0f)-vPosition;
    if (isBackground == 0){
    vec2 dimensions = vec2(cardWidth,cardWidth*1.5);
    vec2 a = vec2(vPosition*dimensions);
     pos = vec2(rotation*vec4(a.x-dimensions.x/2,a.y-dimensions.y/2,1.0f,1.0f)+vec4(modelPos.x+dimensions.x/2,modelPos.y+dimensions.y/2,0.0f,0.0f));
     
      
     gl_Position = model*vec4(pos,0.0f,1.0f);
    
    } else {
     pos = (vPosition-vec2(0.5,0.5f))*2.0f;
     fragPos = pos;
     gl_Position = vec4(pos,0.0f,1.0f);
    }
    



    

}