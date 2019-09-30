/*uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;

attribute vec2 Positions;
 attribute vec2 TextureCoords;
 varying vec2 TextureCoordsOut;

void main(void) {
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Positions[0], Positions[1], 0.0, 1.0);
    TextureCoordsOut = TextureCoords;
    
}
*/




uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 NormalMatrix;

attribute vec3 Positions;

attribute vec3 Normals;
//varying vec3 NormalsOut;

attribute vec3 TextureCoords;
varying vec2 TextureCoordsOut;

varying vec3 N;
varying vec3 v;

void main(void) {
    //vec4 POS = vec4(Positions[0], Positions[1], Positions[2], 1.0);
    //vec4 NORM = vec4(Normals[0], Normals[1], Normals[2], 1.0);
    v = vec3(ModelViewMatrix * vec4(Positions[0], Positions[1], Positions[2], 1.0));
    N = normalize(vec3(NormalMatrix * vec4(Normals[0], Normals[1], Normals[2], 1.0)));
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Positions[0], Positions[1], Positions[2], 1.0);
    TextureCoordsOut = vec2(TextureCoords[0], TextureCoords[1]);
}


