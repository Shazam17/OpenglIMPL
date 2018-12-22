#shader vertex
#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 col;
layout(location = 2) in vec2 textCoord;
out vec4 Tcolor; 

out vec2 txtCoord;
uniform mat4 view;
uniform sampler2D txt;
//vec4(texture(txt , textCoord).rgb , 1) *
void main() {
	gl_Position = vec4(pos, 1);
	Tcolor = vec4(col , 1) ;
	txtCoord = textCoord;
}

#shader fragment
#version 330 core

in vec2 txtCoord;
in vec4 Tcolor;
out vec4 color;
uniform sampler2D txt;
void main() {
	color =  texture(txt, txtCoord);
}


