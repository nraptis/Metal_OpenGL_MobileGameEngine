uniform lowp vec4 ModulateColor;
varying lowp vec2 TextureCoordsOut;
uniform sampler2D Texture;

void main(void) {
    lowp vec4 textureColor = texture2D(Texture, TextureCoordsOut);
    gl_FragColor = vec4(ModulateColor[0], ModulateColor[1], ModulateColor[2], ModulateColor[3] * textureColor[3]);
}
