// Request GLSL 3.3
#version 330

// ���_�V�F�[�_�[����̃e�N�X�`�����W����
in vec2 fragTexCoord;

// �@�� (���[���h���)
in vec3 fragNormal;

// �ʒu (���[���h���)
in vec3 fragWorldPos;

// �o�͐F
out vec4 outColor;

// �e�N�X�`���T���v�����O�p
uniform sampler2D uTexture;

// ���s�����p�ɍ\���̂����
struct DirectionalLight
{
	// ���̕���
	vec3 mDirection;
	// �g�U���ːF
	vec3 mDiffuseColor;
	// ���ʔ��ːF
	vec3 mSpecColor;
};

// ���C�e�B���O�puniform
// �J�����̈ʒu (���[���h���)
uniform vec3 uCameraPos;
// �\�ʂ̋��ʔ��ˎw��
uniform float uSpecPower;
// �����̋���
uniform vec3 uAmbientLight;
// ���s�����i���͂P�����j
uniform DirectionalLight uDirLight;


void main()
{
	// �\�ʖ@��N
	vec3 N = normalize(fragNormal);
	// �\�ʂ�������ւ̃x�N�g��L
	vec3 L = normalize(-uDirLight.mDirection);
	// �\�ʂ���J�����ւ̃x�N�g��V
	vec3 V = normalize(uCameraPos - fragWorldPos);
	// N�Ɋւ���-L�̔���R
	vec3 R = normalize(reflect(-L, N));

	// �t�H���̔��˂��v�Z
	vec3 Phong = uAmbientLight;
	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		vec3 Diffuse = uDirLight.mDiffuseColor * NdotL;
		vec3 Specular = uDirLight.mSpecColor * pow(max(0.0, dot(R, V)), uSpecPower);
		Phong += Diffuse + Specular;
	}

	// �ŏI�I�ȐF�̓e�N�X�`���̐F�~�t�H���̌��ialpha=1�j
	outColor = texture(uTexture, fragTexCoord) * vec4(Phong, 1.0f);
}