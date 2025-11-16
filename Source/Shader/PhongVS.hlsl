cbuffer Cbuf
{
    matrix modelView;
    matrix modelViewProj;
};

struct VSOut
{
    float3 camPos : POSITION;
    float3 n : NORMAL;
    float4 pos : SV_Position;
};

VSOut main( float3 pos : POSITION, float3 n : NORMAL)
{
    VSOut vso;
    float4 camPos = mul(float4(pos, 1.0f), modelView);
    vso.camPos = camPos.xyz / camPos.w;
    vso.pos = mul(float4(pos, 1.0f), modelViewProj);
    vso.n = mul(n, (float3x3) modelView);
	return vso;
}