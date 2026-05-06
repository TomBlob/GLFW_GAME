#version 330 core

in vec3 worldPos;
out vec4 FragColor;

void main() {
    // grid scale (how dense the lines are)
    float scale = 1.0;

    // get fractional part
    vec2 grid = abs(fract(worldPos.xz * scale - 0.5) - 0.5) / fwidth(worldPos.xz * scale);

    float line = min(grid.x, grid.y);

    // line intensity
    float gridLine = 1.0 - min(line, 1.0);

    // base floor color
    vec3 baseColor = vec3(0.2, 0.2, 0.2);

    // grid line color
    vec3 lineColor = vec3(0.7, 0.7, 0.7);

    vec3 color = mix(baseColor, lineColor, gridLine);

    FragColor = vec4(color, 1.0);
}