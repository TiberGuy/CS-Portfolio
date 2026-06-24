///////////////////////////////////////////////////////////////////////////////
// scenemanager.cpp
// ============
// manage the preparing and rendering of 3D scenes - textures, materials, lighting
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
///////////////////////////////////////////////////////////////////////////////

#include "SceneManager.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include <glm/gtx/transform.hpp>

// declaration of global variables
namespace
{
	const char* g_ModelName = "model";
	const char* g_ColorValueName = "objectColor";
	const char* g_TextureValueName = "objectTexture";
	const char* g_UseTextureName = "bUseTexture";
	const char* g_UseLightingName = "bUseLighting";
}

/***********************************************************
 *  SceneManager()
 *
 *  The constructor for the class
 ***********************************************************/
SceneManager::SceneManager(ShaderManager *pShaderManager)
{
	m_pShaderManager = pShaderManager;
	m_basicMeshes = new ShapeMeshes();
}

/***********************************************************
 *  ~SceneManager()
 *
 *  The destructor for the class
 ***********************************************************/
SceneManager::~SceneManager()
{
	m_pShaderManager = NULL;
	delete m_basicMeshes;
	m_basicMeshes = NULL;
}

/***********************************************************
 *  CreateGLTexture()
 *
 *  This method is used for loading textures from image files,
 *  configuring the texture mapping parameters in OpenGL,
 *  generating the mipmaps, and loading the read texture into
 *  the next available texture slot in memory.
 ***********************************************************/
bool SceneManager::CreateGLTexture(const char* filename, std::string tag)
{
	int width = 0;
	int height = 0;
	int colorChannels = 0;
	GLuint textureID = 0;

	// indicate to always flip images vertically when loaded
	stbi_set_flip_vertically_on_load(true);

	// try to parse the image data from the specified image file
	unsigned char* image = stbi_load(
		filename,
		&width,
		&height,
		&colorChannels,
		0);

	// if the image was successfully read from the image file
	if (image)
	{
		std::cout << "Successfully loaded image:" << filename << ", width:" << width << ", height:" << height << ", channels:" << colorChannels << std::endl;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if the loaded image is in RGB format
		if (colorChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		// if the loaded image is in RGBA format - it supports transparency
		else if (colorChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		else
		{
			std::cout << "Not implemented to handle image with " << colorChannels << " channels" << std::endl;
			return false;
		}

		// generate the texture mipmaps for mapping textures to lower resolutions
		glGenerateMipmap(GL_TEXTURE_2D);

		// free the image data from local memory
		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

		// register the loaded texture and associate it with the special tag string
		m_textureIDs[m_loadedTextures].ID = textureID;
		m_textureIDs[m_loadedTextures].tag = tag;
		m_loadedTextures++;

		return true;
	}

	std::cout << "Could not load image:" << filename << std::endl;

	// Error loading the image
	return false;
}

/***********************************************************
 *  BindGLTextures()
 *
 *  This method is used for binding the loaded textures to
 *  OpenGL texture memory slots.  There are up to 16 slots.
 ***********************************************************/
void SceneManager::LoadSceneTextures()
{
	bool bReturn = false;

	// load wood texture for the table
	bReturn = CreateGLTexture(
		"textures/rusticwood.jpg",
		"woodTexture");

	// load stainless texture for the mug body
	bReturn = CreateGLTexture(
		"textures/stainless.jpg",
		"mugBodyTexture");

	// load second stainless texture for the mug handle
	bReturn = CreateGLTexture(
		"textures/stainless_end.jpg",
		"mugHandleTexture");

	BindGLTextures();
}

void SceneManager::BindGLTextures()
{
	for (int i = 0; i < m_loadedTextures; i++)
	{
		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_textureIDs[i].ID);
	}
}

/***********************************************************
 *  DestroyGLTextures()
 *
 *  This method is used for freeing the memory in all the
 *  used texture memory slots.
 ***********************************************************/
void SceneManager::DestroyGLTextures()
{
	for (int i = 0; i < m_loadedTextures; i++)
	{
		glGenTextures(1, &m_textureIDs[i].ID);
	}
}

/***********************************************************
 *  FindTextureID()
 *
 *  This method is used for getting an ID for the previously
 *  loaded texture bitmap associated with the passed in tag.
 ***********************************************************/
int SceneManager::FindTextureID(std::string tag)
{
	int textureID = -1;
	int index = 0;
	bool bFound = false;

	while ((index < m_loadedTextures) && (bFound == false))
	{
		if (m_textureIDs[index].tag.compare(tag) == 0)
		{
			textureID = m_textureIDs[index].ID;
			bFound = true;
		}
		else
			index++;
	}

	return(textureID);
}

/***********************************************************
 *  FindTextureSlot()
 *
 *  This method is used for getting a slot index for the previously
 *  loaded texture bitmap associated with the passed in tag.
 ***********************************************************/
int SceneManager::FindTextureSlot(std::string tag)
{
	int textureSlot = -1;
	int index = 0;
	bool bFound = false;

	while ((index < m_loadedTextures) && (bFound == false))
	{
		if (m_textureIDs[index].tag.compare(tag) == 0)
		{
			textureSlot = index;
			bFound = true;
		}
		else
			index++;
	}

	return(textureSlot);
}

/***********************************************************
 *  FindMaterial()
 *
 *  This method is used for getting a material from the previously
 *  defined materials list that is associated with the passed in tag.
 ***********************************************************/
bool SceneManager::FindMaterial(std::string tag, OBJECT_MATERIAL& material)
{
	if (m_objectMaterials.size() == 0)
	{
		return(false);
	}

	int index = 0;
	bool bFound = false;
	while ((index < m_objectMaterials.size()) && (bFound == false))
	{
		if (m_objectMaterials[index].tag.compare(tag) == 0)
		{
			bFound = true;
			material.ambientColor = m_objectMaterials[index].ambientColor;
			material.ambientStrength = m_objectMaterials[index].ambientStrength;
			material.diffuseColor = m_objectMaterials[index].diffuseColor;
			material.specularColor = m_objectMaterials[index].specularColor;
			material.shininess = m_objectMaterials[index].shininess;
		}
		else
		{
			index++;
		}
	}

	return(true);
}

/***********************************************************
 *  SetTransformations()
 *
 *  This method is used for setting the transform buffer
 *  using the passed in transformation values.
 ***********************************************************/
void SceneManager::SetTransformations(
	glm::vec3 scaleXYZ,
	float XrotationDegrees,
	float YrotationDegrees,
	float ZrotationDegrees,
	glm::vec3 positionXYZ)
{
	// variables for this method
	glm::mat4 modelView;
	glm::mat4 scale;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;
	glm::mat4 translation;

	// set the scale value in the transform buffer
	scale = glm::scale(scaleXYZ);
	// set the rotation values in the transform buffer
	rotationX = glm::rotate(glm::radians(XrotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationY = glm::rotate(glm::radians(YrotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationZ = glm::rotate(glm::radians(ZrotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
	// set the translation value in the transform buffer
	translation = glm::translate(positionXYZ);

	modelView = translation * rotationZ * rotationY * rotationX * scale;

	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setMat4Value(g_ModelName, modelView);
	}
}

/***********************************************************
 *  SetShaderColor()
 *
 *  This method is used for setting the passed in color
 *  into the shader for the next draw command
 ***********************************************************/
void SceneManager::SetShaderColor(
	float redColorValue,
	float greenColorValue,
	float blueColorValue,
	float alphaValue)
{
	// variables for this method
	glm::vec4 currentColor;

	currentColor.r = redColorValue;
	currentColor.g = greenColorValue;
	currentColor.b = blueColorValue;
	currentColor.a = alphaValue;

	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setIntValue(g_UseTextureName, false);
		m_pShaderManager->setVec4Value(g_ColorValueName, currentColor);
	}
}

/***********************************************************
 *  SetShaderTexture()
 *
 *  This method is used for setting the texture data
 *  associated with the passed in ID into the shader.
 ***********************************************************/
void SceneManager::SetShaderTexture(
	std::string textureTag)
{
	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setIntValue(g_UseTextureName, true);

		int textureID = -1;
		textureID = FindTextureSlot(textureTag);
		m_pShaderManager->setSampler2DValue(g_TextureValueName, textureID);
	}
}

/***********************************************************
 *  SetTextureUVScale()
 *
 *  This method is used for setting the texture UV scale
 *  values into the shader.
 ***********************************************************/
void SceneManager::SetTextureUVScale(float u, float v)
{
	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setVec2Value("UVscale", glm::vec2(u, v));
	}
}

/***********************************************************
 *  SetShaderMaterial()
 *
 *  This method is used for passing the material values
 *  into the shader.
 ***********************************************************/
void SceneManager::SetShaderMaterial(
	std::string materialTag)
{
	if (m_objectMaterials.size() > 0)
	{
		OBJECT_MATERIAL material;
		bool bReturn = false;

		bReturn = FindMaterial(materialTag, material);
		if (bReturn == true)
		{
			m_pShaderManager->setVec3Value("material.ambientColor", material.ambientColor);
			m_pShaderManager->setFloatValue("material.ambientStrength", material.ambientStrength);
			m_pShaderManager->setVec3Value("material.diffuseColor", material.diffuseColor);
			m_pShaderManager->setVec3Value("material.specularColor", material.specularColor);
			m_pShaderManager->setFloatValue("material.shininess", material.shininess);
		}
	}
}

/**************************************************************/
/*** STUDENTS CAN MODIFY the code in the methods BELOW for  ***/
/*** preparing and rendering their own 3D replicated scenes.***/
/*** Please refer to the code in the OpenGL sample project  ***/
/*** for assistance.                                        ***/
/**************************************************************/


/***********************************************************
 *  PrepareScene()
 *
 *  This method is used for preparing the 3D scene by loading
 *  the shapes, textures in memory to support the 3D scene 
 *  rendering
 ***********************************************************/
void SceneManager::DefineObjectMaterials()
{
	// Matte material for textured objects
	OBJECT_MATERIAL matteMaterial;
	matteMaterial.ambientColor = glm::vec3(0.2f, 0.2f, 0.2f);
	matteMaterial.ambientStrength = 0.3f;
	matteMaterial.diffuseColor = glm::vec3(0.8f, 0.8f, 0.8f);
	matteMaterial.specularColor = glm::vec3(0.2f, 0.2f, 0.2f);
	matteMaterial.shininess = 16.0f;
	matteMaterial.tag = "matte";

	m_objectMaterials.push_back(matteMaterial);

	// Shinier material for the table plane
	OBJECT_MATERIAL shinyMaterial;
	shinyMaterial.ambientColor = glm::vec3(0.3f, 0.3f, 0.3f);
	shinyMaterial.ambientStrength = 0.4f;
	shinyMaterial.diffuseColor = glm::vec3(0.8f, 0.8f, 0.8f);
	shinyMaterial.specularColor = glm::vec3(0.6f, 0.6f, 0.6f);
	shinyMaterial.shininess = 32.0f;
	shinyMaterial.tag = "shiny";

	m_objectMaterials.push_back(shinyMaterial);
}

void SceneManager::SetupSceneLights()
{
	// Turn on custom lighting
	m_pShaderManager->setBoolValue(g_UseLightingName, true);

	// Front upper-right light
	m_pShaderManager->setVec3Value("lightSources[0].position", 10.0f, 10.0f, 10.0f);
	m_pShaderManager->setVec3Value("lightSources[0].ambientColor", 0.01f, 0.01f, 0.01f);
	m_pShaderManager->setVec3Value("lightSources[0].diffuseColor", 0.4f, 0.4f, 0.4f);
	m_pShaderManager->setVec3Value("lightSources[0].specularColor", 1.0f, 1.0f, 1.0f);
	m_pShaderManager->setFloatValue("lightSources[0].focalStrength", 32.0f);
	m_pShaderManager->setFloatValue("lightSources[0].specularIntensity", 0.05f);

	// Back upper-left light
	m_pShaderManager->setVec3Value("lightSources[1].position", -10.0f, 10.0f, -10.0f);
	m_pShaderManager->setVec3Value("lightSources[1].ambientColor", 0.01f, 0.01f, 0.01f);
	m_pShaderManager->setVec3Value("lightSources[1].diffuseColor", 0.4f, 0.4f, 0.4f);
	m_pShaderManager->setVec3Value("lightSources[1].specularColor", 1.0f, 1.0f, 1.0f);
	m_pShaderManager->setFloatValue("lightSources[1].focalStrength", 32.0f);
	m_pShaderManager->setFloatValue("lightSources[1].specularIntensity", 0.05f);

	// Overhead light
	m_pShaderManager->setVec3Value("lightSources[2].position", 1.0f, 10.0f, 1.0f);
	m_pShaderManager->setVec3Value("lightSources[2].ambientColor", 0.01f, 0.01f, 0.01f);
	m_pShaderManager->setVec3Value("lightSources[2].diffuseColor", 0.3f, 0.3f, 0.3f);
	m_pShaderManager->setVec3Value("lightSources[2].specularColor", 1.0f, 1.0f, 1.0f);
	m_pShaderManager->setFloatValue("lightSources[2].focalStrength", 64.0f);
	m_pShaderManager->setFloatValue("lightSources[2].specularIntensity", 0.05f);

	// Warm side light
	m_pShaderManager->setVec3Value("lightSources[3].position", 10.0f, 0.0f, -10.0f);
	m_pShaderManager->setVec3Value("lightSources[3].ambientColor", 0.1f, 0.08f, 0.05f);
	m_pShaderManager->setVec3Value("lightSources[3].diffuseColor", 1.0f, 0.75f, 0.45f);
	m_pShaderManager->setVec3Value("lightSources[3].specularColor", 1.0f, 0.85f, 0.6f);
	m_pShaderManager->setFloatValue("lightSources[3].focalStrength", 16.0f);
	m_pShaderManager->setFloatValue("lightSources[3].specularIntensity", 0.05f);
}

void SceneManager::PrepareScene()
{
	LoadSceneTextures();
	DefineObjectMaterials();
	SetupSceneLights();

	m_basicMeshes->LoadPlaneMesh();
	m_basicMeshes->LoadBoxMesh();
	m_basicMeshes->LoadCylinderMesh();
	m_basicMeshes->LoadTorusMesh();
	m_basicMeshes->LoadSphereMesh();
}

/***********************************************************
 *  RenderScene()
 *
 *  This method is used for rendering the 3D scene by 
 *  transforming and drawing the basic 3D shapes
 ***********************************************************/
void SceneManager::RenderScene()
{
	glm::vec3 scaleXYZ;
	float XrotationDegrees = 0.0f;
	float YrotationDegrees = 0.0f;
	float ZrotationDegrees = 0.0f;
	glm::vec3 positionXYZ;

	// table
	scaleXYZ = glm::vec3(20.0f, 1.0f, 10.0f);
	positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);

	SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
	SetTextureUVScale(6.0f, 4.0f);
	SetShaderTexture("woodTexture");
	SetShaderMaterial("shiny");
	m_basicMeshes->DrawPlaneMesh();

	// notebook pages
	scaleXYZ = glm::vec3(4.2f, 0.18f, 3.0f);
	positionXYZ = glm::vec3(-4.5f, 0.12f, 1.5f);

	SetTransformations(scaleXYZ, 0.0f, -20.0f, 0.0f, positionXYZ);
	SetShaderColor(0.9f, 0.9f, 0.85f, 1.0f);
	SetShaderMaterial("matte");
	m_basicMeshes->DrawBoxMesh();

	// notebook orange cover
	scaleXYZ = glm::vec3(4.15f, 0.08f, 2.95f);
	positionXYZ = glm::vec3(-4.5f, 0.28f, 1.5f);

	SetTransformations(scaleXYZ, 0.0f, -20.0f, 0.0f, positionXYZ);
	SetShaderColor(1.0f, 0.25f, 0.0f, 1.0f);
	SetShaderMaterial("matte");
	m_basicMeshes->DrawBoxMesh();

	// mug body
	scaleXYZ = glm::vec3(1.2f, 3.0f, 1.2f);
	positionXYZ = glm::vec3(0.0f, 1.5f, 0.0f);

	SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
	SetTextureUVScale(1.0f, 1.0f);
	SetShaderTexture("mugBodyTexture");
	SetShaderMaterial("matte");
	m_basicMeshes->DrawCylinderMesh(false, true, true);

	// mug handle
	scaleXYZ = glm::vec3(1.0f, 0.75f, 0.30f);
	positionXYZ = glm::vec3(1.2f, 3.0f, 0.0f);

	SetTransformations(scaleXYZ, 0.0f, 0.0f, 90.0f, positionXYZ);
	SetTextureUVScale(1.0f, 1.0f);
	SetShaderTexture("mugHandleTexture");
	SetShaderMaterial("matte");
	m_basicMeshes->DrawTorusMesh();

	// rubber band ball
	scaleXYZ = glm::vec3(0.65f, 0.65f, 0.65f);
	positionXYZ = glm::vec3(4.0f, 0.65f, 0.0f);

	SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
	SetShaderColor(0.85f, 0.78f, 0.60f, 1.0f);
	SetShaderMaterial("matte");
	m_basicMeshes->DrawSphereMesh();

	// band wrap 1
	scaleXYZ = glm::vec3(0.48f, 0.48f, 0.04f);
	positionXYZ = glm::vec3(4.0f, 0.65f, 0.0f);

	SetTransformations(scaleXYZ, 90.0f, 0.0f, 0.0f, positionXYZ);
	SetShaderColor(0.65f, 0.55f, 0.35f, 1.0f);
	SetShaderMaterial("matte");
	m_basicMeshes->DrawTorusMesh();

	// band wrap 2
	scaleXYZ = glm::vec3(0.50f, 0.50f, 0.04f);
	positionXYZ = glm::vec3(4.0f, 0.65f, 0.0f);

	SetTransformations(scaleXYZ, 45.0f, 0.0f, 0.0f, positionXYZ);
	SetShaderColor(0.65f, 0.55f, 0.35f, 1.0f);
	SetShaderMaterial("matte");
	m_basicMeshes->DrawTorusMesh();

	// band wrap 3
	scaleXYZ = glm::vec3(0.52f, 0.52f, 0.04f);
	positionXYZ = glm::vec3(4.0f, 0.65f, 0.0f);

	SetTransformations(scaleXYZ, 0.0f, 45.0f, 0.0f, positionXYZ);
	SetShaderColor(0.65f, 0.55f, 0.35f, 1.0f);
	SetShaderMaterial("matte");
	m_basicMeshes->DrawTorusMesh();

	// loose rubber band 1 - separate from ball
	scaleXYZ = glm::vec3(0.70f, 0.50f, 0.035f);
	positionXYZ = glm::vec3(2.65f, 0.18f, 0.85f);

	SetTransformations(scaleXYZ, 90.0f, 25.0f, 0.0f, positionXYZ);
	SetShaderColor(0.72f, 0.63f, 0.45f, 1.0f);
	SetShaderMaterial("matte");
	m_basicMeshes->DrawTorusMesh();

	// loose rubber band 2 - separate from ball
	scaleXYZ = glm::vec3(0.68f, 0.48f, 0.035f);
	positionXYZ = glm::vec3(5.35f, 0.18f, 0.75f);

	SetTransformations(scaleXYZ, 90.0f, -20.0f, 0.0f, positionXYZ);
	SetShaderColor(0.72f, 0.63f, 0.45f, 1.0f);
	SetShaderMaterial("matte");
	m_basicMeshes->DrawTorusMesh();

	// loose rubber band 3 - separate from ball
	scaleXYZ = glm::vec3(0.62f, 0.44f, 0.035f);
	positionXYZ = glm::vec3(4.05f, 0.18f, -1.25f);

	SetTransformations(scaleXYZ, 90.0f, 5.0f, 0.0f, positionXYZ);
	SetShaderColor(0.78f, 0.70f, 0.52f, 1.0f);
	SetShaderMaterial("matte");
	m_basicMeshes->DrawTorusMesh();
}
