uniform lowp vec4 ModulateColor;
varying lowp vec2 TextureCoordsOut;
uniform sampler2D Texture;

void main(void) {
    gl_FragColor = ModulateColor * texture2D(Texture, TextureCoordsOut);
}
