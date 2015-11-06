#include "Shader.h"
#include "../Tools/RayUtils.h"

#include <fstream>
using namespace std;

template<> ShaderManager* Singleton<ShaderManager>::m_pSingleton = nullptr;

ShaderManager::ShaderManager()
	: m_CurrentProgram(0)
	, m_CurrentVS(0)
	, m_CurrentPS(0)
	, m_CurrentGS(0)
{
	DEBUG_MESSAGE(RAY_MESSAGE, "ShaderManager Start...");
}

ShaderManager::~ShaderManager()
{
	//Detach all shaders are using
	for (auto itr : m_Programs)
	{
		const GLsizei maxCount = 5;
		GLsizei count=0;
		GLuint shaders[maxCount];
		GLuint program = itr.second.m_Program;
		glGetAttachedShaders(program, maxCount, &count, shaders);
		
		for (int i = 0; i < count; ++i)
		{
			glDetachShader(program, shaders[i]);
			glDeleteProgram(program);
		}
	}

	//Delete all shader objects
	for (auto itr : m_Vs)
	{
		glDeleteShader(itr.second);
	}
	for (auto itr : m_Ps)
	{
		glDeleteShader(itr.second);
	}
	for (auto itr : m_Gs)
	{
		glDeleteShader(itr.second);
	}

	DEBUG_MESSAGE(RAY_MESSAGE, "Unload ShaderManager...");
}

void ShaderManager::CreateEffect(std::string& progName)
{
	GLuint program = glCreateProgram();
	ASSERT(program != 0);
	m_Programs[progName].m_Program = program;
	m_Programs[progName].m_VS= 0;
	m_Programs[progName].m_PS= 0;
	m_Programs[progName].m_GS= 0;
}

void ShaderManager::AddVertexShader(std::string& vsName)
{
	bool ret = CompileShader(vsName, GL_VERTEX_SHADER);
	ASSERT(ret != 0);
}

void ShaderManager::AddPixelShader(std::string& psName)
{
	bool ret = CompileShader(psName, GL_FRAGMENT_SHADER);
	ASSERT(ret != 0);
}

void ShaderManager::AddGeometrySahder(std::string& gsName)
{
	bool ret = CompileShader(gsName, GL_GEOMETRY_SHADER);
	ASSERT(ret != 0);
}

void ShaderManager::SetVS(std::string& vsName, std::string& programName)
{
	GLuint program = m_Programs[programName].m_Program;
	GLuint oldVS = m_Programs[programName].m_VS;
	GLuint newVS = m_Vs[vsName];

	glDetachShader(program, oldVS);
	glAttachShader(program, newVS);
	m_Programs[programName].m_VS = newVS;
}

void ShaderManager::UnSetVS(std::string& vsName, std::string& programName)
{
	glDetachShader(m_Programs[programName].m_Program, m_Vs[vsName]);
	m_Programs[programName].m_VS = 0;
}

void ShaderManager::SetPS(std::string& psName, std::string& programName)
{
	GLuint program = m_Programs[programName].m_Program;
	GLuint oldPS = m_Programs[programName].m_PS;
	GLuint newPS = m_Ps[psName];

	glDetachShader(program, oldPS);
	glAttachShader(program, newPS);
	m_Programs[programName].m_PS = newPS;
}

void ShaderManager::UnSetPS(std::string& psName, std::string& programName)
{
	glDetachShader(m_Programs[programName].m_Program, m_Ps[psName]);
	m_Programs[programName].m_PS = 0;
}

void ShaderManager::SetGS(std::string& gsName, std::string& programName)
{
	GLuint program = m_Programs[programName].m_Program;
	GLuint oldGS = m_Programs[programName].m_GS;
	GLuint newGS = m_Ps[gsName];

	glDetachShader(program, oldGS);
	glAttachShader(program, newGS);
	m_Programs[programName].m_GS = newGS;
}

void ShaderManager::UnSetGS(std::string& gsName, std::string& programName)
{
	glDetachShader(m_Programs[programName].m_Program, m_Gs[gsName]);
	m_Programs[programName].m_GS = 0;
}

const string ShaderManager::GetCurrentProgName() const
{
	string ret;
	if (m_CurrentProgram == 0)
		return ret;

	for (auto itr : m_Programs)
	{
		if (itr.second.m_Program == m_CurrentProgram)
			ret = itr.first;
	}
	return ret;
}

const string ShaderManager::GetCurrentVSName() const
{
	string ret;

	if (m_CurrentVS == 0)
		return ret;

	for (auto itr : m_Vs)
	{
		if (itr.second == m_CurrentVS)
			ret = itr.first;
	}
	return ret;
}

const string ShaderManager::GetCurrentPSName() const
{
	string ret;

	if (m_CurrentPS == 0)
		return ret;
	
	for (auto itr : m_Ps)
	{
		if (itr.second == m_CurrentPS)
			ret = itr.first;
	}
	return ret;
}

const string ShaderManager::GetCurrentGSName() const
{
	string ret;

	if (m_CurrentGS == 0)
		return ret;

	for (auto itr : m_Gs)
	{
		if (itr.second == m_CurrentGS)
			ret = itr.first;
	}
	return ret;
}

const GLuint ShaderManager::GetCurrentProg() const
{
	return m_CurrentProgram;
}

const GLuint ShaderManager::GetCurrentVS() const
{
	return m_CurrentVS;
}

const GLuint ShaderManager::GetCurrentPS() const
{
	return m_CurrentPS;
}

const GLuint ShaderManager::GetCurrentGS() const
{
	return m_CurrentGS;
}

bool ShaderManager::ReadFile(string fileName, std::string& outFile)
{
	ifstream f(fileName.c_str());
	bool ret = false;
	
	if (f.is_open())
	{
		string line;
		while (getline(f, line))
		{
			outFile.append(line);
			outFile.append("\n");
		}
		f.close();
		return true;
	}
	else
	{
		DEBUG_MESSAGE(RAY_ERROR, "shader file can not be found : %s!", fileName.c_str());
	}
	return false;
}

bool ShaderManager::CompileShader(string& shaderName, GLenum shaderType)
{
	GLuint shaderObj = glCreateShader(shaderType);
	ASSERT(shaderObj != 0);

	string fileName="Shaders/";
	if (shaderType == GL_VERTEX_SHADER)
	{
		fileName += shaderName + ".vs";
	}
	else if (shaderType == GL_FRAGMENT_SHADER)
	{
		fileName += shaderName + ".fs";
	}
	else
	{
		fileName += shaderName + ".gs";
	}
	string content;
	ReadFile(fileName, content);

	const GLchar* p[1];
	GLint Lengths[1];
	p[0] = content.c_str();
	Lengths[0] = content.size();

	glShaderSource(shaderObj, 1, p, Lengths);
	glCompileShader(shaderObj);

	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		GLchar InfoLog[1024];
		glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", shaderType, InfoLog);
		return false;
	}
	
	if (shaderType == GL_VERTEX_SHADER)
	{
		m_Vs[shaderName] = shaderObj;
	}
	else if (shaderType == GL_FRAGMENT_SHADER)
	{
		m_Ps[shaderName] = shaderObj;
	}
	else
	{
		m_Gs[shaderName] = shaderObj;
	}

	return true;
}

bool ShaderManager::LinkShaders(std::string& progName)
{
	GLint success = 0;
	GLchar ErrorLog[1024] = {0};
	GLuint program = m_Programs[progName].m_Program;

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == 0)
	{
		glGetProgramInfoLog(program, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		return false;
	}

#ifdef DEBUG_MODE
	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		return false;
	}
#endif
	
	return true;
}

void ShaderManager::EnableShader(std::string& progName)
{
	Program program = m_Programs[progName];
	glUseProgram(program.m_Program);
	m_CurrentProgram = program.m_Program;
	m_CurrentVS = program.m_VS;
	m_CurrentPS = program.m_PS;
	m_CurrentGS = program.m_GS;
}

