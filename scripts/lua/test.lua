vertices = {
	-1.0, -1.0, 0.0,
	1.0,  -1.0, 0.0,
	0.0,  1.0, 0.0,
}

vertex = [[
	#version 330
	layout (location = 0) in vec3 pos; 
	
	void main() 
	{ 
		gl_Position = vec4(pos.x, pos.y, pos.z, 1.0); 
	}
]]

frag = [[
	#version 330
	out vec4 color; 
	
	void main() 
	{ 
		color = vec4(0.0, 1.0, 0.0, 1.0); 
	}
]]