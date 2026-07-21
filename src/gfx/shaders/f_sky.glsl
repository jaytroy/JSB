#version 330 core
in vec2 vUv;
out vec4 FragColor;

uniform vec3 topColor;    // darker blue
uniform vec3 bottomColor; // lighter blue

void main() {
    vec3 skyColor = mix(bottomColor, topColor, vUv.y);
    FragColor = vec4(skyColor, 1.0);
}