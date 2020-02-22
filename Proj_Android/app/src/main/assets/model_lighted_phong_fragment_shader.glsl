varying lowp vec3 NormalOut;
varying lowp vec3 EyePosOut;

uniform lowp vec4 ModulateColor;
varying lowp vec2 TextureCoordsOut;
uniform sampler2D Texture;

//r, g, b, [ambient intensity]
uniform lowp vec4 Ambient;

//dirX, dirY, dirZ, [diffuse intensity]
uniform lowp vec4 Diffuse;

//Shininess, Specular Intensity
uniform lowp vec2 Specular;

void main (void) {
    
    lowp vec3 Direction = vec3(-Diffuse[0], -Diffuse[1], -Diffuse[2]);
    lowp vec3 N = normalize(vec3(NormalOut[0], NormalOut[1], NormalOut[2]));
    lowp vec3 E = normalize(EyePosOut);
    lowp vec3 R = normalize(-reflect(Direction, N));
    
    //calculate Diffuse Term:
    lowp float DiffuseIntensity = max(dot(N, Direction), 0.0) * Diffuse[3];
    DiffuseIntensity = clamp(DiffuseIntensity, 0.0, 1.0);
    
    // calculate Specular Term:
    lowp float SpecularIntensity = pow(max(dot(R, E), 0.0), Specular[0]) * Specular[1];
    SpecularIntensity = clamp(SpecularIntensity, 0.0, 10.0);
    
    
    lowp float LightIntensity = Ambient[3] + DiffuseIntensity + SpecularIntensity + SpecularIntensity;
    
    lowp vec4 Color = vec4(ModulateColor[0] * Ambient[0] * LightIntensity,
                           ModulateColor[1] * Ambient[1] * LightIntensity,
                           ModulateColor[2] * Ambient[2] * LightIntensity,
                           ModulateColor[3]) * texture2D(Texture, TextureCoordsOut);
    
    gl_FragColor = vec4(Color[0], Color[1], Color[2], Color[3]);
}
