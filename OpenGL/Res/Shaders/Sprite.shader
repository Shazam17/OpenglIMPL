#shader vertex
#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 textCord;
out vec4 Tcolor;


uniform mat4 MVP;
uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
uniform sampler2D txt;

void main() {
	gl_Position = MVP * vec4(pos.x , pos.y , 0, 1);
	Tcolor = vec4(1, 1, 0.5, 1);
}

#shader fragment
#version 330 core

in vec4 Tcolor;
out vec4 color;

void main() {
	color = Tcolor;
}

