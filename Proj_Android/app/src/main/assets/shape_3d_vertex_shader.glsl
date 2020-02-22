uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;
attribute vec3 Positions;

void main(void) {
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Positions[0], Positions[1], Positions[2], 1.0);
}
