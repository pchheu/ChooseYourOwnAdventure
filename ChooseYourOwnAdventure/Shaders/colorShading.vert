#version 130
//Vertex shader operates on each vertex

//input data from the VBO, each vertex has 2 floats
in vec2 vertexPosition;

int main(){
	//x and y positions are set on the screen
	gl_Position.xy = vertexPosition;

	//We set z to 0 since this is a 2D game
	gl_Position.z = 0.0;

	//Indicates that the coordinates are normalized
	gl_Position.w = 1.0;
}