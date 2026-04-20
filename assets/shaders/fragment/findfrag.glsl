#version 120




varying vec2 fragPos;
varying vec2 UV;
uniform sampler2D text;
uniform int isWanted;
uniform vec2 projectionSize;
uniform struct Light {
    vec2 position;

    float radius;
} lightCircles[2];
void main() { 
  
   // vec2 textureDimensions = textureSize(wantedTexture,0);
   // float aspect = textureDimensions.y/textureDimensions.x;
    //vec2 adjustedUV = UV;
  
     //   adjustedUV.y /= aspect;
       if (isWanted == 1){
               if (pow((fragPos.x-lightCircles[0].position.x),2)+pow((fragPos.y-lightCircles[0].position.y),2) > lightCircles[0].radius*lightCircles[0].radius && pow((fragPos.x-lightCircles[1].position.x),2)+pow((fragPos.y-lightCircles[1].position.y),2) > lightCircles[1].radius*lightCircles[1].radius){
               gl_FragColor = vec4(0.0f);
               return;
               }
       } else if (fragPos.x > projectionSize.x/2-253*1.7){
         gl_FragColor = vec4(0.0f);
         return;
       }

       gl_FragColor = texture2D(text, UV);

 

}