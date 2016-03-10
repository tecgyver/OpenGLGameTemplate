#pragma once
#include "GLEW\glew.h"

namespace renderEngine 
{
class FrameBuffer
{
public:
	FrameBuffer(bool hasTextureAttachment, bool hasDepthTextureAttachment, bool hasDepthBufferAttachment, int width, int height);
	~FrameBuffer();
	void bindFrameBuffer();
	void unbindFrameBuffer();
	void cleanUp();

	GLuint getTextureID();
	GLuint getDepthTextureID();
	GLuint getDepthBufferID();

private:
	GLuint createFrameBuffer();
	GLuint createTextureAttachment();
	GLuint createDepthTextureAttachment();
	GLuint createDepthBufferAttachment();

	GLuint mFrameBufferID;
	GLuint mTextureID;
	GLuint mDepthTextureID;
	GLuint mDepthBufferID;

	int mWidth;
	int mHeight;
};

}