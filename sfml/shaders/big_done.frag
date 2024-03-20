uniform sampler2D texture;

uniform vec2 iResolution;
uniform float time;

const float size = 0.64;
const float sharpness = 1.3;

void main()
{
    float time = ::time / 3.0;
    if (::time > 1.0) time = (::time - 1.0) / 3.0;

    // Calculate the normalized coordinates
    vec2 uv = gl_FragCoord.xy / iResolution.xy;

    // Calculate the center of the screen
    vec2 center = vec2(0.5, 0.5);

    // Calculate the distance from the current fragment to the center
    float dist = distance(uv, center);

    // Define the radius of the explosion
    float radius = time * 0.5;

    // Define the speed of the explosion
    float speed = 1.0;

    // Calculate the new radius of the explosion
    float newRadius = radius + time * speed;

    // Calculate the alpha value based on the distance from the center
    float alpha = smoothstep(newRadius - 0.1, newRadius, dist);

    // Output color
    //vec4 color = vec4(1.0, 1.0, 1.0, alpha);
    vec4 color;
    if (::time > 1.0){
        color = vec4(vec3(1.0) * (1.0 - alpha), 1.0);
        gl_FragColor = color;
    }
    else{
        color = vec4(1.0, 1.0, 1.0, alpha);

        vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
        gl_FragColor = pixel * color;
    }
    // Output the final color
    //gl_FragColor = color;

}