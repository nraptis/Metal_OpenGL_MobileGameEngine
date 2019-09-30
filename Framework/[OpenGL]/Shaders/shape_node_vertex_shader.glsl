uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;
attribute vec3 Positions;
attribute vec4 Colors;
varying vec4 DestinationColor;

void main(void) {
    DestinationColor = Colors;
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Positions[0], Positions[1], Positions[2], 1.0);
}
