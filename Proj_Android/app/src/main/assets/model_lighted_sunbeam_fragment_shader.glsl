varying highp vec3 N;
varying highp vec3 v;

uniform highp vec4 ModulateColor;
varying highp vec2 TextureCoordsOut;
uniform sampler2D Texture;

//r, g, b, [ambient intensity]
uniform highp vec4 Ambient;

//dirX, dirY, dirZ, [diffuse intensity]
uniform highp vec4 Diffuse;

//spotloightX, spotloightY, spotloightZ, [specular intensity]
uniform highp vec4 Specular;

//shininess, emissions
uniform highp vec2 Material;

void main (void) {
    
    highp vec3 Direction = vec3(Diffuse[0], Diffuse[1], Diffuse[2]);
    highp vec3 SpotlightPosition = vec3(Specular[0], Specular[1], Specular[2]);
    
    highp vec3 L = normalize(SpotlightPosition - v);
    highp vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
    highp vec3 R = normalize(-reflect(L,N));
    
    //calculate Diffuse Term:
    highp float Idiff = max(dot(N,L), 0.0) * Diffuse[3];
    Idiff = clamp(Idiff, 0.0, 1.0);
    
    // calculate Specular Term:
    highp float Ispec = pow(max(dot(R,E),0.0), 0.3 * Material[0]) * Specular[3];
    Ispec = clamp(Ispec, 0.0, 1.0);
    // write Total Color:
    //gl_FragColor = gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec;
    
    highp float Ilight = Ambient[3] + Idiff + Ispec;
    Ilight = clamp(Ilight, 0.0, 1.0);
    
    highp vec4 Color = vec4(ModulateColor[0] * Ambient[0] * Ilight,
                           ModulateColor[1] * Ambient[1] * Ilight,
                           ModulateColor[2] * Ambient[2] * Ilight,
                           ModulateColor[3]);
    
    gl_FragColor = Color;// * texture2D(Texture, TextureCoordsOut);
    //gl_FragColor = Iamb + Idiff + Ispec;
    //gl_FragColor = texture2D(Texture, TextureCoordsOut)
    
    
}


/*
void main(void) {
    
    mediump vec3 DiffuseDirection = vec3(Diffuse[0], Diffuse[1], Diffuse[2]);
    
    lowp float DiffuseFactor = max(0.0, dot(NormalsOut, DiffuseDirection));
    
    lowp float DiffuseIntensity = Diffuse[3] * DiffuseFactor;
    lowp float AmbientIntensity = Ambient[3];
    
    lowp float LightIntensity = AmbientIntensity + DiffuseIntensity;
    
    lowp vec4 Color = vec4(ModulateColor[0] * Ambient[0] * LightIntensity,
                           ModulateColor[1] * Ambient[1] * LightIntensity,
                           ModulateColor[2] * Ambient[2] * LightIntensity,
                           ModulateColor[3]);
    
    gl_FragColor = Color * texture2D(Texture, TextureCoordsOut);
}
*/
