cbuffer Cbuf
{
    matrix modelView;
    matrix transform;
};

struct VSOut
{
    float3 camPos : POSITION;
    float2 texCoord : TexCoord;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
    float4 position : SV_POSITION;
};

VSOut main(float3 pos : POSITION, float2 tex : TexCoord, float3 n : NORMAl, float3 T : TANGENT)
{
    VSOut vso;
    vso.camPos = (float3)mul(float4(pos, 1.0f), modelView);
    vso.position = mul(float4(pos, 1.0f), transform);
    vso.texCoord = tex;
    vso.normal = normalize((float3) mul(float4(n, 0.0f), modelView));
    vso.tangent = normalize((float3) mul(float4(T, 0.0f), modelView));
    vso.bitangent = -normalize(cross(vso.normal, vso.tangent));
    return vso;
}