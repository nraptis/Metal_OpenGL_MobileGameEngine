uniform lowp vec4 ModulateColor;
varying lowp vec2 TextureCoordsOut;
uniform sampler2D Texture;
uniform lowp vec4 Ambient;

void main(void) {
    
    lowp vec4 Color = vec4(ModulateColor[0] * Ambient[0] * Ambient[3],
                      ModulateColor[1] * Ambient[1] * Ambient[3],
                      ModulateColor[2] * Ambient[2] * Ambient[3],
                      ModulateColor[3]);
    
    gl_FragColor = Color * texture2D(Texture, TextureCoordsOut);
}
