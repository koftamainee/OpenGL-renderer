#version 330 core

uniform vec2 resolution;
uniform float time;
out vec4 theColor;

void main() {
    vec2 uv = gl_FragCoord.xy / resolution;

    vec3 col = 0.5 + 0.5 * cos(time + uv.xyx + vec3(0, 2, 4));

    theColor = vec4(col, 1.0);
}
