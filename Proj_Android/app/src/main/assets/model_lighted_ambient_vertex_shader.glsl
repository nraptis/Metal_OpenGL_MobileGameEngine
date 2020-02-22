uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;
attribute vec3 Positions;
attribute vec3 TextureCoords;
varying vec2 TextureCoordsOut;

void main(void) {
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Positions[0], Positions[1], Positions[2], 1.0);
    TextureCoordsOut = vec2(TextureCoords[0], TextureCoords[1]);
}
