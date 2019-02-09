#shader vertex
#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 textCord;


uniform mat4 MVP;
//uniform mat4 view;
//uniform mat4 model;
//uniform mat4 projection;

out vec2 vTexCord;

void main() {
	gl_Position = MVP * vec4(pos.x , pos.y , 0, 1);
	vTexCord = textCord;
}

#shader fragment
#version 330 core


uniform sampler2D txt;

in vec2 vTexCord;
out vec4 color;


void main() {
	color = texture(txt, vTexCord);
}

