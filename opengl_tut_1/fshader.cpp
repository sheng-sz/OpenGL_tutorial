#version 330 core
in vec3 ourColor;
in vec2 ourtexcoord;

out vec4 color;

uniform sampler2D myTexture;
uniform sampler2D myTexture1;

uniform float my_mixer;

void main()
{
//	    color = vec4(ourColor, 1.0f);
//    color=texture(myTexture,ourtexcoord);
//    color = vec4(0.0f,1.0f,1.0f,1.0f);
//        color=texture(myTexture,ourtexcoord);


    color=mix(texture(myTexture,vec2(1.0-ourtexcoord.x,ourtexcoord.y)),texture(myTexture1,ourtexcoord),my_mixer);
}

