#include "FrameBuffer.h"
#include "DisplayManager.h"

using namespace renderEngine;

FrameBuffer::FrameBuffer(bool hasTextureAttachment, bool hasDepthTextureAttachment, bool hasDepthBufferAttachment, int width, int height)
{
	mFrameBufferID = createFrameBuffer();
	mWidth = width;
	mHeight = height;
	if (hasTextureAttachment)
	{
		mTextureID = createTextureAttachment();
	}
	if (hasDepthTextureAttachment)
	{
		mDepthTextureID = createDepthTextureAttachment();
	}
	if (hasDepthBufferAttachment)
	{
		mDepthBufferID = createDepthBufferAttachment();
	}
	unbindFrameBuffer();
}


FrameBuffer::~FrameBuffer()
{
}

GLuint FrameBuffer::getTextureID()
{
	return mTextureID;
}

GLuint FrameBuffer::getDepthTextureID()
{
	return mDepthTextureID;
}

GLuint FrameBuffer::getDepthBufferID()
{
	return mDepthBufferID;
}

GLuint FrameBuffer::createFrameBuffer()
{
	GLuint frameBufferID;
	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	return frameBufferID;
}

GLuint FrameBuffer::createTextureAttachment()
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureID, 0);
	return textureID;
}

GLuint FrameBuffer::createDepthTextureAttachment()
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, mWidth, mHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureID, 0);
	return textureID;
}

GLuint FrameBuffer::createDepthBufferAttachment()
{
	GLuint depthBufferID;
	glGenRenderbuffers(1, &depthBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mWidth, mHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferID);
	return depthBufferID;
}

void FrameBuffer::bindFrameBuffer()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferID);
	glViewport(0, 0, mWidth, mHeight);
}

void FrameBuffer::unbindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, DisplayManager::WIDTH, DisplayManager::HEIGHT);
}

void FrameBuffer::cleanUp()
{
	glDeleteFramebuffers(1, &mFrameBufferID);
	if (mTextureID > 0)
		glDeleteTextures(1, &mTextureID);
	if (mDepthTextureID > 0)
		glDeleteTextures(1, &mDepthTextureID);
	if (mDepthBufferID > 0)
	glDeleteRenderbuffers(1, &mDepthBufferID);
}