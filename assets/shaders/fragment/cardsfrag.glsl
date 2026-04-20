#version 120


uniform int isBackground;
uniform sampler2D card_top;
uniform sampler2D card_back;
uniform sampler2D centerImage;
uniform sampler2D background;
uniform int show;
uniform vec2 textSize;
varying vec2 fragPos;
varying vec2 UV;


void main() { 
    vec4 col;
    if (isBackground == 0){

      if (show == 0){
        col = vec4(texture2D(card_back,UV));
      }  else {
        col = vec4(texture2D(card_top,UV));
          ivec2 imageDimensions = ivec2(textSize);
          float aspectRatio = float(imageDimensions.x)/float(imageDimensions.y);
          
          vec2 centerImageUV = (UV)*vec2(1.5f,1.5f)*vec2(1.0f,aspectRatio/0.6667)-vec2((1.5-1)/2,(aspectRatio*2.25-1)/2);//-vec2(0.5f,0.5f);

    

          vec4 cnterImageCol = vec4(texture2D(centerImage,centerImageUV));
          if (cnterImageCol.a != 0){
           col = cnterImageCol;
      
        }
       
       
        
      }


    } else {
  //  vec2 lightPos = vec2(0.0f,-1.0f);
   // float dst = length(lightPos-fragPos);
    vec4 textCol = texture2D(background,UV)*2;
    col = textCol;
    }
    
    gl_FragColor = col;
}