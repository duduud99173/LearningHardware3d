Texture3D texture0 : register(t3); // 绑定到 t0 寄存器
SamplerState sampler0 : register(s3); // 绑定到 s0 寄存器


cbuffer timeData : register(b3)
{
    float iTime;
}

float2 RayBoxDist(float3 boxMin, float3 boxMax, float3 rayOrigin, float3 rayDir)
{
    float3 t0 = (boxMin - rayOrigin) / rayDir;
    float3 t1 = (boxMax - rayOrigin) / rayDir;
    
    float3 tmin = min(t0, t1);
    float3 tmax = max(t0, t1);
    
    float far = min(min(tmax.x, tmax.y), tmax.z);
    float near = max(max(tmin.x, tmin.y), tmin.z);
    
    return float2(near, far-near);
}

float SampleTexture(float3 pos)
{
    return texture0.Sample(sampler0, pos);
}


float fbm(float3 pos)
{
    return (SampleTexture(pos / 32.0f) + SampleTexture(pos / 16.0f) + SampleTexture(pos / 8.0f))/3.0f;

}


float3 RotateTexCoords(float3 pos)
{
    float3x3 rotation = float3x3(
        cos(35), 0.0f, -sin(35),
        0.0f, 1.0f, 0.0f,
        sin(35), 0.0f, cos(35)
    );
    return mul(rotation, pos); // 对 pos 应用旋转
}



float SampleDensity(float3 pos)
{
    float threshold = 0.69f;
    pos.z += iTime;
    float density = max(1 - fbm(pos)
    - threshold, 0);
    return density;
}

//uv (-1,1)∪(-0.75,0.75)
float4 main(float2 uv : TEXCOORD) : SV_Target
{
    float3 pixelColor = float3(0.529f, 0.808f, 1.0f);
    pixelColor = 1 - pixelColor;
    float3 rayOrigin = float3(0.0f, 0.0f, 0.0f);
    float3 rayDir = normalize(float3(uv, 1.0f));
    float3 boxMin = float3(-20.0f, 3.0f, 0.0f);
    float3 boxMax = float3(20.0f, 3.4f, 20.0f);
    
    float2 rayBoxDist = RayBoxDist(boxMin, boxMax, rayOrigin, rayDir);
    if (rayBoxDist.x > 0 && rayBoxDist.y > 0)
    {
        float density = 0.0f;
        float step = 0.1f;
        float t = rayBoxDist.x;
        [loop]
        while (t < rayBoxDist.x + rayBoxDist.y)
        {
            density += SampleDensity(rayOrigin + t * rayDir);
            t += step;
        }
        pixelColor = pixelColor * exp(-density);
    }
    
    
    
    return float4(1-pixelColor, 1.0f);
}
