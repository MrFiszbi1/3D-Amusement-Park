#include "Wall.h"

// Destructor
Wall::~Wall(void)
{
	if (initialized)
	{
		glDeleteLists(display_list, 1);
		glDeleteTextures(1, &texture_obj);
	}
}

// Initializer. Returns false if something went wrong, like not being able to
// load the texture.
bool
Wall::Initialize(void)
{
	display_list = glGenLists(1);
	glNewList(display_list, GL_COMPILE);
	glColor3f(1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	LoadTexture("Wall.tga");

	glBegin(GL_QUADS);
	//top
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0, 1);  	glVertex3f(-1, 1, 1);
	glTexCoord2f(0, 0);  	glVertex3f(-1, -1, 1);
	glTexCoord2f(1, 0);  	glVertex3f(1, -1, 1);
	glTexCoord2f(1, 1);  	glVertex3f(1, 1, 1);

	//bottom
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0, 0);  	glVertex3f(-1, 1, -1);
	glTexCoord2f(1, 0);  	glVertex3f(1, 1, -1);
	glTexCoord2f(1, 1);  	glVertex3f(1, -1, -1);
	glTexCoord2f(0, 1);  	glVertex3f(-1, -1, -1);

	//side
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1, 0);  	glVertex3f(-1, 1, -1);
	glTexCoord2f(1, 1);  	glVertex3f(-1, 1, 1);
	glTexCoord2f(0, 1);  	glVertex3f(1, 1, 1);
	glTexCoord2f(0, 0);  	glVertex3f(1, 1, -1);

	//side
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 0);  	glVertex3f(-1, -1, -1);
	glTexCoord2f(1, 0);  	glVertex3f(1, -1, -1);
	glTexCoord2f(1, 1);  	glVertex3f(1, -1, 1);
	glTexCoord2f(0, 1);  	glVertex3f(-1, -1, 1);

	//side
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 0);  	glVertex3f(-1, 1, -1);
	glTexCoord2f(1, 0);  	glVertex3f(-1, -1, -1);
	glTexCoord2f(1, 1);  	glVertex3f(-1, -1, 1);
	glTexCoord2f(0, 1);  	glVertex3f(-1, 1, 1);

	//side
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1, 1);  	glVertex3f(1, 1, 1);
	glTexCoord2f(0, 1);     glVertex3f(1, -1, 1);
	glTexCoord2f(0, 0);     glVertex3f(1, -1, -1);
	glTexCoord2f(1, 0);  	glVertex3f(1, 1, -1);
	glEnd();
	glEndList();

	initialized = true;

	return true;
}

// Draw just calls the display list we set up earlier.
void
Wall::Draw(void)
{
	float   posn[3];
	float   tangent[3];
	double  angle;

	if (!initialized)
		return;

	//back wall
	glPushMatrix();
	glTranslatef(0.0, -18.0, 1.0);
	glScalef(3, 0.4, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6, -18.0, 1.0);
	glScalef(3, 0.4, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, -18.0, 1.0);
	glScalef(3, 0.4, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-18, -18.0, 1.0);
	glScalef(3, 0.4, 1);
	glCallList(display_list);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(6, -18.0, 1.0);
	glScalef(3, 0.4, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12, -18.0, 1.0);
	glScalef(3, 0.4, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18, -18.0, 1.0);
	glScalef(3, 0.4, 1);
	glCallList(display_list);
	glPopMatrix();

	//front wall
	glPushMatrix();
	glTranslatef(-6, 18.0, 1.0);
	glScalef(3, 0.4, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 18.0, 1.0);
	glScalef(3, 0.4, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-18, 18.0, 1.0);
	glScalef(3, 0.4, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 18.0, 1.0);
	glScalef(3, 0.4, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12, 18.0, 1.0);
	glScalef(3, 0.4, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18, 18.0, 1.0);
	glScalef(3, 0.4, 1);
	glCallList(display_list);
	glPopMatrix();

	//left wall
	glPushMatrix();
	glTranslatef(20.6, 0.0, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.6, 4, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.6, 8, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.6, 12, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.6, 16, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.6, -4, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.6, -8, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.6, -12, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.6, -16, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	//right wall
	glPushMatrix();
	glTranslatef(-20.6, 0.0, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.6, 4, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.6, 8, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.6, 12, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.6, 16, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.6, -4, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.6, -8, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.6, -12, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.6, -16, 1.0);
	glScalef(0.4, 2, 1);
	glCallList(display_list);
	glPopMatrix();
}

void Wall::LoadTexture(const char* filename)
{
	TargaImage* image = TargaImage::Load_Image((char*)filename);
	if (!image)
	{
		std::cerr << "Failed to load texture:  " << filename << std::endl;
		return;
	}

	// reverse the row order
	TargaImage* reversedImage = image->Reverse_Rows();
	delete image;
	image = reversedImage;

	if (!ResizeImage(image))
	{
		std::cerr << "Failed to resize texture." << std::endl;
		return;
	}

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
}

bool Wall::ResizeImage(TargaImage* image)
{
	int newWidth = pow(2.0, (int)ceil(log((float)image->width) / log(2.f)));
	int newHeight = pow(2.0, (int)ceil(log((float)image->width) / log(2.f)));

	newWidth = max(64, newWidth);
	newHeight = max(64, newHeight);

	if (newWidth != image->width && newHeight != image->height)
	{
		unsigned char* scaledData = new unsigned char[newWidth * newHeight * 4];
		if (gluScaleImage(GL_RGBA, image->width, image->height, GL_UNSIGNED_BYTE, image->data, newWidth, newHeight, GL_UNSIGNED_BYTE, scaledData) != 0)
		{
			delete[] scaledData;
			return false;
		}// if

		delete image->data;
		image->data = scaledData;
		image->width = newWidth;
		image->height = newHeight;
	}// if

	return true;
}