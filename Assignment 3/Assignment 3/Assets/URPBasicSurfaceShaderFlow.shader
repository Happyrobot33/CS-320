Shader "Custom/URPBasicShaderFlow"
{
    Properties
    {
        // Inputs that can be set in Unity's Material Inspector.
        _BaseMap ("Texture", 2D) = "blue" {}
        _TintColor ("Tint Color", Color) = (0,1,1,1)
        _NormalMap ("Normal Map", 2D) = "bump" {} // For normal mapping (Bonus)
    }

    // SubShader contains rendering logic.
    SubShader
    {
        // Make this shader work in URP.
        Tags { "RenderPipeline" = "UniversalRenderPipeline" }
        // Pass defines how the object is drawn.
        Pass
        {
            Name "MainPass"
            Tags { "LightMode" = "UniversalForward" }

            HLSLPROGRAM
            // Calls the vertex shader named vert().
            #pragma vertex vert
            // Calls the fragment shader named frag().
            #pragma fragment frag

            #include "Packages/com.unity.render-pipelines.universal/ShaderLibrary/Core.hlsl"

            // Defines the input data from the 3D model (mesh):
            struct Attributes
            {
                float4 positionOS : POSITION;
                float2 uv : TEXCOORD0;
                float3 normalOS : NORMAL;
            };
            
            // Defines the output data sent to the fragment shader:
            struct Varyings
            {
                float4 positionHCS : SV_POSITION;
                float2 uv : TEXCOORD0;
                float3 normalWS : NORMAL;
            };

            // Defines Texture Samplers for _BaseMap and _NormalMap
            TEXTURE2D(_BaseMap); SAMPLER(sampler_BaseMap);
            TEXTURE2D(_NormalMap); SAMPLER(sampler_NormalMap);

            // _TintColor is stored per material, making it compatible with URP SRP Batcher (optimization)
            CBUFFER_START(UnityPerMaterial)
            float4 _TintColor;
            CBUFFER_END
            
            // Vertex shader: Transforms vertices from Object Space → Clip Space.
            // Passes Texture UVs and Normals to the Fragment Shader.
            Varyings vert(Attributes IN)
            {
                Varyings OUT;
                // Converts object space to clip space for correct positioning
                OUT.positionHCS = TransformObjectToHClip(IN.positionOS.xyz);
                // Passes UV coordinates unchanged for texture mapping
                OUT.uv = IN.uv;
                // Converts normals to world space for lighting
                OUT.normalWS = TransformObjectToWorldNormal(IN.normalOS);
                return OUT;
            }

           // Fragment shader
           // Samples the texture using the UV coordinates
           // Returns the final pixel color
            half4 frag(Varyings IN) : SV_Target
            { 
                //sample the input texture as grayscale at the current frag UV
                half timeOffset = SAMPLE_TEXTURE2D(_BaseMap, sampler_BaseMap, IN.uv).r * 10;
                float pulse = sin(_Time.y + timeOffset) * 0.5 + 0.5;
                return half4(1 * pulse, 0, 0, 1);
            }

            ENDHLSL
        }
    }
}
