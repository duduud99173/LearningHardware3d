struct VSOutput
{
    float2 uv : TEXCOORD; 
    float4 position : SV_Position; 
};

VSOutput main(uint vertexID : SV_VertexID) 
{
    float2 positions[4] =
    {
        float2(-1.0f, 1.0f), // вСио╫г
        float2(1.0f, 1.0f), // срио╫г
        float2(-1.0f, -1.0f), // вСоб╫г
        float2(1.0f, -1.0f) // сроб╫г
    };

    VSOutput output;
    output.position = float4(positions[vertexID], 0.999f, 1.0f); // фад╩©у╪ДвЬ╠Й
    output.uv = float2(positions[vertexID].x, positions[vertexID].y * 3.0f / 4.0f);
    return output;
}
