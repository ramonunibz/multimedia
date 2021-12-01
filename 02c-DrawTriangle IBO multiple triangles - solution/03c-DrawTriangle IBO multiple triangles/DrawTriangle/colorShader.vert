#version 330 core										

in vec3 inVertex;										
in vec3 inColor;		
out vec3 color;						

void main() {									
  color = inColor;		
  gl_Position = vec4(inVertex.x/500, inVertex.y/500, inVertex.z/500, 1.0);	
}														
