uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;
attribute vec2 Positions;

void main(void) {
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Positions[0], Positions[1], 0.0, 1.0);
}
