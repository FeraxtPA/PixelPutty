#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec2 textureSize;
uniform float outlineSize;
uniform vec4 outlineColor;

// Output fragment color
out vec4 finalColor;

void main()
{
    vec4 texel = texture(texture0, fragTexCoord);   // Get texel color
    vec2 texelScale = vec2(0.0);
    texelScale.x = outlineSize / textureSize.x;
    texelScale.y = outlineSize / textureSize.y;

    // Sample points around the text
    float alpha = 0.0;
    for (float x = -1.0; x <= 1.0; x += 1.0) {
        for (float y = -1.0; y <= 1.0; y += 1.0) {
            vec2 offset = vec2(x * texelScale.x, y * texelScale.y);
            alpha = max(alpha, texture(texture0, fragTexCoord + offset).a);
        }
    }

    float outline = min(alpha, 1.0);
    vec4 color = mix(vec4(0.0), outlineColor, outline);
    finalColor = mix(color, texel, texel.a);
}
