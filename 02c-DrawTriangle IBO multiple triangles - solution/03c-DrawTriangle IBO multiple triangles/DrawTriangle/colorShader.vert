#version 330 core										

in vec3 inVertex;										
in vec3 inColor;		
out vec3 color;						

void main() {									
  color = inColor;		
  gl_Position = vec4(inVertex.x, inVertex.y, inVertex.z, 1.0);	
}														
