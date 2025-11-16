Texture2D tex : register(t0);
Texture2D normalTex : register(t1);
Texture2D aoMap : register(t2);

SamplerState splr;

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

    float specularIntensity;
    float specularPower;
};


float4 main(float3 viewPos : POSITION, float2 tc : TexCoord, float3 N : NORMAL, float3 T : TANGENT, float3 B : BITANGENT) : SV_TARGET
{
    float3 materialColor = tex.Sample(splr, tc);
    float3x3 TBN = float3x3(T, B, N);
    float3 n = mul(normalTex.Sample(splr, tc).xyz*2-1, TBN);
    
    const float3 vToL = lightPos - viewPos;
    const float distToL = length(vToL);
    const float3 dirToL = vToL / distToL;
    const float att = 1.0f / (attCon + attLin * distToL + attQuad * (distToL * distToL));
    const float3 diffuse = diffColor * lightIntensity * att * max(0.0f, dot(dirToL, n));
    
    const float3 halfdist = normalize(vToL - normalize(viewPos));
    const float3 specular = diffColor * lightIntensity * pow(max(0.0f, dot(halfdist, n)), specularPower);
    
    const float ao = aoMap.Sample(splr, tc).r;
    
    return float4(saturate(diffuse + ambient + specular) * materialColor*ao, 1.0f);
}