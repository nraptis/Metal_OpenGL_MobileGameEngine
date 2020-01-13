uniform lowp vec4 ModulateColor;
varying lowp vec4 DestinationColor;
varying lowp vec2 TextureCoordsOut;
uniform sampler2D Texture;

void main(void) {
    gl_FragColor = vec4(ModulateColor[0] * DestinationColor[0],
                        ModulateColor[1] * DestinationColor[1],
                        ModulateColor[2] * DestinationColor[2],
                        ModulateColor[3] * DestinationColor[3]) * texture2D(Texture, TextureCoordsOut);
}
