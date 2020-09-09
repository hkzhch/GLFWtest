#version 330 core
//in vec3 ourColor;
//in vec3 ourPosition;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 texCoord;
in vec2 emissionTexCoord;
struct Material {
    vec3 ambient;
    sampler2D emission;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct LightDirection{
    vec3 direction;
    vec3 position;
    vec3 color;
};

struct LightPoint{
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};
struct LightSpot{
    
    vec3 position;
    vec3 color;
    vec3 direction;
    float cosPhyInner;
    float cosPhyOuter;

};

vec3 CalcDirLight(LightDirection light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(LightPoint light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(LightSpot light, vec3 normal, vec3 fragPos, vec3 viewDir);

uniform Material material;
uniform LightDirection lightDir;
uniform LightPoint lightPoint;
uniform LightSpot lightSpot;
//uniform vec3 lightPos; 
//uniform vec3 lightColor;
//uniform vec3 colorT;
//uniform vec3 objectColor;
uniform vec3 viewPos;
out vec4 FragColor;



vec3 CalcDirLight(LightDirection light, vec3 normal, vec3 viewDir)
{
	vec3 lightColor = light.color;
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient =texture(material. diffuse,texCoord).rgb * ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, light.direction), 0.0);
    vec3 diffuse = texture(material.diffuse,texCoord).rgb * diff * lightColor;
    
    //specular

    float specularStrength = 0;

    vec3 reflectDir = reflect(-light.direction, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(material.specular,texCoord).rgb * specularStrength * spec * lightColor;
    
    //emission
    vec3 emission = texture(material.emission,texCoord + emissionTexCoord).rgb * lightColor * 0;

    vec3 result = ambient + diffuse + specular + emission;
    return result;
}

vec3 CalcPointLight(LightPoint light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightColor = light.color;
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
                light.quadratic * (distance * distance));
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient =texture(material. diffuse,texCoord).rgb * ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = texture(material.diffuse,texCoord).rgb * diff * lightColor;
    
    //specular
    float specularStrength = 0;
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(material.specular,texCoord).rgb * specularStrength * spec * lightColor;

    //emission
    vec3 emission = texture(material.emission,texCoord + emissionTexCoord).rgb * lightColor * 0;

    vec3 result = ambient + (diffuse + specular)*attenuation + emission;

    return result;
}


vec3 CalcSpotLight(LightSpot light,vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightColor = light.color;
    float distance = length(light.position - fragPos);
    vec3 lightDir = normalize(light.position - fragPos);
    float cosTheta = dot(lightDir, normalize(light.direction));
    //float attenuation = 1.0 / (lightPoint.constant + lightPoint.linear * distance + 
    //            lightPoint.quadratic * (distance * distance));

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient =texture(material.diffuse,texCoord).rgb * ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = texture(material.diffuse,texCoord).rgb * diff * lightColor;
    
    //specular
    float specularStrength = 0;
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(material.specular,texCoord).rgb * specularStrength * spec * lightColor;

    //emission
    vec3 emission = texture(material.emission,texCoord + emissionTexCoord).rgb * lightColor * 0;
    vec3 result;
    if(cosTheta < light.cosPhyOuter)
    {
        result = ambient;
    }else if(cosTheta > light.cosPhyInner)
    {
        result = ambient + diffuse + specular + emission;
    }
    else{
        float intensity = (cosTheta-light.cosPhyOuter)/(light.cosPhyInner-light.cosPhyOuter);
        result = ambient + (diffuse + specular)*intensity + emission;
    }

    return result;
}

void main()
{
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 lightResult = CalcDirLight(lightDir,Normal,viewDir);
    //**************Point Light***************
    lightResult += CalcPointLight(lightPoint,Normal,FragPos,viewDir);
    //**************Point Light***************

    //****************Spot Light****************
    lightResult += CalcSpotLight(lightSpot,Normal,FragPos,viewDir);

    //****************Spot Light****************
    
    






    vec3 result =lightResult;
    FragColor = vec4 ( result , 1.0f );
    //FragColor = texture(material.diffuse,texCoord);
}