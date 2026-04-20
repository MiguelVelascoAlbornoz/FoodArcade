#version 120 




varying vec2 fragPos;
varying vec2 UV;
uniform sampler2D text;
uniform float time;
uniform int sparklin;

uniform vec2 projectionSize;

void main() { 
  
       vec4 color = texture2D(text, UV);
      // if (color.a == 0){
      // color = vec4(1.0f,1.0f,1.0f,1.0f);
      // }
      if (sparklin == 1){
         if (sin(time*20) > 0){
            color+=vec4(0.5,0.5,0.5,0.);
         }
       }
       gl_FragColor =color;

 

}