uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 NormalMatrix;

attribute vec3 Positions;

attribute vec3 Normals;

attribute vec3 TextureCoords;
varying vec2 TextureCoordsOut;

varying vec3 NormalOut;
varying vec3 EyePosOut;

void main(void) {
    EyePosOut = vec3(NormalMatrix * vec4(Positions[0], Positions[1], Positions[2], 1.0));
    NormalOut = vec3(NormalMatrix * vec4(Normals[0], Normals[1], Normals[2], 1.0));
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Positions[0], Positions[1], Positions[2], 1.0);
    TextureCoordsOut = vec2(TextureCoords[0], TextureCoords[1]);
}


