cbuffer lightCBuf
{
    float3 lightPos;
    float lightIntensity;
    float3 diffColor;
    float padding;
    float3 ambient;
    float attCon;
    float attLin;
    float attQuad;
};

cbuffer objectCBuf
{
    float3 materialColor;
    float specularIntensity;
    float specularPower;
};


float4 main(float3 viewPos : POSITION, float3 n : NORMAL) : SV_TARGET
{
    const float3 vToL = lightPos - viewPos;
    const float distToL = length(vToL);
    const float3 dirToL = vToL / distToL; 
    const float att = 1.0f / (attCon + attLin * distToL + attQuad * (distToL * distToL));
    const float3 diffuse = diffColor * lightIntensity * att * max(0.0f, dot(dirToL, n));
    
    const float3 halfdist = normalize(vToL - viewPos);
    const float3 specular = diffColor*lightIntensity*pow(max(0.0f,dot(halfdist, n)), specularPower);
    return float4(saturate(diffuse+ambient+specular)*materialColor,1.0f);
}