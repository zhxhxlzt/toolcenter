#pragma once
#include "Object.h"

namespace yk
{
	struct FrameBuffer
	{
		unsigned int fbo = -1;	// ֡����
		unsigned int tex;	// ��ɫ���帽��
		unsigned int dep;	// ��Ȼ��帽��
		unsigned int ste;	// ģ�建�帽��
		unsigned int rbo;	// ��Ⱦ�������

		unsigned int width = 1024;
		unsigned int height = 1024;

		void initDepthMapFrameBuffer() {
			glGenFramebuffers(1, &fbo);

			// ���������ͼ
			glGenTextures(1, &dep);
			glBindTexture(GL_TEXTURE_2D, dep);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
				width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

			// ���������ͼ����Ȼ���
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, dep, 0);
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void bindDepthMapFrameBuffer()
		{
			glViewport(0, 0, width, height);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glClear(GL_DEPTH_BUFFER_BIT);
		}

		void reSize(unsigned int width, unsigned int height)
		{
			this->width = width;
			this->height = height;
		}
	};
}