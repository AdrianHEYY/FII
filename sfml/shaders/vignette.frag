uniform sampler2D texture;

uniform vec2 iResolution;

const float size = 0.64;
const float sharpness = 1.3;

void main()
{
    vec2 uv = gl_FragCoord.xy / iResolution.xy; // down left = 0, 0
    vec2 center = vec2(0.5, 0.5);

    float distance = sqrt((center.x-uv.x)*(center.x-uv.x) + (center.y-uv.y)*(center.y-uv.y));
    
    float gradient_val;

    if (distance < (1.0 - size)){
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        gradient_val = 1.0;
    }
    else{
        distance = distance - (1.0 - size); 
        float distance_max = 1.0 - size;
        
        float iterpolated_distance = distance / distance_max;
        
        gradient_val = 1.0 - (iterpolated_distance * sharpness - (sharpness - 1.0)); // 0 around edges
        
        gradient_val *= sharpness;
    }
    gradient_val = clamp(gradient_val, 0.0, 1.0);

    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    vec3 sol = pixel.rgb * gradient_val;

    gl_FragColor = vec4(sol.rgb, 1.0);
    if (pixel.a == 0){
    gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
    }
}