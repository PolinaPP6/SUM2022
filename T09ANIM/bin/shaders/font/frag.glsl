/**/
#version 420

layout(location = 0) out vec4 OutColor;

in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawNormal;
in vec2 DrawTexCoord;

uniform float Time;
uniform vec3 CamLoc;
uniform vec3 Ka, Kd, Ks;
uniform float Ph, Trans;

layout(binding = 0) uniform sampler2D Texture0;
uniform bool IsTexture0;

void main( void )
{  
  vec4 tc = texture(Texture0, DrawTexCoord);
  if (tc.a < 0.5)
    discard;
  OutColor = tc.rgba;
  //OutColor = vec4(1, 1, 1, 1);
}

