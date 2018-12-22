#shader vertex
#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 col;
out vec4 Tcolor;

uniform float trans;

void main() {
	gl_Position =  vec4(pos.x + trans ,pos.y + trans, 0, 1);
	Tcolor = vec4(col, 0, 1);
}

#shader fragment
#version 330 core

in vec4 Tcolor;
out vec4 color;

void main() {
	color = Tcolor;
}

