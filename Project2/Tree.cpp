#include "Tree.h"

// Destructor
Tree::~Tree(void)
{
	if (initialized)
	{
		glDeleteLists(trunk_list, 1);
		glDeleteLists(branch_list, 1);
		glDeleteTextures(1, &texture_obj);
	}
}

// Initializer. Returns false if something went wrong, like not being able to
// load the texture.
bool
Tree::Initialize(void)
{
	int i, n = 10;
	
	trunk_list = glGenLists(1);
	glNewList(trunk_list, GL_COMPILE);
	glColor3f(1.0, 1.0, 1.0);

	object.loadOBJ("trunk.obj");

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	LoadTexture("wood.tga");

	glBegin(GL_POLYGON);
	for (unsigned int i = 0; i < object.vertexIndices.size(); i++) {
		unsigned int normalIndex = object.normalIndices[i];
		vec3 normal = object.temp_normals[normalIndex - 1];
		glNormal3f(normal.x, normal.y, normal.z);

		unsigned int uvIndex = object.uvIndices[i];
		vec2 uv = object.temp_uvs[uvIndex - 1];
		glTexCoord2f(uv.t, uv.s);

		unsigned int vertexIndex = object.vertexIndices[i];
		vec3 vertex = object.temp_vertices[vertexIndex - 1];
		glVertex3f(vertex.x, vertex.y, vertex.z);	
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEndList();

	branch_list = glGenLists(1);
	glNewList(branch_list, GL_COMPILE);
	glColor3f(1.0, 1.0, 1.0);

	object2.loadOBJ("branch.obj");

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	LoadTexture("leaves.tga");

	glBegin(GL_POLYGON);
	for (unsigned int i = 0; i < object2.vertexIndices.size(); i++) {
		unsigned int normalIndex = object2.normalIndices[i];
		vec3 normal = object2.temp_normals[normalIndex - 1];
		glNormal3f(normal.x, normal.y, normal.z);

		unsigned int uvIndex = object2.uvIndices[i];
		vec2 uv = object2.temp_uvs[uvIndex - 1];
		glTexCoord2f(uv.t, uv.s);

		unsigned int vertexIndex = object2.vertexIndices[i];
		vec3 vertex = object2.temp_vertices[vertexIndex - 1];
		glVertex3f(vertex.x, vertex.y, vertex.z);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEndList();

	initialized = true;
	
	return true;
}

// Draw just calls the display list we set up earlier.
void
Tree::Draw(void)
{
	float   posn[3];
	float   tangent[3];
	double  angle;

	if (!initialized)
		return;

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(3, 0, -7);
	// Draw the trunk
	glCallList(trunk_list);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(3, 0, -7);
	// Draw the top tree part
	glCallList(branch_list);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-10, 0, 7);
	glScalef(1.5, 1.5, 1.5);
	glCallList(trunk_list);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-10, 0, 7);
	glScalef(1.5, 1.5, 1.5);
	glCallList(branch_list);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(4, 0, -21);
	glScalef(0.8, 0.8, 0.8);
	glCallList(trunk_list);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(4, 0, -21);
	glScalef(0.8, 0.8, 0.8);
	glCallList(branch_list);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-4, 0, -21);
	glScalef(0.8, 0.8, 0.8);
	glCallList(trunk_list);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-4, 0, -21);
	glScalef(0.8, 0.8, 0.8);
	glCallList(branch_list);
	glPopMatrix();
}

void Tree::LoadTexture(const char* filename)
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

bool Tree::ResizeImage(TargaImage* image)
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