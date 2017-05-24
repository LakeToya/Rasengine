#version 130

in vec4 fragmentColor;
in vec2 fragmentPosition;
in vec2 fragmentUV;

out vec4 color;

//Uniform variables are used so that you arent setting per vertex
//Used to change color tranform over time

uniform float time;
uniform sampler2D mySampler;

void main()
{
	float posSin = (sin(3 * time)+1) *.5;
	float pulseMultiplier = posSin * (1 - .5) + .5;

	//color = vec4(fragmentColor.x * pulseMultiplier,
	//			fragmentColor.y * pulseMultiplier,
	//			fragmentColor.z * pulseMultiplier,
	//			fragmentColor.w);
	//
	//
	//Wave effect(sort of)
	vec4 textureColor= texture(mySampler, fragmentUV);
	//color = textureColor * fragmentColor;
	//color = textureColor * vec4(fragmentColor.r * (cos(fragmentPosition.x *4 + time)+1)*.5,
	// 		fragmentColor.g  * (cos(fragmentPosition.y *8 + time)+1)*.5,
	//			fragmentColor.b  * (cos(fragmentPosition.y *2 + time)+1)*.5,
	//			fragmentColor.w);
				
	//blinking effect			
	 color = textureColor * vec4(fragmentColor.x * pulseMultiplier,fragmentColor.y * pulseMultiplier,fragmentColor.z * pulseMultiplier,fragmentColor.w);
	//vec4(1.0 * (cos(time) + 1.0) * 0.5,1.0 * (cos(time + 2.0) + 1.0) * 0.5, 1.0 * (sin(time) + 1.0) * 0.5,0.0);
}