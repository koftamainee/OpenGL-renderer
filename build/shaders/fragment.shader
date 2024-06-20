#version 330 core

uniform vec2 resolution;
uniform float time;
out vec4 theColor;

void main() {
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy / resolution;

    // Time varying pixel color
    vec3 col = 0.5 + 0.5 * cos(time + uv.xyx + vec3(0, 2, 4));

    // Output to screen
    theColor = vec4(col, 1.0);
}
