//===========================================================================
// Shader: abstrcat base class for creating shaders and config shaders.
//===========================================================================

#pragma once
#include <assert.h>
#include <string>
#include <map>
#include "Singleton.h"

//opengl
#include <GL/glew.h>

struct Program
{
	GLuint m_Program;
	GLuint m_VS; //the vs bounded to this program
	GLuint m_PS; //the ps bounded to this program
	GLuint m_GS; //the gs bounded to this program
};

class ShaderManager : public Singleton<ShaderManager>
{
public:
	ShaderManager();
	~ShaderManager();

	void CreateEffect(std::string& progName);
	void AddVertexShader(std::string& vsName);
	void AddPixelShader(std::string& psName);
	void AddGeometrySahder(std::string& gsName);

	void SetVS(std::string& vsName, std::string& programName);
	void SetPS(std::string& psName, std::string& programName);
	void SetGS(std::string& gsName, std::string& programName);
	void UnSetVS(std::string& vsName, std::string& programName);
	void UnSetPS(std::string& psName, std::string& programName);
	void UnSetGS(std::string& gsName, std::string& programName);

	const std::string GetCurrentProgName() const;
	const std::string GetCurrentVSName() const;
	const std::string GetCurrentPSName() const;
	const std::string GetCurrentGSName() const;

	const GLuint GetCurrentProg() const;
	const GLuint GetCurrentVS() const;
	const GLuint GetCurrentPS() const;
	const GLuint GetCurrentGS() const;

	bool LinkShaders(std::string& progName);
	void EnableShader(std::string& shaderName);

private:
	bool ReadFile(std::string fileName, std::string& outFile);
	bool CompileShader(std::string& shaderName, GLenum shaderType);

private:
	GLuint m_CurrentProgram;
	GLuint m_CurrentVS, m_CurrentPS, m_CurrentGS;

	std::map<std::string, Program> m_Programs;
	std::map<std::string, GLuint> m_Vs;
	std::map<std::string, GLuint> m_Ps;
	std::map<std::string, GLuint> m_Gs;
};