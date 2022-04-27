#ifdef GL_ES
precision mediump float;
#endif

#ifndef PREDEFINED_SHADER
#define PREDEFINED_SHADER

vec3 DrawPointLight(vec3 vNormal, vec3 lightPos, vec3 lightColor, vec3 viewPos, vec3 FragPos, float ambientStrength, float specularStrength, float impactValue) {
    const float constant = 1.0;
    const float linear = 0.09;
    const float quadratic = 0.32;
    float distance = length(lightPos - FragPos);
    float attenuation = 1.0 / (constant + linear * distance +
        quadratic * (distance * distance));

    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), impactValue);
    vec3 specular = specularStrength * spec * lightColor;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 DrawDirectionalLight(vec3 vNormal, vec3 lightColor, vec3 viewPos, vec3 FragPos, vec3 direction, float ambientStrength, float specularStrength, float impactValue) {
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(-direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), impactValue);
    vec3 specular = specularStrength * spec * lightColor;

    return (ambient + diffuse + specular);
}

vec3 DrawSpotLight(vec3 vNormal, vec3 lightColor, vec3 viewPos, vec3 FragPos, vec3 Lposition, vec3 direction, float ambientStrength, float specularStrength, float impactValue){
    vec3 lightDir = normalize(Lposition - FragPos);
    
    // check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-direction)); 
    float cutOff = cos(radians(12.0));
    float epsilon = cutOff - 13.0;
    float intensity = clamp((theta - 13.0) / epsilon, 0.0, 1.0);
    
    vec3 ambient = ambientStrength * lightColor;

    if(theta > cutOff) // remember that we're working with angles as cosines instead of degrees so a '>' is used.
    {    
    
        vec3 norm = normalize(vNormal);
        vec3 lightDir = normalize(-direction);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), impactValue);
        vec3 specular = specularStrength * spec * lightColor; 
        
        // attenuation
        float distance    = length(Lposition - FragPos);

        const float constant = 1.0;
        const float linear = 0.09;
        const float quadratic = 0.32;
        float distance1 = length(Lposition - FragPos);
        float attenuation = 1.0 / (constant + linear * distance1 +
            quadratic * (distance1 * distance)); 

        // ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branche
        diffuse   *= attenuation;
        specular *= attenuation;  

        diffuse *= intensity; 
        specular *= intensity; 
            
        vec3 result = ambient + diffuse + specular;
        return result;
    }
    else 
    {
        // else, use ambient light so scene isn't completely dark outside the spot
        return ambient;
    }
}

#endif