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
			
			glGenTextures(1, &ste);
			glBindTexture(GL_TEXTURE_2D, ste);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_ATTACHMENT, width, height, 0, GL_STENCIL_ATTACHMENT, GL_INT, NULL);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, ste, 0);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void initStencilBuffer()
		{
			
		}

		void bindDepthMapFrameBuffer()
		{
			glViewport(0, 0, width, height);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glClear(GL_DEPTH_BUFFER_BIT);
		}

		void initCubeMapDepthMapFrameBuffer()
		{
			glGenFramebuffers(1, &fbo);

			// ����cubemap����ÿ������������
			glGenTextures(1, &dep);
			glBindTexture(GL_TEXTURE_CUBE_MAP, dep);
			for (GLuint i = 0; i < 6; ++i)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
					width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			}
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, dep, 0);
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void bindCubeMapDepthMapFrameBuffer()
		{
			glViewport(0, 0, width, height);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glClear(GL_DEPTH_BUFFER_BIT);
		}

		void initRenderBuffer()
		{
			glGenFramebuffers(1, &fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);

			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);

			glGenRenderbuffers(1, &rbo);
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
			
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void bindRenderBuffer()
		{
			glViewport(0, 0, width, height);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void reSize(unsigned int width, unsigned int height)
		{
			this->width = width;
			this->height = height;
		}
	};
}