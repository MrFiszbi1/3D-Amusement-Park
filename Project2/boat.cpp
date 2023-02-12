#include "boat.h"

// Destructor
Boat::~Boat(void)
{
	if (initialized)
	{
		glDeleteLists(boat_list, 1);
		glDeleteLists(stand_list, 1);
	}
}

// Initializer. Returns false if something went wrong, like not being able to
// load the texture.
bool
Boat::Initialize(void)
{
	int i, n = 10;

	boat_list = glGenLists(1);
	glNewList(boat_list, GL_COMPILE);
	glColor3f(1.0, 1.0, 1.0);

	object.loadOBJ("boat.obj");

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	LoadTexture("woodcubes.tga");

	glBegin(GL_TRIANGLES);
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

	stand_list = glGenLists(1);
	glNewList(stand_list, GL_COMPILE);
	glColor3f(1.0, 1.0, 1.0);

	object2.loadOBJ("stand.obj");

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	LoadTexture("bluetiles.tga");

	glBegin(GL_TRIANGLES);
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
Boat::Draw(void)
{
	float   posn[3];
	float   tangent[3];
	double  angle;

	if (!initialized)
		return;

	glPushMatrix();
	glTranslatef(12, 0, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.3, 0.3, 0.3);
	glCallList(boat_list);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(12, 0, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.3, 0.3, 0.3);
	glCallList(stand_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 3, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	glCallList(boat_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 3, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	glCallList(stand_list);
	glPopMatrix();
}

void Boat::LoadTexture(const char* filename)
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

bool Boat::ResizeImage(TargaImage* image)
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