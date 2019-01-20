#shader vertex
#version 330 core
layout(location = 0) in vec2 pos;

out vec4 Tcolor;
uniform mat4 View;

uniform float x;
uniform float y;
uniform vec3 NewColor;


void main() {
	gl_Position = View * vec4(pos.x + x ,pos.y +  y, 0, 1);
	Tcolor = vec4(NewColor,1);
}

#shader fragment
#version 330 core

in vec4 Tcolor;
out vec4 color;

void main() {
	color = Tcolor;
}

