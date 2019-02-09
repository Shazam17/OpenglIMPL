#shader vertex
#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uvCord;

out vec2 oUvCord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;


void main() {
	gl_Position = proj * view * model * vec4(pos.x  ,pos.y  , pos.z   , 1);
	oUvCord = uvCord;

}

#shader fragment
#version 330 core

uniform sampler2D txt;

in vec2 oUvCord;
out vec4 color;

void main() {
	color = texture(txt , oUvCord);
}

